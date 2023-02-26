#pragma once

#define DEFAULT_DEVICE_NAME "newDevice"
#define DEFAULT_DEVICE_GROUP "luna"
#define DEFAULT_HEIRARCHY hierarchy::HUB
#define DEFAULT_EXECUTION_MODE executionMode::STOP
#define DEFAULT_CHANNEL channel::CH_3
#define DEFAULT_HUB_MAC mac(5, 5, 5, 5, 5, 5)
#define DEFAULT_NETWORK_SSID "Les Bon Temps"
#define DEFAULT_NETWORK_PASSWORD "lagniappe"
#define DEFAULT_MQTT_IP ip(192, 168, 0, 55)
#define DEFAULT_MQTT_PORT 1883
#define DEFAULT_MQTT_USERNAME "treehouse"
#define DEFAULT_MQTT_PASSWORD "Tt9899MX5!Ee000"
#define DEFAULT_GUI_STATE guiState::ENABLED
#define DEFAULT_GUI_IP ip(192, 168, 0, 5)
#define DEFAULT_GUI_SUBNET ip(255, 255, 255, 0)
#define DEFAULT_GUI_GATEWAY ip(192, 168, 0, 8)
#define DEFAULT_GUI_PORT 80
#define DEFAULT_GUI_PASSWORD "lunaAutomation"
#define DEFAULT_MAX_SATELLITE_SEND_ATTEMPTS 3
#define DEFAULT_MAX_MESSAGE_QUEUE_SIZE 50

#include <file.h>
#include <ip.h>
#include <mac.h>
#include <stdint.h>

#include <string>

enum class hierarchy : uint8_t { HUB = 0, SATELLITE = 1 };

enum class guiState : uint8_t { ENABLED = 0, DISABLED = 1 };

enum class executionMode : uint8_t { STOP = 0, RUN = 1 };

enum class channel : uint8_t {
  CH_1 = 1,
  CH_2 = 2,
  CH_3 = 3,
  CH_4 = 4,
  CH_5 = 5,
  CH_6 = 6,
  CH_7 = 7,
  CH_8 = 8,
  CH_9 = 9,
  CH_10 = 10,
  CH_11 = 11,
  CH_12 = 12,
  CH_13 = 13,
  CH_14 = 14,
};

enum parameter : uint8_t {
  DEVICE_NAME = 0,
  DEVICE_GROUP = 1,
  HIERARCHY = 2,
  EXECUTION_MODE = 3,
  CHANNEL = 4,
  HUB_MAC = 5,
  NETWORK_SSID = 6,
  NETWORK_PASSWORD = 7,
  MQTT_IP = 8,
  MQTT_PORT = 9,
  MQTT_USERNAME = 10,
  MQTT_PASSWORD = 11,
  GUI_STATE = 12,
  GUI_IP = 13,
  GUI_SUBNET = 14,
  GUI_GATEWAY = 15,
  GUI_PORT = 16,
  GUI_PASSWORD = 17,
  MAX_SATELLITE_SEND_ATTEMPTS = 18,
  MAX_MESSAGE_QUEUE_SIZE = 19,
};

class configuration : public file {
 public:
  configuration();

  void setDeviceName(std::string newDeviceName);
  void setDeviceGroup(std::string newDeviceGroup);
  void setHierarchy(hierarchy newHierarchy);
  void setExecutionMode(executionMode newExectuionMode);
  void setChannel(channel newChannel);
  void setHubMac(mac newHubMac);
  void setNetworkSsid(std::string newNetworkSsid);
  void setNetworkPassword(std::string newNetworkPassword);
  void setMqttIp(ip newMqttIp);
  void setMqttPort(uint16_t newMqttPort);
  void setMqttUsername(std::string newMqttUsername);
  void setMqttPassword(std::string newMqttPassword);
  void setGuiState(guiState newGuiState);
  void setGuiIp(ip newGuiIp);
  void setGuiSubnet(ip newGuiIp);
  void setGuiGateway(ip newGuiGateway);
  void setGuiPort(uint16_t newGuiPort);
  void setGuiPassword(std::string newGuiPassword);
  void setMaxSatelliteSendAttempts(uint8_t newMaxSatelliteSendAttempts);
  void setMaxMessageQueueSize(uint8_t newMaxMessageQueueSize);

  void setDefaults();

  std::string getDeviceName();
  std::string getDeviceGroup();
  hierarchy getHierarchy();
  executionMode getExecutionMode();
  channel getChannel();
  mac getHubMac();
  std::string getNetworkSsid();
  std::string getNetworkPassword();
  ip getMqttIp();
  uint16_t getMqttPort();
  std::string getMqttUsername();
  std::string getMqttPassword();
  guiState getGuiState();
  ip getGuiIp();
  ip getGuiSubnet();
  ip getGuiGateway();
  uint16_t getGuiPort();
  std::string getGuiPassword();
  uint8_t getMaxSatelliteSendAttempts();
  uint8_t getMaxMessageQueueSize();

 private:
};
