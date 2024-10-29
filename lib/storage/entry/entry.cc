#include <entry/entry.h>

// entry class
entry::entry() {}
entry::entry(uint16_t id, type &object) {
  this->id = id;
  this->bytes = object.encode();
}

uint16_t entry::getId() { return this->id; }

entryType entry::getType() { return (entryType)this->bytes[0]; }

byteString_t entry::getData() { return this->bytes; }