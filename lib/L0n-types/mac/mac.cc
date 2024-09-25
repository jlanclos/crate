#include <mac/mac.h>

// mac class
mac::mac() { this->value = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; }
mac::mac(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4, uint8_t octet5, uint8_t octet6) {
  this->value = {octet1, octet2, octet3, octet4, octet5, octet6};
}
mac::mac(std::string macString) {
  std::array<uint8_t, 6> macBytes;
  if (sscanf(macString.c_str(), "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX", &macBytes[0], &macBytes[1], &macBytes[2],
             &macBytes[3], &macBytes[4], &macBytes[5]) == 6) {
    this->value = macBytes;
  } else {
    this->value = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  }
}
mac::mac(std::vector<uint8_t> serializedMac) { deserialize(serializedMac); }

std::array<uint8_t, 6> mac::getArray() { return this->value; }

std::string mac::getString() {
  char hexCharBytes[18];
  sprintf(hexCharBytes, "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX", this->value[0], this->value[1], this->value[2],
          this->value[3], this->value[4], this->value[5]);
  std::string macString = hexCharBytes;
  return macString;
}

uint8_t mac::getOctet1() { return this->value[0]; }

uint8_t mac::getOctet2() { return this->value[1]; }

uint8_t mac::getOctet3() { return this->value[2]; }

uint8_t mac::getOctet4() { return this->value[3]; }

uint8_t mac::getOctet5() { return this->value[4]; }

uint8_t mac::getOctet6() { return this->value[5]; }

std::vector<uint8_t> mac::serialize() {
  std::vector<uint8_t> bytes;
  bytes.push_back((uint8_t)entryType::MAC);
  bytes.push_back(6);
  bytes.push_back(this->value[0]);
  bytes.push_back(this->value[1]);
  bytes.push_back(this->value[2]);
  bytes.push_back(this->value[3]);
  bytes.push_back(this->value[4]);
  bytes.push_back(this->value[5]);
  return bytes;
}

void mac::deserialize(std::vector<uint8_t> serializedMac) {
  if (isValidMac(serializedMac)) {
    this->value = {serializedMac[2], serializedMac[3], serializedMac[4],
                   serializedMac[5], serializedMac[6], serializedMac[7]};
  }
}

// methods
bool isValidMac(std::vector<uint8_t> serializedMac) {
  uint32_t dataSize = serializedMac.size();
  if (dataSize != 8) {
    return false;
  }
  if ((entryType)serializedMac[0] != entryType::MAC) {
    return false;
  }
  if (serializedMac[1] != 6) {
    return false;
  }
  return true;
}