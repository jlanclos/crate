#include <entry.h>

// entry class
entry::entry() {}
entry::entry(uint16_t id) { this->id = id; }
entry::entry(std::vector<uint8_t> data) { this->data = data; }
entry::entry(uint16_t id, std::vector<uint8_t> data) {
  this->id = id;
  this->data = data;
}

void entry::setId(uint16_t newId) { this->id = newId; }

uint16_t entry::getId() { return this->id; }

entryType entry::getType() {
  uint32_t serialSize = this->data.size();
  if (serialSize == 0) {
    return entryType::UNKNOWN;
  }
  return (entryType)this->data[0];
}

void entry::setData(std::vector<uint8_t> newData) { this->data = newData; }

std::vector<uint8_t> entry::getData() { return this->data; }