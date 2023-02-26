#include <entry.h>

// entry class
entry::entry() {
  this->id = 0;
  this->type = entryType::UNKNOWN;
}
entry::entry(uint8_t id) {
  this->id = id;
  this->type = entryType::UNKNOWN;
}
entry::entry(uint8_t id, entryType getType) {
  this->id = id;
  this->type = type;
}

void entry::setId(uint8_t newId) { this->id = newId; }

uint8_t entry::getId() { return this->id; }

void entry::setType(entryType newType) { this->type = newType; }

entryType entry::getType() { return this->type; }

uint8_t entry::getDataSize() { return this->data.size(); }

void entry::setData(std::vector<uint8_t> newData) {
  std::vector<uint8_t> updateData;
  for (uint16_t i = 0; i < newData.size(); i++) {
    updateData.push_back(newData[i]);
  }
  this->data = updateData;
}

std::vector<uint8_t> entry::getData() { return this->data; }

bool entry::isType(entryType typeExpected) {
  switch (typeExpected) {
    case entryType::DIGITAL:
      return this->data.size() == 1 && this->type == entryType::DIGITAL;
    case entryType::UINT8:
      return this->data.size() == 1 && this->type == entryType::UINT8;
    case entryType::UINT16:
      return this->data.size() == 2 && this->type == entryType::UINT16;
    case entryType::UINT32:
      return this->data.size() == 4 && this->type == entryType::UINT32;
    case entryType::STRING:
      return this->type == entryType::STRING;
    case entryType::MAC:
      return this->data.size() == 6 && this->type == entryType::MAC;
    case entryType::IP:
      return this->data.size() == 4 && this->type == entryType::IP;
    default:
      return false;
  }
}

void entry::setDigital(bool newValue) {
  std::vector<uint8_t> newData;
  newData.push_back(newValue);
  this->setType(entryType::DIGITAL);
  this->setData(newData);
}

bool entry::getDigital() {
  bool readResult;
  readResult = false;
  if (this->isType(entryType::DIGITAL)) {
    if (this->data[0] == true || this->data[0] == false) {
      readResult = this->data[0];
    }
  }
  return readResult;
}

void entry::setAnalog8(uint8_t newValue) {
  std::vector<uint8_t> newData;
  for (uint8_t i = 0; i < 1; i++) {
    newData.push_back(newValue >> (i * 8));
  }
  this->setType(entryType::UINT8);
  this->setData(newData);
}

uint8_t entry::getAnalog8() {
  uint8_t readResult;
  readResult = 0;
  if (this->isType(entryType::UINT8)) {
    for (uint8_t i = 0; i < 1; i++) {
      readResult |= this->data[i] << (i * 8);
    }
  }
  return readResult;
}

void entry::setAnalog16(uint16_t newValue) {
  std::vector<uint8_t> newData;
  for (uint8_t i = 0; i < 2; i++) {
    newData.push_back(newValue >> (i * 8));
  }
  this->setType(entryType::UINT16);
  this->setData(newData);
}

uint16_t entry::getAnalog16() {
  uint16_t readResult;
  readResult = 0;
  if (this->isType(entryType::UINT16)) {
    for (uint8_t i = 0; i < 2; i++) {
      readResult |= this->data[i] << (i * 8);
    }
  }
  return readResult;
}

void entry::setAnalog32(uint32_t newValue) {
  std::vector<uint8_t> newData;
  for (uint8_t i = 0; i < 4; i++) {
    newData.push_back(newValue >> (i * 8));
  }
  this->setType(entryType::UINT32);
  this->setData(newData);
}

uint32_t entry::getAnalog32() {
  uint32_t readResult;
  readResult = 0;
  if (this->isType(entryType::UINT32)) {
    for (uint8_t i = 0; i < 4; i++) {
      readResult |= this->data[i] << (i * 8);
    }
  }
  return readResult;
}

void entry::setString(std::string newValue) {
  std::vector<uint8_t> newData;
  for (uint16_t i = 0; i < newValue.length(); i++) {
    newData.push_back(newValue[i]);
  }
  this->setType(entryType::STRING);
  this->setData(newData);
}

std::string entry::getString() {
  std::string readResult;
  readResult = "";
  if (this->isType(entryType::STRING)) {
    for (uint16_t i = 0; i < this->data.size(); i++) {
      readResult += this->data[i];
    }
  }
  return readResult;
}

void entry::setMac(mac newValue) {
  std::vector<uint8_t> newData;
  for (uint8_t i = 0; i < 6; i++) {
    newData.push_back(newValue.getArray()[i]);
  }
  this->setType(entryType::MAC);
  this->setData(newData);
}

mac entry::getMac() {
  mac readResult;
  if (this->isType(entryType::MAC)) {
    std::array<uint8_t, 6> readMacArray;
    for (uint8_t i = 0; i < 6; i++) {
      readMacArray[i] = this->data[i];
    }
    mac readMac(readMacArray[0], readMacArray[1], readMacArray[2], readMacArray[3], readMacArray[4], readMacArray[5]);
    readResult = readMac;
  }
  return readResult;
}

void entry::setIp(ip newValue) {
  std::vector<uint8_t> newData;
  for (uint8_t i = 0; i < 4; i++) {
    newData.push_back(newValue.getArray()[i]);
  }
  this->setType(entryType::IP);
  this->setData(newData);
}

ip entry::getIp() {
  ip readResult;
  if (this->isType(entryType::IP)) {
    std::array<uint8_t, 4> readIpArray;
    for (uint8_t i = 0; i < 4; i++) {
      readIpArray[i] = this->data[i];
    }
    ip readIp(readIpArray[0], readIpArray[1], readIpArray[2], readIpArray[3]);
    readResult = readIp;
  }
  return readResult;
}

// utility functions
entry createDigitalEntry(uint8_t id, bool value) {
  entry entryResult(id);
  entryResult.setDigital(value);
  return entryResult;
}

entry createAnalog8Entry(uint8_t id, uint8_t value) {
  entry entryResult(id);
  entryResult.setAnalog8(value);
  return entryResult;
}

entry createAnalog16Entry(uint8_t id, uint16_t value) {
  entry entryResult(id);
  entryResult.setAnalog16(value);
  return entryResult;
}

entry createAnalog32Entry(uint8_t id, uint32_t value) {
  entry entryResult(id);
  entryResult.setAnalog32(value);
  return entryResult;
}

entry createStringEntry(uint8_t id, std::string value) {
  entry entryResult(id);
  entryResult.setString(value);
  return entryResult;
}

entry createMacEntry(uint8_t id, mac value) {
  entry entryResult(id);
  entryResult.setMac(value);
  return entryResult;
}

entry createIpEntry(uint8_t id, ip value) {
  entry entryResult(id);
  entryResult.setIp(value);
  return entryResult;
}