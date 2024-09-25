#include <real/real.h>

// real class
real::real() { this->value = false; }
real::real(float value) { this->value = value; }
real::real(std::vector<uint8_t> serializedReal) { deserialize(serializedReal); }

int32_t real::getValue() { return this->value; }

std::vector<uint8_t> real::serialize() {
  std::vector<uint8_t> bytes;
  uint32_t binaryValue = (uint32_t)this->value;
  uint8_t dataSize = 4;
  bytes.push_back((uint8_t)entryType::REAL);
  bytes.push_back(dataSize);
  for (uint8_t i = 0; i < dataSize; i++) {
    bytes.push_back(binaryValue >> (i * 8));
  }
  return bytes;
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

void real::deserialize(std::vector<uint8_t> serializedReal) {
  if (isValidSerial(serializedReal)) {
    uint32_t binaryValue = 0;
    uint8_t dataSize = 4;
    for (uint8_t i = 0; i < dataSize; i++) {
      binaryValue |= serializedReal[2 + i] << (i * 8);
    }
    this->value = (float)binaryValue;
  };
}