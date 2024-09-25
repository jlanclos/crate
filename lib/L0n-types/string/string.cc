#include <string/string.h>

// string class
string::string() { this->value = ""; }
string::string(std::string value) { this->value = value; }
string::string(std::vector<uint8_t> serializedBoolean) { deserialize(serializedBoolean); }

std::string string::getValue() { return this->value; }

std::vector<uint8_t> string::serialize() {
  union {
    uint32_t integer;
    uint8_t bytes[4];
  } dataSize;
  std::vector<uint8_t> bytes;
  dataSize.integer = this->value.length();
  bytes.push_back((uint8_t)entryType::STRING);
  bytes.push_back(dataSize.bytes[0]);
  bytes.push_back(dataSize.bytes[1]);
  bytes.push_back(dataSize.bytes[2]);
  bytes.push_back(dataSize.bytes[3]);
  for (uint32_t i = 0; i < dataSize.integer; i++) {
    bytes.push_back(this->value[i]);
  }
  return bytes;
}

void string::deserialize(std::vector<uint8_t> serializedString) {
  if (isValidString(serializedString)) {
    union {
      uint32_t integer;
      uint8_t bytes[4];
    } dataSize;
    dataSize.bytes[0] = serializedString[1];
    dataSize.bytes[1] = serializedString[2];
    dataSize.bytes[2] = serializedString[3];
    dataSize.bytes[3] = serializedString[4];
    std::string value = "";
    for (uint32_t i = 0; i < dataSize.integer; i++) {
      value += serializedString[5 + i];
    }
    this->value = value;
  };
}

bool isValidString(std::vector<uint8_t> serializedString) {
  uint32_t dataSize = serializedString.size();
  if (dataSize < 5) {
    return false;
  }
  if ((entryType)serializedString[0] != entryType::STRING) {
    return false;
  }
  return true;
}
