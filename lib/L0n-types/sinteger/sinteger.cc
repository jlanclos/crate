#include <sinteger/sinteger.h>

// sinteger class
sinteger::sinteger(int8_t value) { this->value = value; }
sinteger::sinteger(byteString_t bytes) {
  if (isValidSinteger(bytes)) {
    this->value = bytes[1];
  };
  ;
}

int8_t sinteger::getValue() { return this->value; }

byteString_t sinteger::encode() {
  byteString_t bytes;
  bytes.push_back((uint8_t)entryType::SINTEGER);
  bytes.push_back(this->value);
  return bytes;
}

// methods
bool isValidSinteger(byteString_t bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 2) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::SINTEGER) {
    return false;
  }
  return true;
}