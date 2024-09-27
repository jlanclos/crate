#include <uinteger/uinteger.h>

// unsigned integer class
uinteger::uinteger(uint16_t value) { this->value = value; }
uinteger::uinteger(std::vector<uint8_t> bytes) {
  if (isValidUinteger(bytes)) {
    union {
      uint16_t integer;
      uint8_t bytes[2];
    } number;
    number.bytes[0] = bytes[2];
    number.bytes[1] = bytes[3];
    this->value = number.integer;
  };
}

uint16_t uinteger::getValue() { return this->value; }

std::vector<uint8_t> uinteger::getBytes() {
  union {
    uint16_t integer;
    uint8_t bytes[2];
  } number;
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 2;
  number.integer = this->value;
  bytes.push_back((uint8_t)entryType::UINTEGER);
  bytes.push_back(dataSize);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  return bytes;
}

// methods
bool isValidUinteger(std::vector<uint8_t> bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 4) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::UINTEGER) {
    return false;
  }
  if (bytes[1] != 2) {
    return false;
  }
  return true;
}