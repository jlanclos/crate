#include <entry/entry.h>

// entry class
entry::entry() {}
entry::entry(uint16_t id) { this->id = id; }
entry::entry(std::vector<uint8_t> data) {
  if (data.size() > 0) {
    this->type = (entryType)data[0];
  } else {
    this->type = entryType::UNKNOWN;
  }
  this->data = data;
}
entry::entry(uint16_t id, std::vector<uint8_t> data) {
  this->id = id;
  if (data.size() > 0) {
    this->type = (entryType)data[0];
  } else {
    this->type = entryType::UNKNOWN;
  }
  this->data = data;
}

void entry::setId(uint16_t newId) { this->id = newId; }

uint16_t entry::getId() { return this->id; }

entryType entry::getType() { return this->type; }

void entry::setData(std::vector<uint8_t> newData) {
  if (newData.size() > 0) {
    this->type = (entryType)data[0];
  } else {
    this->type = entryType::UNKNOWN;
  }
  this->data = newData;
}

std::vector<uint8_t> entry::getData() { return this->data; }

std::vector<uint8_t> entry::serialize() {}

void entry::deserialize(std::vector<uint8_t> serialEntry) {}