#include <ulinteger/ulinteger.h>

// unsigned long class
ulinteger::ulinteger(uint32_t value) { this->value = value; }
ulinteger::ulinteger(byteString_t bytes) {
  if (isValidUlinteger(bytes)) {
    union {
      uint32_t ulinteger;
      uint8_t bytes[4];
    } number;
    number.bytes[0] = bytes[1];
    number.bytes[1] = bytes[2];
    number.bytes[2] = bytes[3];
    number.bytes[3] = bytes[4];
    this->value = number.ulinteger;
  };
}

uint32_t ulinteger::getValue() { return this->value; }

byteString_t ulinteger::encode() {
  union {
    uint32_t ulinteger;
    uint8_t bytes[4];
  } number;
  byteString_t bytes;
  number.ulinteger = this->value;
  bytes.push_back((uint8_t)entryType::ULINTEGER);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  bytes.push_back(number.bytes[2]);
  bytes.push_back(number.bytes[3]);
  return bytes;
}

// methods
bool isValidUlinteger(byteString_t bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 5) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::ULINTEGER) {
    return false;
  }
  return true;
}