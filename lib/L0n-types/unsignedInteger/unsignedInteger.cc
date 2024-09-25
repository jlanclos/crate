#include <unsignedInteger/unsignedInteger.h>

// unsigned integer class
unsignedInteger::unsignedInteger() { this->value = 0; }
unsignedInteger::unsignedInteger(uint32_t value) { this->value = value; }
unsignedInteger::unsignedInteger(std::vector<uint8_t> serializedUnsignedInteger) {
  deserialize(serializedUnsignedInteger);
}

uint32_t unsignedInteger::getValue() { return this->value; }

std::vector<uint8_t> unsignedInteger::serialize() {
  union {
    uint32_t integer;
    uint8_t bytes[4];
  } number;
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 4;
  number.integer = this->value;
  bytes.push_back((uint8_t)entryType::UNSIGNED_INTEGER);
  bytes.push_back(dataSize);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  bytes.push_back(number.bytes[2]);
  bytes.push_back(number.bytes[3]);
  return bytes;
}

void unsignedInteger::deserialize(std::vector<uint8_t> serializedUnsignedInteger) {
  if (isValidSerial(serializedUnsignedInteger)) {
    union {
      uint32_t integer;
      uint8_t bytes[4];
    } number;
    number.bytes[0] = serializedUnsignedInteger[2];
    number.bytes[1] = serializedUnsignedInteger[3];
    number.bytes[2] = serializedUnsignedInteger[4];
    number.bytes[3] = serializedUnsignedInteger[5];
    this->value = number.integer;
  };
}

bool unsignedInteger::isValidSerial(std::vector<uint8_t> serializedUnsignedInteger) {
  uint8_t serialSize = serializedUnsignedInteger.size();
  if (serialSize == 6) {
    entryType dataType = (entryType)serializedUnsignedInteger[0];
    uint8_t dataSize = serializedUnsignedInteger[1];
    if (dataSize == 4 and dataType == entryType::UNSIGNED_INTEGER) {
      return true;
    }
  }
  return false;
}