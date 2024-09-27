#include <real/real.h>

// real class
real::real(float value) { this->value = value; }
real::real(std::vector<uint8_t> bytes) {
  if (isValidReal(bytes)) {
    union {
      float decimal;
      uint8_t bytes[4];
    } number;
    number.bytes[0] = bytes[2];
    number.bytes[1] = bytes[3];
    number.bytes[2] = bytes[4];
    number.bytes[3] = bytes[5];
    this->value = number.decimal;
  };
}

float real::getValue() { return this->value; }

std::vector<uint8_t> real::getBytes() {
  union {
    float decimal;
    uint8_t bytes[4];
  } number;
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 4;
  number.decimal = this->value;
  bytes.push_back((uint8_t)entryType::REAL);
  bytes.push_back(dataSize);
  bytes.push_back(number.bytes[0]);
  bytes.push_back(number.bytes[1]);
  bytes.push_back(number.bytes[2]);
  bytes.push_back(number.bytes[3]);
  return bytes;
}

// methods
bool isValidReal(std::vector<uint8_t> bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 6) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::REAL) {
    return false;
  }
  if (bytes[1] != 4) {
    return false;
  }
  return true;
}