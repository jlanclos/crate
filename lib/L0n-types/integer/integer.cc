#include <integer/integer.h>

// integer class
integer::integer(int16_t value) { this->value = value; }
integer::integer(byteString_t bytes) {
  if (isValidInteger(bytes)) {
    union {
      int16_t integer;
      uint8_t bytes[2];
    } number;
    number.bytes[0] = bytes[1];
    number.bytes[1] = bytes[2];
    this->value = number.integer;
  };
}

int16_t integer::getValue() { return this->value; }

byteString_t integer::encode() {
  union {
    int16_t integer;
    uint8_t bytes[2];
  } number;
  byteString_t bytes;
  number.integer = this->value;
  bytes.push_back((uint8_t)entryType::INTEGER);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  return bytes;
}

// methods
bool isValidInteger(byteString_t bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 3) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::INTEGER) {
    return false;
  }
  return true;
}