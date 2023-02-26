#include "msg.h"

// message class
message::message() {
  this->idTyp = idType::UNDEFINED;
  this->payload.clear();
}

idType message::getIdTyp() { return this->idTyp; }

mac message::getIdAdd() { return this->idAdd; }

std::vector<dataEntry> message::getPayload() { return this->payload; }

void message::setIdTyp(idType newIdTyp) { this->idTyp = newIdTyp; }

void message::setIdAdd(mac newIdAdd) { this->idAdd = newIdAdd; }

void message::setPayload(std::vector<dataEntry> newPayload) { this->payload = newPayload; }

void message::fromString(const std::string& stringIn) {
  this->readIdTyp(stringIn);
  this->readIdAdd(stringIn);
  this->readPayload(stringIn, findDataIndicies(stringIn));
}

std::string message::toString() {
  std::string stringResult;
  stringResult += uint8tToString((uint8_t)this->idTyp);
  for (uint8_t i = 0; i < this->idAdd.getArray().size(); i++) {
    stringResult += uint8tToString(this->idAdd.getArray()[i]);
  }
  for (uint8_t j = 0; j < this->payload.size(); j++) {
    stringResult += "#";
    stringResult += uint8tToString(this->payload[j].getIdTgt());
    for (uint8_t k = 0; k < this->payload[j].getData().size(); k++) {
      stringResult += uint8tToString(this->payload[j].getData()[k]);
    }
  }
  return stringResult;
}

void message::readIdTyp(const std::string& messageString) {
  this->idTyp = idType::UNDEFINED;
  if (messageString.length() >= 14) {
    char typBytes[2] = {messageString[0], messageString[1]};
    sscanf(typBytes, "%02hhX", (uint8_t*)&this->idTyp);
  }
}

void message::readIdAdd(const std::string& messageString) {
  if (messageString.length() >= 14) {
    char addBytes[12];
    for (uint8_t i = 0; i < 12; i++) {
      addBytes[i] = messageString[i + 2];
    }
    std::array<uint8_t, 6> tempAddResult;
    if (sscanf(addBytes, "%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX", &tempAddResult[0],
               &tempAddResult[1], &tempAddResult[2], &tempAddResult[3], &tempAddResult[4],
               &tempAddResult[5]) == 6) {
      this->idAdd = mac(tempAddResult[0], tempAddResult[1], tempAddResult[2], tempAddResult[3],
                        tempAddResult[4], tempAddResult[5]);
    }
  }
}

void message::readPayload(const std::string& messageString, std::vector<uint8_t> dataIndicies) {
  this->payload.clear();
  if (dataIndicies.size() > 0) {
    for (uint8_t i = 0; i < dataIndicies.size(); i++) {
      uint8_t dataLength;
      if (i == dataIndicies.size() - 1) {
        dataLength = messageString.length() - dataIndicies[i] - 1;
      } else {
        dataLength = dataIndicies[i + 1] - dataIndicies[i] - 1;
      }
      if (dataLength >= 4 && dataLength % 2 == 0) {
        dataEntry packetData;
        uint8_t idTgtResult;
        std::vector<uint8_t> dataResult;
        char tgtBytes[2] = {messageString[dataIndicies[i] + 1], messageString[dataIndicies[i] + 2]};
        sscanf(tgtBytes, "%02hhX", &idTgtResult);
        packetData.setIdTgt(idTgtResult);
        for (uint8_t j = dataIndicies[i] + 3; j < dataIndicies[i] + 3 + dataLength - 2; j += 2) {
          char dataBytes[2] = {messageString[j], messageString[j + 1]};
          uint8_t dataByte;
          sscanf(dataBytes, "%02hhX", &dataByte);
          dataResult.push_back(dataByte);
        }
        packetData.setData(dataResult);
        this->payload.push_back(packetData);
      }
    }
  }
}

// messageQueue class
messageQueue::messageQueue() { this->queue.clear(); }

void messageQueue::purge() { this->queue.clear(); }

std::pair<operationStatus, message> messageQueue::read() {
  std::pair<operationStatus, message> readResult;
  readResult.first = operationStatus::FAIL;
  if (this->queue.size() > 0) {
    readResult.first = operationStatus::SUCCESS;
    readResult.second = this->queue.back();
  }
  return readResult;
}

void messageQueue::pop() { this->queue.pop_back(); }

void messageQueue::push(idType idTyp, mac idAdd, std::vector<dataEntry> payload) {
  message newMessage;
  newMessage.setIdTyp(idTyp);
  newMessage.setIdAdd(idAdd);
  newMessage.setPayload(payload);
  this->queue.insert(this->queue.begin(), newMessage);
}

void messageQueue::push(message messageIn) { this->queue.insert(this->queue.begin(), messageIn); }

// utility functions
std::vector<uint8_t> findDataIndicies(const std::string& stringIn) {
  std::vector<uint8_t> flagIndicies;
  if (stringIn.length() >= 17) {
    for (uint8_t i = 14; i < stringIn.length(); i++) {
      if (stringIn[i] == '#') {
        flagIndicies.push_back(i);
      }
    }
  }
  return flagIndicies;
}

std::string uint8tToString(uint8_t valueIn) {
  char hexBytes[2];
  sprintf(hexBytes, "%02X", valueIn);
  std::string stringResult = hexBytes;
  return stringResult;
}