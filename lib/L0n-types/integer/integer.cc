#include <integer/integer.h>

// integer class
integer::integer() { this->value = 0; }
integer::integer(int32_t value) { this->value = value; }
integer::integer(std::vector<uint8_t> serializedInteger) { deserialize(serializedInteger); }

int32_t integer::getValue() { return this->value; }

std::vector<uint8_t> integer::serialize() {
  union {
    int32_t integer;
    uint8_t bytes[4];
  } number;
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 4;
  number.integer = this->value;
  bytes.push_back((uint8_t)entryType::INTEGER);
  bytes.push_back(dataSize);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  bytes.push_back(number.bytes[2]);
  bytes.push_back(number.bytes[3]);
  return bytes;
}

void integer::deserialize(std::vector<uint8_t> serializedInteger) {
  if (isValidSerial(serializedInteger)) {
    union {
      int32_t integer;
      uint8_t bytes[4];
    } number;
    number.bytes[0] = serializedInteger[2];
    number.bytes[1] = serializedInteger[3];
    number.bytes[2] = serializedInteger[4];
    number.bytes[3] = serializedInteger[5];
    this->value = number.integer;
  };
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