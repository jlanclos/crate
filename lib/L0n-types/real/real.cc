#include <real/real.h>

// real class
real::real(float value) { this->value = value; }
real::real(encoding_t bytes) {
  if (isValidReal(bytes)) {
    union {
      float decimal;
      uint8_t bytes[4];
    } number;
    number.bytes[0] = bytes[1];
    number.bytes[1] = bytes[2];
    number.bytes[2] = bytes[3];
    number.bytes[3] = bytes[4];
    this->value = number.decimal;
  };
}

float real::getValue() { return this->value; }

encoding_t real::encode() {
  union {
    float decimal;
    uint8_t bytes[4];
  } number;
  encoding_t bytes;
  number.decimal = this->value;
  bytes.push_back((uint8_t)entryType::REAL);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  bytes.push_back(number.bytes[2]);
  bytes.push_back(number.bytes[3]);
  return bytes;
}

// methods
bool isValidReal(encoding_t bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 5) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::REAL) {
    return false;
  }
  return true;
}