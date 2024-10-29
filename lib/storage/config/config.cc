
#include <config/config.h>

// config class
configuration::configuration(byteString_t bytes) { decode(bytes); }

void configuration::setDeviceName(string newDeviceName) { setEntry(parameter::DEVICE_NAME, newDeviceName); }

void configuration::setDeviceGroup(string newDeviceGroup) { setEntry(parameter::DEVICE_GROUP, newDeviceGroup); }

void configuration::setIsHub(toggle newIsHub) { setEntry(parameter::IS_HUB, newIsHub); }

void configuration::setRunEnabled(toggle newRunEnabled) { setEntry(parameter::RUN_ENABLED, newRunEnabled); }

void configuration::setWifiChannel(wifiChannel newChannel) { setEntry(parameter::WIFI_CHANNEL, newChannel); }

void configuration::setHubMac(mac newHubMac) { setEntry(parameter::HUB_MAC, newHubMac); }

void configuration::setNetworkSsid(string newNetworkSsid) { setEntry(parameter::NETWORK_SSID, newNetworkSsid); }

void configuration::setNetworkPassword(string newNetworkPassword) {
  setEntry(parameter::NETWORK_PASSWORD, newNetworkPassword);
}

void configuration::setMqttIp(ip newMqttIp) { setEntry(parameter::MQTT_IP, newMqttIp); }

void configuration::setMqttPort(uinteger newMqttPort) { setEntry(parameter::MQTT_PORT, newMqttPort); }

void configuration::setMqttUsername(string newMqttUsername) { setEntry(parameter::MQTT_USERNAME, newMqttUsername); }

void configuration::setMqttPassword(string newMqttPassword) { setEntry(parameter::MQTT_PASSWORD, newMqttPassword); }

void configuration::setGuiEnabled(toggle newGuiEnabled) { setEntry(parameter::GUI_ENABLED, newGuiEnabled); }

void configuration::setGuiIp(ip newGuiIp) { setEntry(parameter::GUI_IP, newGuiIp); }

void configuration::setGuiSubnet(ip newGuiSubnet) { setEntry(parameter::GUI_SUBNET, newGuiSubnet); }

void configuration::setGuiGateway(ip newGuiGateway) { setEntry(parameter::GUI_GATEWAY, newGuiGateway); }

void configuration::setGuiPort(uinteger newGuiPort) { setEntry(parameter::GUI_PORT, newGuiPort); }

void configuration::setGuiPassword(string newGuiPassword) { setEntry(parameter::GUI_PASSWORD, newGuiPassword); }

void configuration::setMaxMessageSendAttempts(usinteger newMaxMessageSendAttampts) {
  setEntry(parameter::MAX_MESSAGE_SEND_ATTEMPTS, newMaxMessageSendAttampts);
}

void configuration::setMaxMessageQueueSize(usinteger newMaxMessageQueueSize) {
  setEntry(parameter::MAX_MESSAGE_QUEUE_SIZE, newMaxMessageQueueSize);
}

void configuration::setDefaults() {
  setDeviceName(DEFAULT_DEVICE_NAME);
  setDeviceGroup(DEFAULT_DEVICE_GROUP);
  setIsHub(DEFAULT_IS_HUB);
  setRunEnabled(DEFAULT_RUN_ENABLED);
  setWifiChannel(DEFAULT_WIFI_CHANNEL);
  setHubMac(DEFAULT_HUB_MAC);
  setNetworkSsid(DEFAULT_NETWORK_SSID);
  setNetworkPassword(DEFAULT_NETWORK_PASSWORD);
  setMqttIp(DEFAULT_MQTT_IP);
  setMqttPort(DEFAULT_MQTT_PORT);
  setMqttUsername(DEFAULT_MQTT_USERNAME);
  setMqttPassword(DEFAULT_MQTT_PASSWORD);
  setGuiEnabled(DEFAULT_GUI_ENABLED);
  setGuiIp(DEFAULT_GUI_IP);
  setGuiSubnet(DEFAULT_GUI_SUBNET);
  setGuiGateway(DEFAULT_GUI_GATEWAY);
  setGuiPort(DEFAULT_GUI_PORT);
  setGuiPassword(DEFAULT_GUI_PASSWORD);
  setMaxMessageSendAttempts(DEFAULT_MAX_MESSAGE_SEND_ATTEMPTS);
  setMaxMessageQueueSize(DEFAULT_MAX_MESSAGE_QUEUE_SIZE);
}

string configuration::getDeviceName() {
  searchIdResult searchResult = searchId(parameter::DEVICE_NAME);
  if (not searchResult.exists or not(searchResult.type == entryType::STRING)) {
    return DEFAULT_DEVICE_NAME;
  }
  return string(searchResult.entryPackage.getData());
}

string configuration::getDeviceGroup() {
  searchIdResult searchResult = searchId(parameter::DEVICE_GROUP);
  if (not searchResult.exists or not(searchResult.type == entryType::STRING)) {
    return DEFAULT_DEVICE_GROUP;
  }
  return string(searchResult.entryPackage.getData());
}

toggle configuration::getIsHub() {
  searchIdResult searchResult = searchId(parameter::IS_HUB);
  if (not searchResult.exists or not(searchResult.type == entryType::TOGGLE)) {
    return DEFAULT_IS_HUB;
  }
  return toggle(searchResult.entryPackage.getData());
}

