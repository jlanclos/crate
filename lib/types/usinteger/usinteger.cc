#include <usinteger/usinteger.h>

// unsigned integer class
usinteger::usinteger(uint8_t value) { this->value = value; }
usinteger::usinteger(byteString_t bytes) { decode(bytes); }

uint8_t usinteger::getValue() { return this->value; }

byteString_t usinteger::encode() {
  byteString_t bytes;
  bytes.push_back((uint8_t)entryType::USINTEGER);
  bytes.push_back(this->value);
  return bytes;
}

void usinteger::decode(byteString_t bytes) {
  if (isValidUsinteger(bytes)) {
    this->value = bytes[1];
  };
}

// methods
bool isValidUsinteger(byteString_t bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 2) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::USINTEGER) {
    return false;
  }
  return true;
}