
#include <config.h>

// config class
configuration::configuration() {}

void configuration::setDeviceName(std::string newDeviceName) {
  this->updateEntryString(parameter::DEVICE_NAME, newDeviceName);
}

void configuration::setDeviceGroup(std::string newDeviceGroup) {
  this->updateEntryString(parameter::DEVICE_GROUP, newDeviceGroup);
}

void configuration::setHierarchy(hierarchy newHierarchy) {
  this->updateEntryAnalog8(parameter::HIERARCHY, (uint8_t)newHierarchy);
}

void configuration::setExecutionMode(executionMode newExecutionMode) {
  this->updateEntryAnalog8(parameter::EXECUTION_MODE, (uint8_t)newExecutionMode);
}

void configuration::setChannel(channel newChannel) {
  this->updateEntryAnalog8(parameter::CHANNEL, (uint8_t)newChannel);
}

void configuration::setHubMac(mac newHubMac) { this->updateEntryMac(parameter::HUB_MAC, newHubMac); }

void configuration::setNetworkSsid(std::string newNetworkSsid) {
  this->updateEntryString(parameter::NETWORK_SSID, newNetworkSsid);
}

void configuration::setNetworkPassword(std::string newNetworkPassword) {
  this->updateEntryString(parameter::NETWORK_PASSWORD, newNetworkPassword);
}

void configuration::setMqttIp(ip newMqttIp) { this->updateEntryIp(parameter::MQTT_IP, newMqttIp); }

void configuration::setMqttPort(uint16_t newMqttPort) { this->updateEntryAnalog16(parameter::MQTT_PORT, newMqttPort); }

void configuration::setMqttUsername(std::string newMqttUsername) {
  this->updateEntryString(parameter::MQTT_USERNAME, newMqttUsername);
}

void configuration::setMqttPassword(std::string newMqttPassword) {
  this->updateEntryString(parameter::MQTT_PASSWORD, newMqttPassword);
}

void configuration::setGuiState(guiState newGuiState) {
  this->updateEntryAnalog8(parameter::GUI_STATE, (uint8_t)newGuiState);
}

void configuration::setGuiIp(ip newGuiIp) { this->updateEntryIp(parameter::GUI_IP, newGuiIp); }

void configuration::setGuiSubnet(ip newGuiSubnet) { this->updateEntryIp(parameter::GUI_SUBNET, newGuiSubnet); }

void configuration::setGuiGateway(ip newGuiGateway) { this->updateEntryIp(parameter::GUI_GATEWAY, newGuiGateway); }

void configuration::setGuiPort(uint16_t newGuiPort) { this->updateEntryAnalog16(parameter::GUI_PORT, newGuiPort); }

void configuration::setGuiPassword(std::string newGuiPassword) {
  this->updateEntryString(parameter::GUI_PASSWORD, newGuiPassword);
}

void configuration::setMaxSatelliteSendAttempts(uint8_t newMaxSatelliteSendAttampts) {
  this->updateEntryAnalog8(parameter::MAX_SATELLITE_SEND_ATTEMPTS, newMaxSatelliteSendAttampts);
}

void configuration::setMaxMessageQueueSize(uint8_t newMaxMessageQueueSize) {
  this->updateEntryAnalog8(parameter::MAX_MESSAGE_QUEUE_SIZE, newMaxMessageQueueSize);
}

void configuration::setDefaults() {
  setDeviceName(DEFAULT_DEVICE_NAME);
  setDeviceGroup(DEFAULT_DEVICE_GROUP);
  setHierarchy(DEFAULT_HEIRARCHY);
  setExecutionMode(DEFAULT_EXECUTION_MODE);
  setChannel(DEFAULT_CHANNEL);
  setHubMac(DEFAULT_HUB_MAC);
  setNetworkSsid(DEFAULT_NETWORK_SSID);
  setNetworkPassword(DEFAULT_NETWORK_PASSWORD);
  setMqttIp(DEFAULT_MQTT_IP);
  setMqttPort(DEFAULT_MQTT_PORT);
  setMqttUsername(DEFAULT_MQTT_USERNAME);
  setMqttPassword(DEFAULT_MQTT_PASSWORD);
  setGuiState(DEFAULT_GUI_STATE);
  setGuiIp(DEFAULT_GUI_IP);
  setGuiSubnet(DEFAULT_GUI_SUBNET);
  setGuiGateway(DEFAULT_GUI_GATEWAY);
  setGuiPort(DEFAULT_GUI_PORT);
  setGuiPassword(DEFAULT_GUI_PASSWORD);
  setMaxSatelliteSendAttempts(DEFAULT_MAX_SATELLITE_SEND_ATTEMPTS);
  setMaxMessageQueueSize(DEFAULT_MAX_MESSAGE_QUEUE_SIZE);
}

std::string configuration::getDeviceName() {
  reportSummary summary = this->reportEntry(parameter::DEVICE_NAME);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::STRING)) {
    this->setDefaults();
    return DEFAULT_DEVICE_NAME;
  }
  return entry.getString();
}

