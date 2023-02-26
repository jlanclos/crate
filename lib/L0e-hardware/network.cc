
#include <network.h>

networkService& networkService::createNetworkService() {
  static networkService networkSerivceInstance;
  return networkSerivceInstance;
};

networkService::networkService() {}

networkService::~networkService() {};

void networkService::connect(configuration config) {
  this->config = config;
  this->deviceName = config.getDeviceName();
  this->deviceGroup = config.getDeviceGroup();
  this->deviceIdentifier = deviceName + "@" + WiFi.macAddress().c_str();
  this->devicePath = this->deviceGroup + "/" + deviceIdentifier + "/";
  this->selectedHierarchy = config.getHierarchy();
  this->networkSsid = config.getNetworkSsid();
  this->networkPassword = config.getNetworkPassword();
  this->selectedChannel = config.getChannel();
  this->selectedGuiState = config.getGuiState();
  this->guiIp = config.getGuiIp();
  this->guiSubnet = config.getGuiSubnet();
  this->guiGateway = config.getGuiGateway();
  this->guiPort = config.getGuiPort();
  this->guiPassword = config.getGuiPassword();
  this->mqttIp = config.getMqttIp();
  this->mqttPort = config.getMqttPort();
  this->mqttUsername = config.getMqttUsername();
  this->mqttPassword = config.getMqttPassword();
  this->startWifi();
  this->startEspNow();
  this->startMqtt();
  this->startGui();
};

bool networkService::isConnectedWifi() { return this->wifiConnected; }

bool networkService::isStartedEspNow() { return this->espNowStarted; }

bool networkService::isConnectedMqtt() { return this->mqttConnected; }

bool networkService::isReadyToCommunicate() {
  if (this->selectedHierarchy == hierarchy::HUB) {
    return this->isConnectedMqtt() and this->isStartedEspNow();
  }
  return this->isConnectedMqtt() or this->isStartedEspNow();
}

// message wirelessService::nextMessage() {
//   message messageResult;
//   if (this->ioQueue.read().first == operationStatus::SUCCESS) {
//     messageResult = this->ioQueue.read().second;
//     this->ioQueue.pop();
//   }
//   return messageResult;
// }

// void wirelessService::forwardMessageMqtt(message mqttMessage) {
//   idType messageIdTyp = mqttMessage.getIdTyp();
//   mac sourceMac = mqttMessage.getIdAdd();
//   std::vector<dataEntry> payload = mqttMessage.getPayload();

//   std::string block;
//   switch (messageIdTyp) {
//     case idType::DATABLOCK_REPORT:
//       block = "data";
//       break;
//     case idType::CONFIGBLOCK_REPORT:
//       block = "config";
//       break;
//     default:
//       block = "undefined";
//       break;
//   }

//   for (uint8_t i = 0; i < payload.size(); i++) {
//     std::string topic = sourceMac.getString() + "/" + block + "/" + std::to_string(payload[i].getIdTgt());
//     dataType idDataType = payload[i].getIdDataType();
//     std::string mqttData;
//     switch (idDataType) {
//       case dataType::DIGITAL:
//         mqttData = std::to_string(payload[i].getDigital());
//         break;
//       case dataType::UINT8:
//         mqttData = std::to_string(payload[i].getAnalog8());
//         break;
//       case dataType::UINT16:
//         mqttData = std::to_string(payload[i].getAnalog16());
//         break;
//       case dataType::UINT32:
//         mqttData = std::to_string(payload[i].getAnalog32());
//         break;
//       case dataType::STRING:
//         mqttData = payload[i].getString();
//         break;
//       case dataType::MAC:
//         mqttData = payload[i].getMac().getString();
//         break;
//       case dataType::IP:
//         mqttData = payload[i].getIp().getString();
//         break;
//       default:
//         break;
//     }
//     mqttPublish(topic, 2, false, mqttData);
//   }
// }

// void wirelessService::forwardMessageEspNow(message espNowMessage) {
//   mac destinationMac = espNowMessage.getIdAdd();

//   this->espNowSend(destinationMac, espNowMessage);
// }

// wirelessService::wirelessService(deviceConfiguration config) {
//   pinMode(2, OUTPUT);
//   digitalWrite(2, HIGH);

//   this->config = config;
//   this->messageSendInProgress = false;
//   this->mqttConnected = false;
//   this->wifiConnected = false;

//   initWifi();
//   initEspNow();
//   initMQTT();
// };

