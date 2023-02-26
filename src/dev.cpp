
#include "dev.h"

#include <espnow.h>

#include "LittleFS.h"

DEV* DEV::lunaInstance = nullptr;

//***************************************************************************
// PUBLIC METHODS
//***************************************************************************
/////////////////////////////////////////////////////////////////////////
//    Device
/////////////////////////////////////////////////////////////////////////
DEV* DEV::lunaCore() {
  if (lunaInstance == nullptr) {
    lunaInstance = new DEV();
  }
  return lunaInstance;
}

DEV::~DEV() {
  delete lunaInstance;
  lunaInstance = nullptr;
};

void DEV::init() {
  Serial.begin(115200);
  Serial.printf("\n");
  Serial.printf("======================================\n");
  Serial.printf(" ©2023 CRANKCASE                      \n");
  Serial.printf(" LAFAYETTE | LA                       \n");
  Serial.printf("--------------------------------------\n");
  Serial.printf(" LUNA v%s                             \n", VERSION_NUMBER);
  Serial.printf("======================================\n\n");
  Serial.printf("Mounting the file system...\n");

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  this->messageSendInProgress = false;
  this->mqttConnected = false;
  this->wifiConnected = false;

  initWifi();
  initEspNow();
  initMQTT();
}

/////////////////////////////////////////////////////////////////////////
//    Network
/////////////////////////////////////////////////////////////////////////
std::string DEV::macAddress() {
  std::string macAddressStdString = WiFi.macAddress().c_str();
  return macAddressStdString;
}

bool DEV::isMqttConnected() { return this->mqttConnected; }

bool DEV::isWifiConnected() { return this->wifiConnected; }

bool DEV::isEspNowStarted() { return this->espNowStarted; }

bool DEV::isCommunicationReady() { return this->isMqttConnected() || this->isEspNowStarted(); }

//***************************************************************************
// PRIVATE METHODS
//***************************************************************************
/////////////////////////////////////////////////////////////////////////
//    Device
/////////////////////////////////////////////////////////////////////////
DEV::DEV(){};

void DEV::restart() {
  Serial.printf("Restarting...");
  ESP.restart();
}

/////////////////////////////////////////////////////////////////////////
//    Network
/////////////////////////////////////////////////////////////////////////
//----WIFI-------------------------------------------------------------
void DEV::initWifi() {
  if (this->systemConfiguration.program == "no") {
    wifiConnectHandler =
        WiFi.onStationModeGotIP(std::bind(&DEV::onWifiConnect, this, std::placeholders::_1));
    wifiDisconnectHandler = WiFi.onStationModeDisconnected(
        std::bind(&DEV::onWifiDisconnect, this, std::placeholders::_1));
  } else {
  }
  connectToWifi();
}

void DEV::connectToWifi() {
  unsigned int channel;
  sscanf(this->systemConfiguration.channel.c_str(), "%u", &channel);
  if (this->systemConfiguration.program == "no") {
    if (this->systemConfiguration.type == "planet") {
      WiFi.mode(WIFI_AP_STA);
      // Start the STA
      WiFi.begin(this->systemConfiguration.wifiSsid.c_str(),
                 this->systemConfiguration.wifiPassword.c_str());
      Serial.printf("Connecting to %s...\n", this->systemConfiguration.wifiSsid.c_str());
      while (WiFi.status() != WL_CONNECTED) {
        delay(200);
      }
      WiFi.persistent(true);
      WiFi.setAutoReconnect(true);
      // Start the AP
      if (WiFi.softAP((AP_SSID_HEADER + macAddress()).c_str(), HIDDEN_AP_PASSWORD, channel, 1,
                      20)) {
        Serial.printf("Established wireless AP.\n");
        Serial.printf("    SSID: %s\n", (AP_SSID_HEADER + macAddress()).c_str());
      } else {
        Serial.printf("Failed to establish the wireless AP.");
      }
    } else {
      WiFi.mode(WIFI_STA);
    }
  } else {
    WiFi.mode(WIFI_AP);
    if (WiFi.softAP((AP_SSID_HEADER + macAddress()).c_str(), "", channel, 0, 20)) {
      Serial.printf("Established wireless AP.\n");
      Serial.printf("    SSID: %s\n", (AP_SSID_HEADER + macAddress()).c_str());
    } else {
      Serial.printf("Failed to establish the wireless AP.");
    }
  }
}

void DEV::onWifiConnect(const WiFiEventStationModeGotIP& event) {
  this->wifiConnected = true;
  Serial.printf("Connected to wireless network.\n");
  Serial.printf("    SSID: %s\n", this->systemConfiguration.wifiSsid.c_str());
  Serial.printf("    Mac address: %s\n", macAddress().c_str());
  Serial.printf("    IP address: %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("    Subnet mask: %s\n", WiFi.subnetMask().toString().c_str());
  Serial.printf("    Gateway IP: %s\n", WiFi.gatewayIP().toString().c_str());
}

void DEV::onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  this->wifiConnected = false;
  Serial.printf("Disconnected from %s. Attempting to reconnect...\n",
                this->systemConfiguration.wifiSsid.c_str());
}

