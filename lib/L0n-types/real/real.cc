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
  if (isValidSerial(serializedReal)) {
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

bool real::isValidSerial(std::vector<uint8_t> serializedReal) {
  uint8_t serialSize = serializedReal.size();
  if (serialSize == 6) {
    entryType dataType = (entryType)serializedReal[0];
    uint8_t dataSize = serializedReal[1];
    if (dataSize == 4 and dataType == entryType::REAL) {
      return true;
    }
  }
  return false;
}