//----WIFI-------------------------------------------------------------
void networkService::startWifi() {
  // initiate the connection/disconnection handlers
  wifiConnectHandler = WiFi.onStationModeGotIP(std::bind(&networkService::onWifiConnect, this, std::placeholders::_1));
  wifiDisconnectHandler =
      WiFi.onStationModeDisconnected(std::bind(&networkService::onWifiDisconnect, this, std::placeholders::_1));

  // select the wifi mode
  if (this->selectedGuiState == guiState::ENABLED) {
    WiFi.mode(WiFiMode::WIFI_AP_STA);
  } else {
    WiFi.mode(WiFiMode::WIFI_STA);
  }

  // confirm the wifi mode
  WiFiMode wifiMode = WiFi.getMode();
  bool inApMode = wifiMode == WiFiMode::WIFI_AP_STA or wifiMode == WiFiMode::WIFI_AP;
  bool inStationMode = wifiMode == WiFiMode::WIFI_AP_STA or wifiMode == WiFiMode::WIFI_STA;

  // start the access point
  if (inApMode) {
    std::array<uint8_t, 4> guiIpBytes = this->guiIp.getArray();
    std::array<uint8_t, 4> guiSubnetBytes = this->guiSubnet.getArray();
    std::array<uint8_t, 4> guiGatewayBytes = this->guiGateway.getArray();
    IPAddress guiIp(guiIpBytes[0], guiIpBytes[1], guiIpBytes[2], guiIpBytes[3]);
    IPAddress guiSubnet(guiSubnetBytes[0], guiSubnetBytes[1], guiSubnetBytes[2], guiSubnetBytes[3]);
    IPAddress guiGateway(guiGatewayBytes[0], guiGatewayBytes[1], guiGatewayBytes[2], guiGatewayBytes[3]);
    WiFi.softAPConfig(guiIp, guiGateway, guiSubnet);
    WiFi.softAP(this->deviceIdentifier.c_str(), this->guiPassword.c_str(), (uint8_t)selectedChannel, 0, 1);
  }

  // connect to the configured wifi network
  if (this->selectedHierarchy == hierarchy::HUB and inStationMode) {
    WiFi.begin(this->networkSsid.c_str(), this->networkPassword.c_str());
    while (WiFi.status() != WL_CONNECTED) {
      delay(200);
    }
    WiFi.persistent(true);
    WiFi.setAutoReconnect(true);
  }
}

void networkService::onWifiConnect(const WiFiEventStationModeGotIP& event) { this->wifiConnected = true; }

void networkService::onWifiDisconnect(const WiFiEventStationModeDisconnected& event) { this->wifiConnected = false; }

//----ESP-NOW----------------------------------------------------------
void networkService::startEspNow() {
  if (esp_now_init() != 0) {
  } else {
    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_register_send_cb(onEspNowSend);
    esp_now_register_recv_cb(onEspNowReceive);
    this->espNowSendAttempts = 0;
    this->espNowStarted = true;
  }
}

// void wirelessService::espNowSend(mac destinationMac, message payload) {
//   uint8_t channel = this->config.wifiChannel;
//   std::array<uint8_t, 6> macArray = destinationMac.getArray();
//   uint8_t macBytes[6] = {macArray[0], macArray[1], macArray[2], macArray[3], macArray[4], macArray[5]};

//   std::string rawData = payload.toString();
//   esp_now_add_peer(macBytes, ESP_NOW_ROLE_COMBO, channel, NULL, 0);
//   this->lastEspNowMessage = payload;
//   this->messageSendInProgress = true;
//   digitalWrite(2, LOW);
//   this->espNowSendAttempts++;
//   esp_now_send(macBytes, (uint8_t*)rawData.c_str(), rawData.size());
// }

void networkService::onEspNowSend(uint8_t* mac_addr, uint8_t sendStatus) {
  // uint8_t satelliteSendAttempts = wirelessInstance->config.satelliteSendAttempts;

  // if (sendStatus) {
  //   if (wirelessInstance->espNowSendAttempts <= satelliteSendAttempts) {
  //     wirelessInstance->ioQueue.push(wirelessInstance->lastEspNowMessage);
  //   }
  // } else {
  //   wirelessInstance->espNowSendAttempts = 0;
  //   esp_now_del_peer(mac_addr);
  // }
  // wirelessInstance->messageSendInProgress = false;
  // digitalWrite(2, HIGH);
}

void networkService::onEspNowReceive(uint8_t* mac_addr, uint8_t* incomingData, uint8_t len) {
  // char* buffer = (char*)incomingData;
  // std::string data = buffer;
  // message incomingMessage(data);
  // wirelessInstance->ioQueue.push(incomingMessage);
}