toggle configuration::getRunEnabled() {
  searchIdResult searchResult = searchId(parameter::RUN_ENABLED);
  if (not searchResult.exists or not(searchResult.type == entryType::TOGGLE)) {
    return DEFAULT_RUN_ENABLED;
  }
  return toggle(searchResult.entryPackage.getData());
}

wifiChannel configuration::getWifiChannel() {
  searchIdResult searchResult = searchId(parameter::WIFI_CHANNEL);
  if (not searchResult.exists or not(searchResult.type == entryType::WIFI_CHANNEL)) {
    return DEFAULT_WIFI_CHANNEL;
  }
  return wifiChannel(searchResult.entryPackage.getData());
}

mac configuration::getHubMac() {
  searchIdResult searchResult = searchId(parameter::HUB_MAC);
  if (not searchResult.exists or not(searchResult.type == entryType::MAC)) {
    return DEFAULT_HUB_MAC;
  }
  return mac(searchResult.entryPackage.getData());
}

string configuration::getNetworkSsid() {
  searchIdResult searchResult = searchId(parameter::NETWORK_SSID);
  if (not searchResult.exists or not(searchResult.type == entryType::STRING)) {
    return DEFAULT_NETWORK_SSID;
  }
  return string(searchResult.entryPackage.getData());
}

string configuration::getNetworkPassword() {
  searchIdResult searchResult = searchId(parameter::NETWORK_PASSWORD);
  if (not searchResult.exists or not(searchResult.type == entryType::STRING)) {
    return DEFAULT_NETWORK_PASSWORD;
  }
  return string(searchResult.entryPackage.getData());
}

ip configuration::getMqttIp() {
  searchIdResult searchResult = searchId(parameter::MQTT_IP);
  if (not searchResult.exists or not(searchResult.type == entryType::IP)) {
    return DEFAULT_MQTT_IP;
  }
  return ip(searchResult.entryPackage.getData());
}

uinteger configuration::getMqttPort() {
  searchIdResult searchResult = searchId(parameter::MQTT_PORT);
  if (not searchResult.exists or not(searchResult.type == entryType::UINTEGER)) {
    return DEFAULT_MQTT_PORT;
  }
  return uinteger(searchResult.entryPackage.getData());
}

string configuration::getMqttUsername() {
  searchIdResult searchResult = searchId(parameter::MQTT_USERNAME);
  if (not searchResult.exists or not(searchResult.type == entryType::STRING)) {
    return DEFAULT_MQTT_USERNAME;
  }
  return string(searchResult.entryPackage.getData());
}

string configuration::getMqttPassword() {
  searchIdResult searchResult = searchId(parameter::MQTT_PASSWORD);
  if (not searchResult.exists or not(searchResult.type == entryType::STRING)) {
    return DEFAULT_MQTT_PASSWORD;
  }
  return string(searchResult.entryPackage.getData());
}

toggle configuration::getGuiEnabled() {
  searchIdResult searchResult = searchId(parameter::GUI_ENABLED);
  if (not searchResult.exists or not(searchResult.type == entryType::TOGGLE)) {
    return DEFAULT_GUI_ENABLED;
  }
  return toggle(searchResult.entryPackage.getData());
}

ip configuration::getGuiIp() {
  searchIdResult searchResult = searchId(parameter::GUI_IP);
  if (not searchResult.exists or not(searchResult.type == entryType::IP)) {
    return DEFAULT_GUI_IP;
  }
  return ip(searchResult.entryPackage.getData());
}

ip configuration::getGuiSubnet() {
  searchIdResult searchResult = searchId(parameter::GUI_SUBNET);
  if (not searchResult.exists or not(searchResult.type == entryType::IP)) {
    return DEFAULT_GUI_SUBNET;
  }
  return ip(searchResult.entryPackage.getData());
}

ip configuration::getGuiGateway() {
  searchIdResult searchResult = searchId(parameter::GUI_GATEWAY);
  if (not searchResult.exists or not(searchResult.type == entryType::IP)) {
    return DEFAULT_GUI_GATEWAY;
  }
  return ip(searchResult.entryPackage.getData());
}

uinteger configuration::getGuiPort() {
  searchIdResult searchResult = searchId(parameter::GUI_PORT);
  if (not searchResult.exists or not(searchResult.type == entryType::UINTEGER)) {
    return DEFAULT_GUI_PORT;
  }
  return uinteger(searchResult.entryPackage.getData());
}

string configuration::getGuiPassword() {
  searchIdResult searchResult = searchId(parameter::GUI_PASSWORD);
  if (not searchResult.exists or not(searchResult.type == entryType::STRING)) {
    return DEFAULT_GUI_PASSWORD;
  }
  return string(searchResult.entryPackage.getData());
}

usinteger configuration::getMaxMessageSendAttempts() {
  searchIdResult searchResult = searchId(parameter::MAX_MESSAGE_SEND_ATTEMPTS);
  if (not searchResult.exists or not(searchResult.type == entryType::USINTEGER)) {
    return DEFAULT_MAX_MESSAGE_SEND_ATTEMPTS;
  }
  return usinteger(searchResult.entryPackage.getData());
}

usinteger configuration::getMaxMessageQueueSize() {
  searchIdResult searchResult = searchId(parameter::MAX_MESSAGE_QUEUE_SIZE);
  if (not searchResult.exists or not(searchResult.type == entryType::USINTEGER)) {
    return DEFAULT_MAX_MESSAGE_QUEUE_SIZE;
  }
  return usinteger(searchResult.entryPackage.getData());
}