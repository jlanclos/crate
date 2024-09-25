#include <unsignedInteger/unsignedInteger.h>

// unsigned integer class
unsignedInteger::unsignedInteger() { this->value = false; }
unsignedInteger::unsignedInteger(uint32_t value) { this->value = value; }
unsignedInteger::unsignedInteger(std::vector<uint8_t> serializedUnsignedInteger) {
  deserialize(serializedUnsignedInteger);
}

uint32_t unsignedInteger::getValue() { return this->value; }

std::vector<uint8_t> unsignedInteger::serialize() {
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 4;
  bytes.push_back((uint8_t)entryType::UNSIGNED_INTEGER);
  bytes.push_back(dataSize);
  for (uint8_t i = 0; i < dataSize; i++) {
    bytes.push_back(this->value >> (i * 8));
  }
  return bytes;
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

void unsignedInteger::deserialize(std::vector<uint8_t> serializedUnsignedInteger) {
  if (isValidSerial(serializedUnsignedInteger)) {
    uint32_t value = 0;
    uint8_t dataSize = 4;
    for (uint8_t i = 0; i < dataSize; i++) {
      value |= serializedUnsignedInteger[2 + i] << (i * 8);
    }
    this->value = value;
  };
}