//----MQTT-------------------------------------------------------------
void networkService::startMqtt() {
  if (this->selectedHierarchy == hierarchy::HUB) {
    mqttClient = new AsyncMqttClient;
    mqttClient->onConnect(std::bind(&networkService::onMqttConnect, this, std::placeholders::_1));
    mqttClient->onDisconnect(std::bind(&networkService::onMqttDisconnect, this, std::placeholders::_1));
    mqttClient->onSubscribe(
        std::bind(&networkService::onMqttSubscribe, this, std::placeholders::_1, std::placeholders::_2));
    mqttClient->onUnsubscribe(std::bind(&networkService::onMqttUnsubscribe, this, std::placeholders::_1));
    mqttClient->onMessage(std::bind(&networkService::onMqttMessage, this, std::placeholders::_1, std::placeholders::_2,
                                    std::placeholders::_3, std::placeholders::_4, std::placeholders::_5,
                                    std::placeholders::_6));
    mqttClient->onPublish(std::bind(&networkService::onMqttPublish, this, std::placeholders::_1));
    connectToMqtt();
  }
}

void networkService::mqttSubscribe(std::string topic, uint8_t qos) {
  mqttClient->subscribe((this->devicePath + topic).c_str(), qos);
}

void networkService::mqttPublish(std::string topic, uint8_t qos, bool retain, std::string payload) {
  mqttClient->publish((this->devicePath + topic).c_str(), qos, retain, payload.c_str());
}

void networkService::onMqttConnect(bool sessionPresent) {
  this->mqttConnected = true;
  this->mqttSubscribe("command", 2);
  this->mqttPublish("command", 2, 1, "newdata");
}

void networkService::onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  this->mqttConnected = false;
  if (WiFi.status() == WL_CONNECTED) {
    this->mqttReconnectTimer.once(10, std::bind(&networkService::connectToMqtt, this));
  }
}

void networkService::onMqttSubscribe(uint16_t packetId, uint8_t qos) {}

void networkService::onMqttUnsubscribe(uint16_t packetId) {}

void networkService::onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len,
                                   size_t index, size_t total) {
  std::string data = payload;
  // message incomingMessage(data);
  // ioQueue.push(incomingMessage);
}

void networkService::onMqttPublish(uint16_t packetId) {}

void networkService::connectToMqtt() {
  std::array<uint8_t, 4> mqttIpBytes = this->mqttIp.getArray();
  IPAddress mqttIp(mqttIpBytes[0], mqttIpBytes[1], mqttIpBytes[2], mqttIpBytes[3]);
  mqttClient->setCredentials(this->mqttUsername.c_str(), this->mqttPassword.c_str());
  mqttClient->setServer(mqttIp, this->mqttPort);
  mqttClient->connect();
}

//----GUI--------------------------------------------------------------
void networkService::startGui() {
  webServer = new AsyncWebServer(this->guiPort);
  webSocket = new AsyncWebSocket("/ws");
  // webServer->serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
  webSocket->onEvent(std::bind(&networkService::handleWebSocketEvent, this, std::placeholders::_1,
                               std::placeholders::_2, std::placeholders::_3, std::placeholders::_4,
                               std::placeholders::_5, std::placeholders::_6));
  webServer->addHandler(webSocket);
  webServer->begin();
  this->guiStarted = true;
}

void networkService::handleWebSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type,
                                          void* arg, uint8_t* data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      break;
    case WS_EVT_DISCONNECT:
      break;
    case WS_EVT_DATA:
      this->handleWebSocketMessage(arg, data, len);
      // Serial.printf("%s\n", data);
      // DynamicJsonDocument doc2(1000);
      // deserializeJson(doc2, data);
      // Serial.printf("%s\n", doc2.as<String>().c_str());
      break;
    case WS_EVT_PONG:
      break;
    case WS_EVT_ERROR:
      break;
  };
}

void networkService::handleWebSocketMessage(void* arg, uint8_t* data, size_t len) {
  // AwsFrameInfo *info = (AwsFrameInfo *)arg;
  // if (info->final && info->index == 0 && info->len == len &&
  //     info->opcode == WS_TEXT) {
  //   if (this->jsonReceived != NULL) {
  //     delete this->jsonReceived;
  //   }
  //   if (temp != NULL) {
  //     delete temp;
  //   }
  //   temp = new char[len + 1];
  //   memset(temp, 0, len + 1);
  //   memcpy(temp, data, len);
  //   // temp[len] = 0;

  //   this->jsonReceived = new DynamicJsonDocument(1000);
  //   // String jsonStr(data, len);
  //   deserializeJson(*this->jsonReceived, temp);
  // Serial.printf("%s\n", this->jsonReceived->as<String>().c_str());
  //   String *strData = new String();
  //   this->jsonReceived = doc2.as<String>();
  // }
}