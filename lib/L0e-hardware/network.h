#pragma once

#include <Arduino.h>
#include <AsyncMqttClient.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Ticker.h>
#include <config.h>
#include <espnow.h>
#include <file.h>
#include <ip.h>
#include <mac.h>
// #include <message.h>

#include <string>
#include <vector>

class networkService {
 public:
  static networkService& createNetworkService();

  void connect(configuration config);

  bool isConnectedWifi();
  bool isStartedEspNow();
  bool isConnectedMqtt();
  bool isReadyToCommunicate();
  // message nextMessage();
  // void forwardMessageMqtt(message mqttMessage);
  // void forwardMessageEspNow(message espNowMessage);

 private:
  networkService();
  ~networkService();

  configuration config;
  //  messageQueue ioQueue;
  //  bool messageSendInProgress;
  //  message lastEspNowMessage;
  int espNowSendAttempts;

  AsyncMqttClient* mqttClient;
  AsyncWebServer* webServer;
  AsyncWebSocket* webSocket;
  Ticker mqttReconnectTimer;
  WiFiEventHandler wifiConnectHandler;
  WiFiEventHandler wifiDisconnectHandler;
  bool wifiConnected = false;
  bool espNowStarted = false;
  bool mqttConnected = false;
  bool guiStarted = false;

  std::string deviceName;
  std::string deviceGroup;
  std::string deviceIdentifier;
  std::string devicePath;
  hierarchy selectedHierarchy;
  std::string networkSsid;
  std::string networkPassword;
  channel selectedChannel;
  guiState selectedGuiState;
  ip guiIp;
  ip guiSubnet;
  ip guiGateway;
  uint16_t guiPort;
  std::string guiPassword;
  ip mqttIp;
  uint16_t mqttPort;
  std::string mqttUsername;
  std::string mqttPassword;

  //----WIFI-------------------------------------------------------------
  void startWifi();
  void onWifiConnect(const WiFiEventStationModeGotIP& event);
  void onWifiDisconnect(const WiFiEventStationModeDisconnected& event);
  //----ESP-NOW----------------------------------------------------------
  void startEspNow();
  // void espNowSend(mac destinationMac, message payload);
  static void onEspNowSend(uint8_t* mac_addr, uint8_t sendStatus);
  static void onEspNowReceive(uint8_t* mac_addr, uint8_t* incomingData, uint8_t len);
  //----MQTT-------------------------------------------------------------
  void startMqtt();
  void mqttSubscribe(std::string topic, uint8_t qos);
  void mqttPublish(std::string topic, uint8_t qos, bool retain, std::string payload);
  void onMqttConnect(bool sessionPresent);
  void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
  void onMqttSubscribe(uint16_t packetId, uint8_t qos);
  void onMqttUnsubscribe(uint16_t packetId);
  void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index,
                     size_t total);
  void onMqttPublish(uint16_t packetId);
  void connectToMqtt();
  //----GUI--------------------------------------------------------------
  void startGui();
  void handleWebSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg,
                            uint8_t* data, size_t len);
  void handleWebSocketMessage(void* arg, uint8_t* data, size_t len);
};
