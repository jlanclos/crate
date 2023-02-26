#include "def.h"

// mac class
mac::mac() { this->value = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; }
mac::mac(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4, uint8_t octet5,
         uint8_t octet6) {
  this->value = {octet1, octet2, octet3, octet4, octet5, octet6};
}

std::array<uint8_t, 6> mac::getArray() { return this->value; }

// ip class
ip::ip() { this->value = {0, 0, 0, 0}; }
ip::ip(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4) {
  this->value = {octet1, octet2, octet3, octet4};
}

std::array<uint8_t, 4> ip::getArray() { return this->value; }

// dataEntry class
dataEntry::dataEntry() { this->idTgt = 0x00; }
dataEntry::dataEntry(uint8_t idTgt) { this->idTgt = idTgt; }

void dataEntry::setIdTgt(uint8_t newIdTgt) { this->idTgt = newIdTgt; }

uint8_t dataEntry::getIdTgt() { return this->idTgt; }

uint8_t dataEntry::getDataSize() { return this->data.size(); }

void dataEntry::setData(std::vector<uint8_t> newData) { this->data = newData; }

std::vector<uint8_t> dataEntry::getData() { return this->data; }

void dataEntry::pushDigital(bool newValue) {
  std::vector<uint8_t> newData;
  newData.push_back(newValue);
  this->setData(newData);
}

std::pair<operationStatus, bool> dataEntry::pullDigital() {
  std::pair<operationStatus, bool> readResult;
  readResult.first = operationStatus::FAIL;
  readResult.second = false;
  if (this->data.size() == 1) {
    if (this->data[0] == true || this->data[0] == false) {
      readResult.second = this->data[0];
      readResult.first = operationStatus::SUCCESS;
    }
  }
  return readResult;
}

void dataEntry::pushAnalogUInt8(uint8_t newState) {
  std::vector<uint8_t> newData;
  for (uint8_t i = 0; i < 1; i++) {
    newData.push_back(newState >> (i * 8));
  }
  this->setData(newData);
}

std::pair<operationStatus, uint8_t> dataEntry::pullAnalogUInt8() {
  std::pair<operationStatus, uint8_t> readResult;
  readResult.first = operationStatus::FAIL;
  readResult.second = 0;
  if (this->data.size() == 1) {
    for (uint8_t i = 0; i < 1; i++) {
      readResult.second |= this->data[i] << (i * 8);
    }
    readResult.first = operationStatus::SUCCESS;
  }
  return readResult;
}

void dataEntry::pushAnalogUInt16(uint16_t newState) {
  std::vector<uint8_t> newData;
  for (uint8_t i = 0; i < 2; i++) {
    newData.push_back(newState >> (i * 8));
  }
  this->setData(newData);
}

std::pair<operationStatus, uint16_t> dataEntry::pullAnalogUInt16() {
  std::pair<operationStatus, uint16_t> readResult;
  readResult.first = operationStatus::FAIL;
  readResult.second = 0;
  if (this->data.size() == 2) {
    for (uint8_t i = 0; i < 2; i++) {
      readResult.second |= this->data[i] << (i * 8);
    }
    readResult.first = operationStatus::SUCCESS;
  }
  return readResult;
}

void dataEntry::pushAnalogUInt32(uint32_t newState) {
  std::vector<uint8_t> newData;
  for (uint8_t i = 0; i < 4; i++) {
    newData.push_back(newState >> (i * 8));
  }
  this->setData(newData);
}

std::pair<operationStatus, uint32_t> dataEntry::pullAnalogUInt32() {
  std::pair<operationStatus, uint32_t> readResult;
  readResult.first = operationStatus::FAIL;
  readResult.second = 0;
  if (this->data.size() == 4) {
    for (uint8_t i = 0; i < 4; i++) {
      readResult.second |= this->data[i] << (i * 8);
    }
    readResult.first = operationStatus::SUCCESS;
  }
  return readResult;
}

void dataEntry::pushString(std::string newValue) {
  std::vector<uint8_t> newData;
  for (uint8_t i = 0; i < newValue.length(); i++) {
    newData.push_back(newValue[i]);
  }
  this->setData(newData);
}

std::pair<operationStatus, std::string> dataEntry::pullString() {
  std::pair<operationStatus, std::string> readResult;
  readResult.second = "";
  for (uint8_t i = 0; i < this->data.size(); i++) {
    readResult.second += this->data[i];
  }
  readResult.first = operationStatus::SUCCESS;
  return readResult;
}

void dataEntry::pushMac(mac newState) {
  std::vector<uint8_t> newData;
  for (uint8_t i = 0; i < 6; i++) {
    newData.push_back(newState.getArray()[i]);
  }
  this->setData(newData);
}

std::pair<operationStatus, mac> dataEntry::pullMac() {
  std::pair<operationStatus, mac> readResult;
  readResult.first = operationStatus::FAIL;
  if (this->data.size() == 6) {
    std::array<uint8_t, 6> readMacArray;
    for (uint8_t i = 0; i < 6; i++) {
      readMacArray[i] = this->data[i];
    }
    mac readMac(readMacArray[0], readMacArray[1], readMacArray[2], readMacArray[3], readMacArray[4],
                readMacArray[5]);
    readResult.second = readMac;
    readResult.first = operationStatus::SUCCESS;
  }
  return readResult;
}

void dataEntry::pushIp(ip newState) {
  std::vector<uint8_t> newData;
  for (uint8_t i = 0; i < 4; i++) {
    newData.push_back(newState.getArray()[i]);
  }
  this->setData(newData);
}

std::pair<operationStatus, ip> dataEntry::pullIp() {
  std::pair<operationStatus, ip> readResult;
  readResult.first = operationStatus::FAIL;
  if (this->data.size() == 4) {
    std::array<uint8_t, 4> readIpArray;
    for (uint8_t i = 0; i < 4; i++) {
      readIpArray[i] = this->data[i];
    }
    ip readIp(readIpArray[0], readIpArray[1], readIpArray[2], readIpArray[3]);
    readResult.second = readIp;
    readResult.first = operationStatus::SUCCESS;
  }
  return readResult;
}

// utility functions
dataEntry createDigitalEntry(uint8_t idTgt, bool value) {
  dataEntry dataEntryResult(idTgt);
  dataEntryResult.pushDigital(value);
  return dataEntryResult;
}

dataEntry createAnalogUInt8Entry(uint8_t idTgt, uint8_t value) {
  dataEntry dataEntryResult(idTgt);
  dataEntryResult.pushAnalogUInt8(value);
  return dataEntryResult;
}

dataEntry createAnalogUInt16Entry(uint8_t idTgt, uint16_t value) {
  dataEntry dataEntryResult(idTgt);
  dataEntryResult.pushAnalogUInt16(value);
  return dataEntryResult;
}

dataEntry createAnalogUInt32Entry(uint8_t idTgt, uint32_t value) {
  dataEntry dataEntryResult(idTgt);
  dataEntryResult.pushAnalogUInt32(value);
  return dataEntryResult;
}

dataEntry createStringEntry(uint8_t idTgt, std::string value) {
  dataEntry dataEntryResult(idTgt);
  dataEntryResult.pushString(value);
  return dataEntryResult;
}

dataEntry createMacEntry(uint8_t idTgt, mac value) {
  dataEntry dataEntryResult(idTgt);
  dataEntryResult.pushMac(value);
  return dataEntryResult;
}

dataEntry createIpEntry(uint8_t idTgt, ip value) {
  dataEntry dataEntryResult(idTgt);
  dataEntryResult.pushIp(value);
  return dataEntryResult;
}