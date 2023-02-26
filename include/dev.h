#pragma once

#define VERSION_NUMBER "00.00.18"

#define AP_SSID_HEADER "LUNA:"
#define HIDDEN_AP_PASSWORD "lunaAdmin"
#define WEBSERVER_PORT 80
#define ESPNOW_MAX_SEND_ATTEMPTS 3

#define ARDUINOJSON_ENABLE_STD_STRING_1

#include <Arduino.h>
#include <Ticker.h>

#include <set>
#include <string>
#include <vector>

#include "AsyncMqttClient.h"
#include "AsyncWebSocket.h"

class DEV {
 public:
  //***************************************************************************
  // PUBLIC VARIABLES
  //***************************************************************************

  //***************************************************************************
  // PUBLIC METHODS
  //***************************************************************************
  /////////////////////////////////////////////////////////////////////////
  //    Device
  /////////////////////////////////////////////////////////////////////////
  static DEV* lunaCore();
  ~DEV();

  void init();

  /////////////////////////////////////////////////////////////////////////
  //    Network
  /////////////////////////////////////////////////////////////////////////
  std::string macAddress();
  bool isMqttConnected();
  bool isWifiConnected();
  bool isEspNowStarted();
  bool isCommunicationReady();

 private:
  //***************************************************************************
  // PRIVATE VARIABLES
  //***************************************************************************
  /////////////////////////////////////////////////////////////////////////
  //    Device
  /////////////////////////////////////////////////////////////////////////
  static DEV* lunaInstance;

  config systemConfiguration;
  std::vector<bool> di;
  std::vector<bool> dq;
  std::vector<double> ai;
  std::vector<double> aq;

  /////////////////////////////////////////////////////////////////////////
  //    Messages
  /////////////////////////////////////////////////////////////////////////

  std::vector<message> messageQueue;
  bool messageSendInProgress;
  message lastEspNowMessage;
  int espNowSendAttempts;

  /////////////////////////////////////////////////////////////////////////
  //    Network
  /////////////////////////////////////////////////////////////////////////
  AsyncMqttClient* mqttClient;
  Ticker mqttReconnectTimer;
  WiFiEventHandler wifiConnectHandler;
  WiFiEventHandler wifiDisconnectHandler;
  bool mqttConnected;
  bool wifiConnected;
  bool espNowStarted;

  //***************************************************************************
  // PRIVATE METHODS
  //***************************************************************************
  /////////////////////////////////////////////////////////////////////////
  //    Device
  /////////////////////////////////////////////////////////////////////////
  DEV();
  void restart();

  /////////////////////////////////////////////////////////////////////////
  //    Network
  /////////////////////////////////////////////////////////////////////////
  //----WIFI-------------------------------------------------------------
  void initWifi();
  void connectToWifi();
  void onWifiConnect(const WiFiEventStationModeGotIP& event);
  void onWifiDisconnect(const WiFiEventStationModeDisconnected& event);
  //----ESP-NOW----------------------------------------------------------
  void initEspNow();
  void espNowSend(std::string macAddress, message payload);
  static void onEspNowSend(uint8_t* mac_addr, uint8_t sendStatus);
  static void onEspNowReceive(uint8_t* mac_addr, uint8_t* incomingData, uint8_t len);
  //----MQTT-------------------------------------------------------------
  void initMQTT();
  void mqttPublish(std::string topic, uint8_t qos, bool retain, std::string payload);
  void onMqttConnect(bool sessionPresent);
  void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
  void onMqttSubscribe(uint16_t packetId, uint8_t qos);
  void onMqttUnsubscribe(uint16_t packetId);
  void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties,
                     size_t len, size_t index, size_t total);
  void onMqttPublish(uint16_t packetId);
  void connectToMqtt();
};
