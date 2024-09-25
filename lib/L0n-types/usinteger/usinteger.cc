#include <usinteger/usinteger.h>

// unsigned integer class
usinteger::usinteger() { this->value = 0; }
usinteger::usinteger(uint8_t value) { this->value = value; }
usinteger::usinteger(std::vector<uint8_t> serializedUsinteger) { deserialize(serializedUsinteger); }

uint8_t usinteger::getValue() { return this->value; }

std::vector<uint8_t> usinteger::serialize() {
  union {
    uint8_t integer;
    uint8_t bytes[2];
  } number;
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 1;
  number.integer = this->value;
  bytes.push_back((uint8_t)entryType::USINTEGER);
  bytes.push_back(dataSize);
  bytes.push_back(number.bytes[0]);
  return bytes;
}

void usinteger::deserialize(std::vector<uint8_t> serializedUsinteger) {
  if (isValidUsinteger(serializedUsinteger)) {
    union {
      uint8_t integer;
      uint8_t bytes[2];
    } number;
    number.bytes[0] = serializedUsinteger[2];
    this->value = number.integer;
  };
}

// methods
bool isValidUsinteger(std::vector<uint8_t> serializedUsinteger) {
  uint32_t dataSize = serializedUsinteger.size();
  if (dataSize != 3) {
    return false;
  }
  if ((entryType)serializedUsinteger[0] != entryType::USINTEGER) {
    return false;
  }
  if (serializedUsinteger[1] != 1) {
    return false;
  }
  return true;
}