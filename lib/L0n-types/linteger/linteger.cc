#include <linteger/linteger.h>

// linteger class
linteger::linteger() { this->value = 0; }
linteger::linteger(int32_t value) { this->value = value; }
linteger::linteger(std::vector<uint8_t> serializedLinteger) { deserialize(serializedLinteger); }

int32_t linteger::getValue() { return this->value; }

std::vector<uint8_t> linteger::serialize() {
  union {
    int32_t linteger;
    uint8_t bytes[4];
  } number;
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 4;
  number.linteger = this->value;
  bytes.push_back((uint8_t)entryType::LINTEGER);
  bytes.push_back(dataSize);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  bytes.push_back(number.bytes[2]);
  bytes.push_back(number.bytes[3]);
  return bytes;
}

void linteger::deserialize(std::vector<uint8_t> serializedLinteger) {
  if (isValidSerial(serializedLinteger)) {
    union {
      int32_t linteger;
      uint8_t bytes[4];
    } number;
    number.bytes[0] = serializedLinteger[2];
    number.bytes[1] = serializedLinteger[3];
    number.bytes[2] = serializedLinteger[4];
    number.bytes[3] = serializedLinteger[5];
    this->value = number.linteger;
  };
}

bool linteger::isValidSerial(std::vector<uint8_t> serializedLinteger) {
  uint8_t serialSize = serializedLinteger.size();
  if (serialSize == 6) {
    entryType dataType = (entryType)serializedLinteger[0];
    uint8_t dataSize = serializedLinteger[1];
    if (dataSize == 4 and dataType == entryType::LINTEGER) {
      return true;
    }
  }
  return false;
}