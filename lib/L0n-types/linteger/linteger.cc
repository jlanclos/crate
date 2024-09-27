#include <linteger/linteger.h>

// linteger class
linteger::linteger(int32_t value) { this->value = value; }
linteger::linteger(std::vector<uint8_t> bytes) {
  if (isValidLinteger(bytes)) {
    union {
      int32_t linteger;
      uint8_t bytes[4];
    } number;
    number.bytes[0] = bytes[2];
    number.bytes[1] = bytes[3];
    number.bytes[2] = bytes[4];
    number.bytes[3] = bytes[5];
    this->value = number.linteger;
  };
}

int32_t linteger::getValue() { return this->value; }

std::vector<uint8_t> linteger::getBytes() {
  union {
    int32_t linteger;
    uint8_t bytes[4];
  } number;
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 4;
  number.linteger = this->value;
  bytes.push_back((uint8_t)entryType::LINTEGER);
  bytes.push_back(dataSize);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  bytes.push_back(number.bytes[2]);
  bytes.push_back(number.bytes[3]);
  return bytes;
}

// method
bool isValidLinteger(std::vector<uint8_t> bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 6) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::LINTEGER) {
    return false;
  }
  if (bytes[1] != 4) {
    return false;
  }
  return true;
}