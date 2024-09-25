#include <uinteger/uinteger.h>

// unsigned integer class
uinteger::uinteger() { this->value = 0; }
uinteger::uinteger(uint16_t value) { this->value = value; }
uinteger::uinteger(std::vector<uint8_t> serializedUinteger) { deserialize(serializedUinteger); }

uint16_t uinteger::getValue() { return this->value; }

std::vector<uint8_t> uinteger::serialize() {
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

void uinteger::deserialize(std::vector<uint8_t> serializedUinteger) {
  if (isValidSerial(serializedUinteger)) {
    union {
      uint16_t integer;
      uint8_t bytes[2];
    } number;
    number.bytes[0] = serializedUinteger[2];
    number.bytes[1] = serializedUinteger[3];
    this->value = number.integer;
  };
}

bool uinteger::isValidSerial(std::vector<uint8_t> serializedUinteger) {
  uint8_t serialSize = serializedUinteger.size();
  if (serialSize == 4) {
    entryType dataType = (entryType)serializedUinteger[0];
    uint8_t dataSize = serializedUinteger[1];
    if (dataSize == 2 and dataType == entryType::UINTEGER) {
      return true;
    }
  }
  return false;
}