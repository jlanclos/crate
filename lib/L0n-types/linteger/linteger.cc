#include <linteger/linteger.h>

// linteger class
linteger::linteger(int32_t value) { this->value = value; }
linteger::linteger(byteString_t bytes) {
  if (isValidLinteger(bytes)) {
    union {
      int32_t linteger;
      uint8_t bytes[4];
    } number;
    number.bytes[0] = bytes[1];
    number.bytes[1] = bytes[2];
    number.bytes[2] = bytes[3];
    number.bytes[3] = bytes[4];
    this->value = number.linteger;
  };
}

int32_t linteger::getValue() { return this->value; }

byteString_t linteger::encode() {
  union {
    int32_t linteger;
    uint8_t bytes[4];
  } number;
  byteString_t bytes;
  number.linteger = this->value;
  bytes.push_back((uint8_t)entryType::LINTEGER);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  bytes.push_back(number.bytes[2]);
  bytes.push_back(number.bytes[3]);
  return bytes;
}

// method
bool isValidLinteger(byteString_t bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 5) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::LINTEGER) {
    return false;
  }
  return true;
}