std::string configuration::getDeviceGroup() {
  reportSummary summary = this->reportEntry(parameter::DEVICE_GROUP);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::STRING)) {
    this->setDefaults();
    return DEFAULT_DEVICE_GROUP;
  }
  return entry.getString();
}

hierarchy configuration::getHierarchy() {
  reportSummary summary = this->reportEntry(parameter::HIERARCHY);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::UINT8)) {
    this->setDefaults();
    return (hierarchy)DEFAULT_HEIRARCHY;
  }
  return (hierarchy)entry.getAnalog8();
}

executionMode configuration::getExecutionMode() {
  reportSummary summary = this->reportEntry(parameter::EXECUTION_MODE);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::UINT8)) {
    this->setDefaults();
    return (executionMode)DEFAULT_EXECUTION_MODE;
  }
  return (executionMode)entry.getAnalog8();
}

channel configuration::getChannel() {
  reportSummary summary = this->reportEntry(parameter::CHANNEL);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::UINT8)) {
    this->setDefaults();
    return (channel)DEFAULT_CHANNEL;
  }
  return (channel)entry.getAnalog8();
}

mac configuration::getHubMac() {
  reportSummary summary = this->reportEntry(parameter::HUB_MAC);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::MAC)) {
    this->setDefaults();
    return DEFAULT_HUB_MAC;
  }
  return entry.getMac();
}

std::string configuration::getNetworkSsid() {
  reportSummary summary = this->reportEntry(parameter::NETWORK_SSID);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::STRING)) {
    this->setDefaults();
    return DEFAULT_NETWORK_SSID;
  }
  return entry.getString();
}

std::string configuration::getNetworkPassword() {
  reportSummary summary = this->reportEntry(parameter::NETWORK_PASSWORD);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::STRING)) {
    this->setDefaults();
    return DEFAULT_NETWORK_PASSWORD;
  }
  return entry.getString();
}

ip configuration::getMqttIp() {
  reportSummary summary = this->reportEntry(parameter::MQTT_IP);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::IP)) {
    this->setDefaults();
    return DEFAULT_MQTT_IP;
  }
  return entry.getIp();
}

uint16_t configuration::getMqttPort() {
  reportSummary summary = this->reportEntry(parameter::MQTT_PORT);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::UINT16)) {
    this->setDefaults();
    return DEFAULT_MQTT_PORT;
  }
  return entry.getAnalog16();
}

std::string configuration::getMqttUsername() {
  reportSummary summary = this->reportEntry(parameter::MQTT_USERNAME);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::STRING)) {
    this->setDefaults();
    return DEFAULT_MQTT_USERNAME;
  }
  return entry.getString();
}

std::string configuration::getMqttPassword() {
  reportSummary summary = this->reportEntry(parameter::MQTT_PASSWORD);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::STRING)) {
    this->setDefaults();
    return DEFAULT_MQTT_PASSWORD;
  }
  return entry.getString();
}

guiState configuration::getGuiState() {
  reportSummary summary = this->reportEntry(parameter::GUI_STATE);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::UINT8)) {
    this->setDefaults();
    return (guiState)DEFAULT_GUI_STATE;
  }
  return (guiState)entry.getAnalog8();
}

ip configuration::getGuiIp() {
  reportSummary summary = this->reportEntry(parameter::GUI_IP);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::IP)) {
    this->setDefaults();
    return DEFAULT_GUI_IP;
  }
  return entry.getIp();
}

ip configuration::getGuiSubnet() {
  reportSummary summary = this->reportEntry(parameter::GUI_SUBNET);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::IP)) {
    this->setDefaults();
    return DEFAULT_GUI_SUBNET;
  }
  return entry.getIp();
}

ip configuration::getGuiGateway() {
  reportSummary summary = this->reportEntry(parameter::GUI_GATEWAY);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::IP)) {
    this->setDefaults();
    return DEFAULT_GUI_GATEWAY;
  }
  return entry.getIp();
}

uint16_t configuration::getGuiPort() {
  reportSummary summary = this->reportEntry(parameter::GUI_PORT);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::UINT8)) {
    this->setDefaults();
    return DEFAULT_GUI_PORT;
  }
  return entry.getAnalog8();
}

std::string configuration::getGuiPassword() {
  reportSummary summary = this->reportEntry(parameter::GUI_PASSWORD);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::STRING)) {
    this->setDefaults();
    return DEFAULT_GUI_PASSWORD;
  }
  return entry.getString();
}

uint8_t configuration::getMaxSatelliteSendAttempts() {
  reportSummary summary = this->reportEntry(parameter::MAX_SATELLITE_SEND_ATTEMPTS);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::UINT8)) {
    this->setDefaults();
    return DEFAULT_MAX_SATELLITE_SEND_ATTEMPTS;
  }
  return entry.getAnalog8();
}

uint8_t configuration::getMaxMessageQueueSize() {
  reportSummary summary = this->reportEntry(parameter::MAX_MESSAGE_QUEUE_SIZE);
  bool entryExists = summary.exists;
  entry entry = summary.resultEntry;
  if (not entryExists or not entry.isType(entryType::UINT8)) {
    this->setDefaults();
    return DEFAULT_MAX_MESSAGE_QUEUE_SIZE;
  }
  return entry.getAnalog8();
}