#include <uinteger/uinteger.h>

// unsigned integer class
uinteger::uinteger(uint16_t value) { this->value = value; }
uinteger::uinteger(byteString_t bytes) {
  if (isValidUinteger(bytes)) {
    union {
      uint16_t integer;
      uint8_t bytes[2];
    } number;
    number.bytes[0] = bytes[1];
    number.bytes[1] = bytes[2];
    this->value = number.integer;
  };
}

uint16_t uinteger::getValue() { return this->value; }

byteString_t uinteger::encode() {
  union {
    uint16_t integer;
    uint8_t bytes[2];
  } number;
  byteString_t bytes;
  number.integer = this->value;
  bytes.push_back((uint8_t)entryType::UINTEGER);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  return bytes;
}

// methods
bool isValidUinteger(byteString_t bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 3) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::UINTEGER) {
    return false;
  }
  return true;
}