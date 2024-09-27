#include <integer/integer.h>

// integer class
integer::integer(int16_t value) { this->value = value; }
integer::integer(std::vector<uint8_t> bytes) {
  if (isValidInteger(bytes)) {
    union {
      int16_t integer;
      uint8_t bytes[2];
    } number;
    number.bytes[0] = bytes[2];
    number.bytes[1] = bytes[3];
    this->value = number.integer;
  };
}

int16_t integer::getValue() { return this->value; }

std::vector<uint8_t> integer::getBytes() {
  union {
    int16_t integer;
    uint8_t bytes[2];
  } number;
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 2;
  number.integer = this->value;
  bytes.push_back((uint8_t)entryType::INTEGER);
  bytes.push_back(dataSize);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  return bytes;
}

// methods
bool isValidInteger(std::vector<uint8_t> bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 4) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::INTEGER) {
    return false;
  }
  if (bytes[1] != 2) {
    return false;
  }
  return true;
}