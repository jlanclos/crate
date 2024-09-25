#include <boolean/boolean.h>

// boolean class
boolean::boolean() { this->value = false; }
boolean::boolean(bool value) { this->value = value; }
boolean::boolean(std::vector<uint8_t> serializedBoolean) { deserialize(serializedBoolean); }

bool boolean::getValue() { return this->value; }

std::vector<uint8_t> boolean::serialize() {
  std::vector<uint8_t> bytes;
  uint8_t dataSize = 1;
  bytes.push_back((uint8_t)entryType::BOOLEAN);
  bytes.push_back(dataSize);
  bytes.push_back(this->value);
  return bytes;
}

void boolean::deserialize(std::vector<uint8_t> serializedBoolean) {
  if (isValidBoolean(serializedBoolean)) {
    this->value = serializedBoolean[2];
  };
}

// methods
bool isValidBoolean(std::vector<uint8_t> serializedBoolean) {
  uint32_t dataSize = serializedBoolean.size();
  if (dataSize != 3) {
    return false;
  }
  if ((entryType)serializedBoolean[0] != entryType::BOOLEAN) {
    return false;
  }
  if (serializedBoolean[1] != 1) {
    return false;
  }
  if (serializedBoolean[2] != 1 and serializedBoolean[2] != 0) {
    return false;
  }
  return true;
}