#include <sinteger/sinteger.h>

// sinteger class
sinteger::sinteger(int8_t value) { this->value = value; }
sinteger::sinteger(std::vector<uint8_t> bytes) {
  if (isValidSinteger(bytes)) {
    union {
      int8_t sinteger;
      uint8_t bytes[1];
    } number;
    number.bytes[0] = bytes[2];
    this->value = number.sinteger;
  };
  ;
}

int8_t sinteger::getValue() { return this->value; }

std::vector<uint8_t> sinteger::getBytes() {
  union {
    int8_t sinteger;
    uint8_t bytes[1];
  } number;
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 1;
  number.sinteger = this->value;
  bytes.push_back((uint8_t)entryType::SINTEGER);
  bytes.push_back(dataSize);
  bytes.push_back(number.bytes[0]);
  return bytes;
}

// methods
bool isValidSinteger(std::vector<uint8_t> bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 3) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::SINTEGER) {
    return false;
  }
  if (bytes[1] != 1) {
    return false;
  }
  return true;
}