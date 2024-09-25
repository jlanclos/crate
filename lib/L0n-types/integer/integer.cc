#include <integer/integer.h>

// integer class
integer::integer() { this->value = false; }
integer::integer(int32_t value) { this->value = value; }
integer::integer(std::vector<uint8_t> serializedInteger) { deserialize(serializedInteger); }

int32_t integer::getValue() { return this->value; }

std::vector<uint8_t> integer::serialize() {
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 4;
  bytes.push_back((uint8_t)entryType::INTEGER);
  bytes.push_back(dataSize);
  for (uint8_t i = 0; i < dataSize; i++) {
    bytes.push_back(this->value >> (i * 8));
  }
  return bytes;
}

bool integer::isValidSerial(std::vector<uint8_t> serializedInteger) {
  uint8_t serialSize = serializedInteger.size();
  if (serialSize == 6) {
    entryType dataType = (entryType)serializedInteger[0];
    uint8_t dataSize = serializedInteger[1];
    if (dataSize == 4 and dataType == entryType::INTEGER) {
      return true;
    }
  }
  return false;
}

void integer::deserialize(std::vector<uint8_t> serializedInteger) {
  if (isValidSerial(serializedInteger)) {
    int32_t value = 0;
    uint8_t dataSize = 4;
    for (uint8_t i = 0; i < dataSize; i++) {
      value |= serializedInteger[2 + i] << (i * 8);
    }
    this->value = value;
  };
}