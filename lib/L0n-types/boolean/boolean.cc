#include <boolean/boolean.h>

// boolean class
boolean::boolean(bool value) { this->value = value; }
boolean::boolean(std::vector<uint8_t> bytes) {
  if (isValidBoolean(bytes)) {
    this->value = bytes[1];
  };
}

bool boolean::getValue() { return this->value; }

std::vector<uint8_t> boolean::encode() {
  std::vector<uint8_t> bytes;
  bytes.push_back((uint8_t)entryType::BOOLEAN);
  bytes.push_back(this->value);
  return bytes;
}

// methods
bool isValidBoolean(std::vector<uint8_t> bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 2) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::BOOLEAN) {
    return false;
  }
  if (bytes[1] != 1 and bytes[1] != 0) {
    return false;
  }
  return true;
}