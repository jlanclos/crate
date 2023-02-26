
#include <espnow.h>
#include <network.h>

wirelessService* wirelessService::wirelessInstance = nullptr;

wirelessService* wirelessService::wirelessCore(deviceConfiguration config) {
  if (wirelessInstance == nullptr) {
    wirelessInstance = new wirelessService(config);
  }
  return wirelessInstance;
}

wirelessService::~wirelessService() {
  delete wirelessInstance;
  wirelessInstance = nullptr;
};

bool wirelessService::isMqttConnected() { return this->mqttConnected; }

bool wirelessService::isWifiConnected() { return this->wifiConnected; }

bool wirelessService::isEspNowStarted() { return this->espNowStarted; }

bool wirelessService::isCommunicationReady() { return this->isMqttConnected() || this->isEspNowStarted(); }

message wirelessService::nextMessage() {
  message messageResult;
  if (this->ioQueue.read().first == operationStatus::SUCCESS) {
    messageResult = this->ioQueue.read().second;
    this->ioQueue.pop();
  }
  return messageResult;
}

void wirelessService::forwardMessageMqtt(message mqttMessage) {
  idType messageIdTyp = mqttMessage.getIdTyp();
  mac sourceMac = mqttMessage.getIdAdd();
  std::vector<dataEntry> payload = mqttMessage.getPayload();

  std::string block;
  switch (messageIdTyp) {
    case idType::DATABLOCK_REPORT:
      block = "data";
      break;
    case idType::CONFIGBLOCK_REPORT:
      block = "config";
      break;
    default:
      block = "undefined";
      break;
  }

  for (uint8_t i = 0; i < payload.size(); i++) {
    std::string topic = sourceMac.getString() + "/" + block + "/" + std::to_string(payload[i].getIdTgt());
    dataType idDataType = payload[i].getIdDataType();
    std::string mqttData;
    switch (idDataType) {
      case dataType::DIGITAL:
        mqttData = std::to_string(payload[i].getDigital());
        break;
      case dataType::UINT8:
        mqttData = std::to_string(payload[i].getAnalog8());
        break;
      case dataType::UINT16:
        mqttData = std::to_string(payload[i].getAnalog16());
        break;
      case dataType::UINT32:
        mqttData = std::to_string(payload[i].getAnalog32());
        break;
      case dataType::STRING:
        mqttData = payload[i].getString();
        break;
      case dataType::MAC:
        mqttData = payload[i].getMac().getString();
        break;
      case dataType::IP:
        mqttData = payload[i].getIp().getString();
        break;
      default:
        break;
    }
    mqttPublish(topic, 2, false, mqttData);
  }
}

void wirelessService::forwardMessageEspNow(message espNowMessage) {
  mac destinationMac = espNowMessage.getIdAdd();

  this->espNowSend(destinationMac, espNowMessage);
}

wirelessService::wirelessService(deviceConfiguration config) {
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  this->config = config;
  this->messageSendInProgress = false;
  this->mqttConnected = false;
  this->wifiConnected = false;

  initWifi();
  initEspNow();
  initMQTT();
};

//----WIFI-------------------------------------------------------------
void wirelessService::initWifi() {
  configProgram programMode = this->config.programMode;

  if (programMode == configProgram::FALSE) {
    wifiConnectHandler =
        WiFi.onStationModeGotIP(std::bind(&wirelessService::onWifiConnect, this, std::placeholders::_1));
    wifiDisconnectHandler =
        WiFi.onStationModeDisconnected(std::bind(&wirelessService::onWifiDisconnect, this, std::placeholders::_1));
  } else {
  }
  connectToWifi();
}

void wirelessService::connectToWifi() {
  configProgram programMode = this->config.programMode;
  configType deviceType = this->config.deviceType;
  std::string wifiSsid = this->config.wifiSsid;
  std::string wifiPassword = this->config.wifiPassword;
  std::string apSsid = this->config.apSsidHeader + this->config.deviceMac.getString();
  std::string apPassword = this->config.apPassword;
  uint8_t channel = this->config.wifiChannel;

  if (programMode == configProgram::FALSE) {
    if (deviceType == configType::PLANET) {
      WiFi.mode(WIFI_AP_STA);
      // Start the STA
      WiFi.begin(wifiSsid.c_str(), wifiPassword.c_str());
      while (WiFi.status() != WL_CONNECTED) {
        delay(200);
      }
      WiFi.persistent(true);
      WiFi.setAutoReconnect(true);
      // Start the AP
      if (WiFi.softAP(apSsid.c_str(), apPassword.c_str(), channel, 1, 1)) {
      } else {
      }
    } else {
      WiFi.mode(WIFI_STA);
    }
  } else {
    WiFi.mode(WIFI_AP);
    if (WiFi.softAP(apSsid.c_str(), "", channel, 0, 1)) {
    } else {
    }
  }
}

void wirelessService::onWifiConnect(const WiFiEventStationModeGotIP& event) { this->wifiConnected = true; }

void wirelessService::onWifiDisconnect(const WiFiEventStationModeDisconnected& event) { this->wifiConnected = false; }

