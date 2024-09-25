#include <string/string.h>

// string class
string::string() { this->value = false; }
string::string(std::string value) { this->value = value; }
string::string(std::vector<uint8_t> serializedBoolean) { deserialize(serializedBoolean); }

std::string string::getValue() { return this->value; }

std::vector<uint8_t> string::serialize() {
  uint32_t dataSize = this->value.length();
  std::vector<uint8_t> bytes;
  bytes.push_back((uint8_t)entryType::STRING);
  for (uint8_t i = 0; i < 4; i++) {
    bytes.push_back(dataSize >> (i * 8));
  }
  for (uint32_t i = 0; i < dataSize; i++) {
    bytes.push_back(this->value[i]);
  }
  return bytes;
}

bool string::isValidSerial(std::vector<uint8_t> serializedString) {
  uint8_t serialSize = serializedString.size();
  if (serialSize >= 3) {
    entryType dataType = (entryType)serializedString[0];
    uint32_t dataSize = 0;
    for (uint8_t i = 0; i < 4; i++) {
      dataSize |= serializedString[1 + i] << (i * 8);
    }
    if (dataType == entryType::STRING) {
      return true;
    }
  }
  return false;
}

void string::deserialize(std::vector<uint8_t> serializedString) {
  if (isValidSerial(serializedString)) {
    std::string value = "";
    uint32_t dataSize = 0;
    for (uint8_t i = 0; i < 4; i++) {
      dataSize |= serializedString[1 + i] << (i * 8);
    }
    for (uint32_t i = 0; i < dataSize; i++) {
      value += serializedString[5 + i];
    }
    this->value = value;
  };
}