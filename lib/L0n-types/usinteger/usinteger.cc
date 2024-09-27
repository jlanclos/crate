#include <usinteger/usinteger.h>

// unsigned integer class
usinteger::usinteger(uint8_t value) { this->value = value; }
usinteger::usinteger(encoding_t bytes) {
  if (isValidUsinteger(bytes)) {
    this->value = bytes[1];
  };
}

uint8_t usinteger::getValue() { return this->value; }

encoding_t usinteger::encode() {
  encoding_t bytes;
  bytes.push_back((uint8_t)entryType::USINTEGER);
  bytes.push_back(this->value);
  return bytes;
}

// methods
bool isValidUsinteger(encoding_t bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 2) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::USINTEGER) {
    return false;
  }
  return true;
}