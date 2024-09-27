#include <sinteger/sinteger.h>

// sinteger class
sinteger::sinteger(int8_t value) { this->value = value; }
sinteger::sinteger(std::vector<uint8_t> bytes) {
  if (isValidSinteger(bytes)) {
    this->value = bytes[1];
  };
  ;
}

int8_t sinteger::getValue() { return this->value; }

std::vector<uint8_t> sinteger::getBytes() {
  std::vector<uint8_t> bytes;
  bytes.push_back((uint8_t)entryType::SINTEGER);
  bytes.push_back(this->value);
  return bytes;
}

// methods
bool isValidSinteger(std::vector<uint8_t> bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 2) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::SINTEGER) {
    return false;
  }
  return true;
}