//----ESP-NOW----------------------------------------------------------
void wirelessService::initEspNow() {
  configProgram programMode = this->config.programMode;

  if (programMode == configProgram::FALSE) {
    if (esp_now_init() != 0) {
    } else {
      esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
      esp_now_register_send_cb(onEspNowSend);
      esp_now_register_recv_cb(onEspNowReceive);
      this->espNowSendAttempts = 0;
      this->espNowStarted = true;
    }
  } else {
  }
}

void wirelessService::espNowSend(mac destinationMac, message payload) {
  uint8_t channel = this->config.wifiChannel;
  std::array<uint8_t, 6> macArray = destinationMac.getArray();
  uint8_t macBytes[6] = {macArray[0], macArray[1], macArray[2], macArray[3], macArray[4], macArray[5]};

  std::string rawData = payload.toString();
  esp_now_add_peer(macBytes, ESP_NOW_ROLE_COMBO, channel, NULL, 0);
  this->lastEspNowMessage = payload;
  this->messageSendInProgress = true;
  digitalWrite(2, LOW);
  this->espNowSendAttempts++;
  esp_now_send(macBytes, (uint8_t*)rawData.c_str(), rawData.size());
}

void wirelessService::onEspNowSend(uint8_t* mac_addr, uint8_t sendStatus) {
  uint8_t satelliteSendAttempts = wirelessInstance->config.satelliteSendAttempts;

  if (sendStatus) {
    if (wirelessInstance->espNowSendAttempts <= satelliteSendAttempts) {
      wirelessInstance->ioQueue.push(wirelessInstance->lastEspNowMessage);
    }
  } else {
    wirelessInstance->espNowSendAttempts = 0;
    esp_now_del_peer(mac_addr);
  }
  wirelessInstance->messageSendInProgress = false;
  digitalWrite(2, HIGH);
}

void wirelessService::onEspNowReceive(uint8_t* mac_addr, uint8_t* incomingData, uint8_t len) {
  char* buffer = (char*)incomingData;
  std::string data = buffer;
  message incomingMessage(data);
  wirelessInstance->ioQueue.push(incomingMessage);
}

//----MQTT-------------------------------------------------------------
void wirelessService::initMQTT() {
  configProgram programMode = this->config.programMode;
  configType deviceType = this->config.deviceType;

  if (programMode == configProgram::FALSE && deviceType == configType::PLANET) {
    mqttClient = new AsyncMqttClient;
    mqttClient->onConnect(std::bind(&wirelessService::onMqttConnect, this, std::placeholders::_1));
    mqttClient->onDisconnect(std::bind(&wirelessService::onMqttDisconnect, this, std::placeholders::_1));
    mqttClient->onSubscribe(
        std::bind(&wirelessService::onMqttSubscribe, this, std::placeholders::_1, std::placeholders::_2));
    mqttClient->onUnsubscribe(std::bind(&wirelessService::onMqttUnsubscribe, this, std::placeholders::_1));
    mqttClient->onMessage(std::bind(&wirelessService::onMqttMessage, this, std::placeholders::_1, std::placeholders::_2,
                                    std::placeholders::_3, std::placeholders::_4, std::placeholders::_5,
                                    std::placeholders::_6));
    mqttClient->onPublish(std::bind(&wirelessService::onMqttPublish, this, std::placeholders::_1));
    connectToMqtt();
  }
}

void wirelessService::mqttPublish(std::string topic, uint8_t qos, bool retain, std::string payload) {
  mqttClient->publish(topic.c_str(), qos, retain, payload.c_str());
}

void wirelessService::onMqttConnect(bool sessionPresent) {
  std::string macString = this->config.deviceMac.getString();

  this->mqttConnected = true;
  mqttClient->subscribe((macString + "/command").c_str(), 2);
}

void wirelessService::onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  this->mqttConnected = false;
  if (WiFi.status() == WL_CONNECTED) {
    this->mqttReconnectTimer.once(10, std::bind(&wirelessService::connectToMqtt, this));
  }
}

void wirelessService::onMqttSubscribe(uint16_t packetId, uint8_t qos) {}

void wirelessService::onMqttUnsubscribe(uint16_t packetId) {}

void wirelessService::onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len,
                                    size_t index, size_t total) {
  std::string data = payload;
  message incomingMessage(data);
  ioQueue.push(incomingMessage);
}

void wirelessService::onMqttPublish(uint16_t packetId) {}

void wirelessService::connectToMqtt() {
  std::array<uint8_t, 4> hostIpBytes = this->config.mqttHostIp.getArray();
  uint16_t hostPort = this->config.mqttHostPort;
  std::string mqttUsername = this->config.mqttUsername;
  std::string mqttPassword = this->config.mqttPassword;

  IPAddress hostIp(hostIpBytes[0], hostIpBytes[1], hostIpBytes[2], hostIpBytes[3]);
  mqttClient->setCredentials(mqttUsername.c_str(), mqttPassword.c_str());
  mqttClient->setServer(hostIp, hostPort);
  mqttClient->connect();
}