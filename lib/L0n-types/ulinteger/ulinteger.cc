#include <ulinteger/ulinteger.h>

// unsigned long class
ulinteger::ulinteger() { this->value = 0; }
ulinteger::ulinteger(uint32_t value) { this->value = value; }
ulinteger::ulinteger(std::vector<uint8_t> serializedUnsignedLong) { deserialize(serializedUnsignedLong); }

uint32_t ulinteger::getValue() { return this->value; }

std::vector<uint8_t> ulinteger::serialize() {
  union {
    uint32_t ulinteger;
    uint8_t bytes[4];
  } number;
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 4;
  number.ulinteger = this->value;
  bytes.push_back((uint8_t)entryType::ULINTEGER);
  bytes.push_back(dataSize);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  bytes.push_back(number.bytes[2]);
  bytes.push_back(number.bytes[3]);
  return bytes;
}

void ulinteger::deserialize(std::vector<uint8_t> serializedUnsignedLong) {
  if (isValidSerial(serializedUnsignedLong)) {
    union {
      uint32_t ulinteger;
      uint8_t bytes[4];
    } number;
    number.bytes[0] = serializedUnsignedLong[2];
    number.bytes[1] = serializedUnsignedLong[3];
    number.bytes[2] = serializedUnsignedLong[4];
    number.bytes[3] = serializedUnsignedLong[5];
    this->value = number.ulinteger;
  };
}

bool ulinteger::isValidSerial(std::vector<uint8_t> serializedUnsignedLong) {
  uint8_t serialSize = serializedUnsignedLong.size();
  if (serialSize == 6) {
    entryType dataType = (entryType)serializedUnsignedLong[0];
    uint8_t dataSize = serializedUnsignedLong[1];
    if (dataSize == 4 and dataType == entryType::ULINTEGER) {
      return true;
    }
  }
  return false;
}