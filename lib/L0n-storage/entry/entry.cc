#include <entry/entry.h>

// entry class
entry::entry(uint16_t id, type data) {
  this->id = id;
  this->bytes = data.encode();
}

uint16_t entry::getId() { return this->id; }

entryType entry::getType() { return (entryType)this->bytes[0]; }

std::vector<uint8_t> entry::getBytes() { return this->bytes; }