//----ESP-NOW----------------------------------------------------------
void DEV::initEspNow() {
  if (std::string(this->systemConfiguration.program) == "no") {
    if (esp_now_init() != 0) {
      Serial.printf("Failure to start ESP-NOW service.\n");
    } else {
      Serial.printf("Established ESP-NOW service.\n");
    }
    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_register_send_cb(onEspNowSend);
    esp_now_register_recv_cb(onEspNowReceive);
    this->espNowSendAttempts = 0;
    this->espNowStarted = true;
  } else {
  }
}

void DEV::espNowSend(std::string macAddress, message payload) {
  uint8_t macInBytes[6];
  memcpy(macInBytes, macToArray(macAddress), 6);
  unsigned int channel;
  sscanf(this->systemConfiguration.channel.c_str(), "%u", &channel);
  std::string rawJson = messageToJsonString(payload);
  esp_now_add_peer(macInBytes, ESP_NOW_ROLE_COMBO, channel, NULL, 0);
  this->lastEspNowMessage = payload;
  this->messageSendInProgress = true;
  this->espNowSendAttempts++;
  esp_now_send(macInBytes, (uint8_t*)rawJson.c_str(), rawJson.size());
}

void DEV::onEspNowSend(uint8_t* mac_addr, uint8_t sendStatus) {
  if (sendStatus) {
    Serial.printf("ESP-NOW send: Failed\n");
    if (lunaInstance->espNowSendAttempts <= ESPNOW_MAX_SEND_ATTEMPTS) {
      lunaInstance->queueMessage(lunaInstance->lastEspNowMessage);
    }
  } else {
    lunaInstance->espNowSendAttempts = 0;
    Serial.printf("ESP-NOW send: Success\n");
    esp_now_del_peer(mac_addr);
  }
  lunaInstance->messageSendInProgress = false;
}

void DEV::onEspNowReceive(uint8_t* mac_addr, uint8_t* incomingData, uint8_t len) {
  char* buffer = (char*)incomingData;
  std::string data = buffer;
  Serial.printf("ESP-NOW received data.\n");
  Serial.printf("    payload: %s\n", data.c_str());
  lunaInstance->queueMessage(lunaInstance->jsonToMessage(data));
}

//----MQTT-------------------------------------------------------------
void DEV::initMQTT() {
  if (this->systemConfiguration.program == "no" && this->systemConfiguration.type == "planet") {
    mqttClient = new AsyncMqttClient;
    mqttClient->onConnect(std::bind(&DEV::onMqttConnect, this, std::placeholders::_1));
    mqttClient->onDisconnect(std::bind(&DEV::onMqttDisconnect, this, std::placeholders::_1));
    mqttClient->onSubscribe(
        std::bind(&DEV::onMqttSubscribe, this, std::placeholders::_1, std::placeholders::_2));
    mqttClient->onUnsubscribe(std::bind(&DEV::onMqttUnsubscribe, this, std::placeholders::_1));
    mqttClient->onMessage(std::bind(&DEV::onMqttMessage, this, std::placeholders::_1,
                                    std::placeholders::_2, std::placeholders::_3,
                                    std::placeholders::_4, std::placeholders::_5,
                                    std::placeholders::_6));
    mqttClient->onPublish(std::bind(&DEV::onMqttPublish, this, std::placeholders::_1));
    connectToMqtt();
  }
}

void DEV::mqttPublish(std::string topic, uint8_t qos, bool retain, std::string payload) {
  mqttClient->publish(topic.c_str(), qos, retain, payload.c_str());
}

void DEV::onMqttConnect(bool sessionPresent) {
  this->mqttConnected = true;
  mqttClient->subscribe((macAddress() + "/command").c_str(), 2);
  Serial.printf("Connected to MQTT server.\n");
}

void DEV::onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  this->mqttConnected = false;
  Serial.printf("Disconnected from MQTT server.\n");
  if (WiFi.status() == WL_CONNECTED) {
    this->mqttReconnectTimer.once(10, std::bind(&DEV::connectToMqtt, this));
  }
}

void DEV::onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.printf("Subscribe acknowledged.\n");
  Serial.printf("    id: %u\n", packetId);
  Serial.printf("    qos: %u\n", qos);
}

void DEV::onMqttUnsubscribe(uint16_t packetId) {
  Serial.printf("Unsubscribe acknowledged.\n");
  Serial.printf("    id: %u\n", packetId);
}

void DEV::onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties,
                        size_t len, size_t index, size_t total) {
  std::string payloadString = payload;
  payloadString.insert(len, "\0");
  queueMessage(jsonToMessage(payloadString));

  Serial.printf("Publish received.\n");
}

void DEV::onMqttPublish(uint16_t packetId) {
  Serial.printf("Publish acknowledged.\n");
  Serial.printf("    id: %u\n", packetId);
}

void DEV::connectToMqtt() {
  unsigned int mqttPort;
  sscanf(this->systemConfiguration.mqttPort.c_str(), "%u", &mqttPort);
  Serial.printf("Connecting to MQTT server @ %s:%u...\n",
                this->systemConfiguration.mqttHost.c_str(), mqttPort);
  IPAddress hostIP;
  hostIP.fromString(this->systemConfiguration.mqttHost.c_str());
  mqttClient->setCredentials(this->systemConfiguration.mqttUsername.c_str(),
                             this->systemConfiguration.mqttPassword.c_str());
  mqttClient->setServer(hostIP, mqttPort);
  mqttClient->connect();
}