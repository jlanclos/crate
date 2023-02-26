#include <message.h>

// message class
message::message() {
  this->idTyp = idType::UNDEFINED;
  this->idAdd = mac();
  this->payload.clear();
}
message::message(std::vector<uint8_t> messageRaw) { this->fromRaw(messageRaw); }

idType message::getIdTyp() { return this->idTyp; }

mac message::getIdAdd() { return this->idAdd; }

std::vector<entry> message::getPayload() { return this->payload; }

void message::setIdTyp(idType newIdTyp) { this->idTyp = newIdTyp; }

void message::setIdAdd(mac newIdAdd) { this->idAdd = newIdAdd; }

void message::setPayload(std::vector<entry> newPayload) { this->payload = newPayload; }

std::vector<uint8_t> message::toRaw() {
  std::vector<uint8_t> messageRaw;
  messageRaw.push_back((uint8_t)getIdTyp());
  std::array<uint8_t, 6> macArray = getIdAdd().getArray();
  for (uint8_t i = 0; i < macArray.size(); i++) {
    messageRaw.push_back(macArray[i]);
  }
  std::vector<entry> payload = getPayload();
  uint8_t payloadEntryCount = payload.size();
  messageRaw.push_back(payloadEntryCount);
  for (uint16_t i = 0; i < payloadEntryCount; i++) {
    std::vector<uint8_t> entryData = payload[i].getData();
    messageRaw.push_back(payload[i].getIdTgt());
    messageRaw.push_back((uint8_t)payload[i].getIdEntryType());
    uint8_t entryDataSize = payload[i].getDataSize();
    messageRaw.push_back(entryDataSize);
    for (uint16_t j = 0; j < entryDataSize; j++) {
      messageRaw.push_back(entryData[j]);
    }
  }
  return messageRaw;
}

void message::fromRaw(const std::vector<uint8_t>& messageRaw) {
  std::vector<entry> payload;
  setIdTyp(idType::UNDEFINED);
  setIdAdd(mac());
  setPayload(payload);
  if (messageRaw.size() >= 8) {
    uint16_t iterator = 0;
    setIdTyp((idType)messageRaw[iterator]);
    iterator++;
    std::array<uint8_t, 6> macArray;
    for (uint8_t i = 0; i < macArray.size(); i++) {
      macArray[i] = messageRaw[iterator];
      iterator++;
    }
    mac messageMac(macArray[0], macArray[1], macArray[2], macArray[3], macArray[4], macArray[5]);
    setIdAdd(messageMac);
    uint8_t payloadEntryCount = messageRaw[iterator];
    iterator++;
    for (uint16_t i = 0; i < payloadEntryCount; i++) {
      uint8_t idTgt = messageRaw[iterator];
      entry entry(idTgt);
      iterator++;
      entry.setIdEntryType((entryType)messageRaw[iterator]);
      iterator++;
      uint8_t entryDataSize = messageRaw[iterator];
      std::vector<uint8_t> entryData;
      for (uint16_t j = 0; j < entryDataSize; j++) {
        entryData.push_back(messageRaw[iterator]);
        iterator++;
      }
      entry.setData(entryData);
      payload.push_back(entry);
    }
    setPayload(payload);
  }
}

// messageQueue class
messageQueue::messageQueue() { this->queue.clear(); }

void messageQueue::purge() { this->queue.clear(); }

messageReadSummary messageQueue::read() {
  messageReadSummary summary;
  summary.success = false;
  if (this->queue.size() > 0) {
    summary.success = true;
    summary.message = this->queue.back();
  }
  return summary;
}

void messageQueue::pop() { this->queue.pop_back(); }

void messageQueue::push(idType idTyp, mac idAdd, std::vector<entry> payload) {
  message newMessage;
  newMessage.setIdTyp(idTyp);
  newMessage.setIdAdd(idAdd);
  newMessage.setPayload(payload);
  this->queue.insert(this->queue.begin(), newMessage);
}

void messageQueue::push(message messageIn) { this->queue.insert(this->queue.begin(), messageIn); }

// utility functions
std::string uint8tToString(uint8_t valueIn) {
  char hexBytes[2];
  sprintf(hexBytes, "%02X", valueIn);
  std::string stringResult = hexBytes;
  return stringResult;
}