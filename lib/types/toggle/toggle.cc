#include <toggle/toggle.h>

// toggle class
toggle::toggle(bool value) { this->value = value; }
toggle::toggle(byteString_t bytes) { decode(bytes); }

bool toggle::getValue() { return this->value; }

byteString_t toggle::encode() {
  byteString_t bytes;
  bytes.push_back((uint8_t)entryType::TOGGLE);
  bytes.push_back(this->value);
  return bytes;
}

void toggle::decode(byteString_t bytes) {
  if (isValidToggle(bytes)) {
    this->value = bytes[1];
  };
}

// methods
bool isValidToggle(byteString_t bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 2) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::TOGGLE) {
    return false;
  }
  if (bytes[1] != 1 and bytes[1] != 0) {
    return false;
  }
  return true;
}