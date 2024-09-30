#pragma once

#define DEFAULT_DEVICE_NAME string("newDevice")
#define DEFAULT_DEVICE_GROUP string("luna")
#define DEFAULT_IS_HUB boolean(true)
#define DEFAULT_RUN_ENABLED boolean(false)
#define DEFAULT_WIFI_CHANNEL wifiChannel(channel::CH_3)
#define DEFAULT_HUB_MAC mac(5, 5, 5, 5, 5, 5)
#define DEFAULT_NETWORK_SSID string("Les Bon Temps")
#define DEFAULT_NETWORK_PASSWORD string("lagniappe")
#define DEFAULT_MQTT_IP ip(192, 168, 0, 55)
#define DEFAULT_MQTT_PORT uinteger(1883)
#define DEFAULT_MQTT_USERNAME string("treehouse")
#define DEFAULT_MQTT_PASSWORD string("Tt9899MX5!Ee000")
#define DEFAULT_GUI_ENABLED boolean(true)
#define DEFAULT_GUI_IP ip(192, 168, 0, 5)
#define DEFAULT_GUI_SUBNET ip(255, 255, 255, 0)
#define DEFAULT_GUI_GATEWAY ip(192, 168, 0, 8)
#define DEFAULT_GUI_PORT uinteger(80)
#define DEFAULT_GUI_PASSWORD string("lunaAutomation")
#define DEFAULT_MAX_MESSAGE_SEND_ATTEMPTS usinteger(3)
#define DEFAULT_MAX_MESSAGE_QUEUE_SIZE usinteger(50)

#include <file/file.h>

enum parameter : uint8_t {
  DEVICE_NAME = 0,
  DEVICE_GROUP = 1,
  IS_HUB = 2,
  RUN_ENABLED = 3,
  WIFI_CHANNEL = 4,
  HUB_MAC = 5,
  NETWORK_SSID = 6,
  NETWORK_PASSWORD = 7,
  MQTT_IP = 8,
  MQTT_PORT = 9,
  MQTT_USERNAME = 10,
  MQTT_PASSWORD = 11,
  GUI_ENABLED = 12,
  GUI_IP = 13,
  GUI_SUBNET = 14,
  GUI_GATEWAY = 15,
  GUI_PORT = 16,
  GUI_PASSWORD = 17,
  MAX_MESSAGE_SEND_ATTEMPTS = 18,
  MAX_MESSAGE_QUEUE_SIZE = 19,
};

class configuration : public file {
 public:
  configuration();
  configuration(byteString_t bytes);

  void setDeviceName(string newDeviceName);
  void setDeviceGroup(string newDeviceGroup);
  void setIsHub(boolean newIsHub);
  void setRunEnabled(boolean newRunEnabled);
  void setWifiChannel(wifiChannel newChannel);
  void setHubMac(mac newHubMac);
  void setNetworkSsid(string newNetworkSsid);
  void setNetworkPassword(string newNetworkPassword);
  void setMqttIp(ip newMqttIp);
  void setMqttPort(uinteger newMqttPort);
  void setMqttUsername(string newMqttUsername);
  void setMqttPassword(string newMqttPassword);
  void setGuiEnabled(boolean newGuiEnabled);
  void setGuiIp(ip newGuiIp);
  void setGuiSubnet(ip newGuiIp);
  void setGuiGateway(ip newGuiGateway);
  void setGuiPort(uinteger newGuiPort);
  void setGuiPassword(string newGuiPassword);
  void setMaxMessageSendAttempts(usinteger newMaxMessageSendAttempts);
  void setMaxMessageQueueSize(usinteger newMaxMessageQueueSize);

  void setDefaults();

  string getDeviceName();
  string getDeviceGroup();
  boolean getIsHub();
  boolean getRunEnabled();
  wifiChannel getWifiChannel();
  mac getHubMac();
  string getNetworkSsid();
  string getNetworkPassword();
  ip getMqttIp();
  uinteger getMqttPort();
  string getMqttUsername();
  string getMqttPassword();
  boolean getGuiEnabled();
  ip getGuiIp();
  ip getGuiSubnet();
  ip getGuiGateway();
  uinteger getGuiPort();
  string getGuiPassword();
  usinteger getMaxMessageSendAttempts();
  usinteger getMaxMessageQueueSize();

 private:
  file config;
};
