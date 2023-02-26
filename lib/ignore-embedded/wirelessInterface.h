#pragma once

#include <Arduino.h>
#include <AsyncMqttClient.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>
// #include <message.h>

#include <string>
#include <vector>

class wirelessService {
 public:
  static wirelessService* wirelessCore(deviceConfiguration config);
  ~wirelessService();

  bool isMqttConnected();
  bool isWifiConnected();
  bool isEspNowStarted();
  bool isCommunicationReady();
  message nextMessage();
  void forwardMessageMqtt(message mqttMessage);
  void forwardMessageEspNow(message espNowMessage);

 private:
  static wirelessService* wirelessInstance;

  deviceConfiguration config;
  messageQueue ioQueue;
  bool messageSendInProgress;
  message lastEspNowMessage;
  int espNowSendAttempts;

  AsyncMqttClient* mqttClient;
  Ticker mqttReconnectTimer;
  WiFiEventHandler wifiConnectHandler;
  WiFiEventHandler wifiDisconnectHandler;
  bool mqttConnected;
  bool wifiConnected;
  bool espNowStarted;

  wirelessService(deviceConfiguration config);

  //----WIFI-------------------------------------------------------------
  void initWifi();
  void connectToWifi();
  void onWifiConnect(const WiFiEventStationModeGotIP& event);
  void onWifiDisconnect(const WiFiEventStationModeDisconnected& event);
  //----ESP-NOW----------------------------------------------------------
  void initEspNow();
  // void espNowSend(mac destinationMac, message payload);
  static void onEspNowSend(uint8_t* mac_addr, uint8_t sendStatus);
  static void onEspNowReceive(uint8_t* mac_addr, uint8_t* incomingData, uint8_t len);
  //----MQTT-------------------------------------------------------------
  void initMQTT();
  void mqttPublish(std::string topic, uint8_t qos, bool retain, std::string payload);
  void onMqttConnect(bool sessionPresent);
  void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
  void onMqttSubscribe(uint16_t packetId, uint8_t qos);
  void onMqttUnsubscribe(uint16_t packetId);
  void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index,
                     size_t total);
  void onMqttPublish(uint16_t packetId);
  void connectToMqtt();
};
