#include <string/string.h>

// string class
string::string(string_t value) { this->value = value; }
string::string(byteString_t bytes) { decode(bytes); }

string_t string::getValue() { return this->value; }

byteString_t string::encode() {
  union {
    uint32_t integer;
    uint8_t bytes[4];
  } dataSize;
  byteString_t bytes;
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

void string::decode(byteString_t bytes) {
  if (isValidString(bytes)) {
    union {
      uint32_t integer;
      uint8_t bytes[4];
    } dataSize;
    dataSize.bytes[0] = bytes[1];
    dataSize.bytes[1] = bytes[2];
    dataSize.bytes[2] = bytes[3];
    dataSize.bytes[3] = bytes[4];
    string_t value = "";
    for (uint32_t i = 0; i < dataSize.integer; i++) {
      value += bytes[5 + i];
    }
    this->value = value;
  };
}

bool isValidString(byteString_t bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize < 5) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::STRING) {
    return false;
  }
  return true;
}
