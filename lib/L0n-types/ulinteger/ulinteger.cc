#include <ulinteger/ulinteger.h>

// unsigned long class
ulinteger::ulinteger(uint32_t value) { this->value = value; }
ulinteger::ulinteger(std::vector<uint8_t> bytes) {
  if (isValidUlinteger(bytes)) {
    union {
      uint32_t ulinteger;
      uint8_t bytes[4];
    } number;
    number.bytes[0] = bytes[2];
    number.bytes[1] = bytes[3];
    number.bytes[2] = bytes[4];
    number.bytes[3] = bytes[5];
    this->value = number.ulinteger;
  };
}

uint32_t ulinteger::getValue() { return this->value; }

std::vector<uint8_t> ulinteger::getBytes() {
  union {
    uint32_t ulinteger;
    uint8_t bytes[4];
  } number;
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 4;
  number.ulinteger = this->value;
  bytes.push_back((uint8_t)entryType::ULINTEGER);
  bytes.push_back(dataSize);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  bytes.push_back(number.bytes[2]);
  bytes.push_back(number.bytes[3]);
  return bytes;
}

// methods
bool isValidUlinteger(std::vector<uint8_t> bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 6) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::ULINTEGER) {
    return false;
  }
  if (bytes[1] != 4) {
    return false;
  }
  return true;
}