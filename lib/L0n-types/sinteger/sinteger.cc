#include <sinteger/sinteger.h>

// sinteger class
sinteger::sinteger() { this->value = 0; }
sinteger::sinteger(int8_t value) { this->value = value; }
sinteger::sinteger(std::vector<uint8_t> serializedSinteger) { deserialize(serializedSinteger); }

int8_t sinteger::getValue() { return this->value; }

std::vector<uint8_t> sinteger::serialize() {
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

void sinteger::deserialize(std::vector<uint8_t> serializedSinteger) {
  if (isValidSinteger(serializedSinteger)) {
    union {
      int8_t sinteger;
      uint8_t bytes[1];
    } number;
    number.bytes[0] = serializedSinteger[2];
    this->value = number.sinteger;
  };
}

// methods
bool isValidSinteger(std::vector<uint8_t> serializedSinteger) {
  uint32_t dataSize = serializedSinteger.size();
  if (dataSize != 3) {
    return false;
  }
  if ((entryType)serializedSinteger[0] != entryType::SINTEGER) {
    return false;
  }
  if (serializedSinteger[1] != 1) {
    return false;
  }
  return true;
}