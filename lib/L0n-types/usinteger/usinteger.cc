#include <usinteger/usinteger.h>

// unsigned integer class
usinteger::usinteger(uint8_t value) { this->value = value; }
usinteger::usinteger(std::vector<uint8_t> bytes) {
  if (isValidUsinteger(bytes)) {
    union {
      uint8_t integer;
      uint8_t bytes[2];
    } number;
    number.bytes[0] = bytes[2];
    this->value = number.integer;
  };
}

uint8_t usinteger::getValue() { return this->value; }

std::vector<uint8_t> usinteger::getBytes() {
  union {
    uint8_t integer;
    uint8_t bytes[2];
  } number;
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 1;
  number.integer = this->value;
  bytes.push_back((uint8_t)entryType::USINTEGER);
  bytes.push_back(dataSize);
  bytes.push_back(number.bytes[0]);
  return bytes;
}

// methods
bool isValidUsinteger(std::vector<uint8_t> bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 3) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::USINTEGER) {
    return false;
  }
  if (bytes[1] != 1) {
    return false;
  }
  return true;
}