#include <real/real.h>

// real class
real::real() { this->value = 0.0; }
real::real(float value) { this->value = value; }
real::real(std::vector<uint8_t> serializedReal) { deserialize(serializedReal); }

float real::getValue() { return this->value; }

std::vector<uint8_t> real::serialize() {
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

void real::deserialize(std::vector<uint8_t> serializedReal) {
  if (isValidReal(serializedReal)) {
    union {
      float decimal;
      uint8_t bytes[4];
    } number;
    number.bytes[0] = serializedReal[2];
    number.bytes[1] = serializedReal[3];
    number.bytes[2] = serializedReal[4];
    number.bytes[3] = serializedReal[5];
    this->value = number.decimal;
  };
}

// methods
bool isValidReal(std::vector<uint8_t> serializedReal) {
  uint32_t dataSize = serializedReal.size();
  if (dataSize != 6) {
    return false;
  }
  if ((entryType)serializedReal[0] != entryType::REAL) {
    return false;
  }
  if (serializedReal[1] != 4) {
    return false;
  }
  return true;
}