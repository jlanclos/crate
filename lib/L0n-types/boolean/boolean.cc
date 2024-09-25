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

bool boolean::isValidSerial(std::vector<uint8_t> serializedBoolean) {
  uint8_t serialSize = serializedBoolean.size();
  if (serialSize == 3) {
    entryType dataType = (entryType)serializedBoolean[0];
    uint8_t dataSize = serializedBoolean[1];
    if (dataSize == 1 and dataType == entryType::BOOLEAN) {
      return true;
    }
  }
  return false;
}

void boolean::deserialize(std::vector<uint8_t> serializedBoolean) {
  if (isValidSerial(serializedBoolean)) {
    this->value = serializedBoolean[2];
  };
}