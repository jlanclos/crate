#include <boolean/boolean.h>

// boolean class
boolean::boolean(bool value) { this->value = value; }
boolean::boolean(std::vector<uint8_t> bytes) {
  if (isValidBoolean(bytes)) {
    this->value = bytes[2];
  };
}

bool boolean::getValue() { return this->value; }

std::vector<uint8_t> boolean::getBytes() {
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 1;
  bytes.push_back((uint8_t)entryType::BOOLEAN);
  bytes.push_back(dataSize);
  bytes.push_back(this->value);
  return bytes;
}

// methods
bool isValidBoolean(std::vector<uint8_t> bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 3) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::BOOLEAN) {
    return false;
  }
  if (bytes[1] != 1) {
    return false;
  }
  if (bytes[2] != 1 and bytes[2] != 0) {
    return false;
  }
  return true;
}