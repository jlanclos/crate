#include <mac.h>

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

std::array<uint8_t, 6> mac::getArray() { return this->value; }

std::string mac::getString() {
  char hexCharBytes[18];
  sprintf(hexCharBytes, "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX", this->value[0], this->value[1], this->value[2],
          this->value[3], this->value[4], this->value[5]);
  std::string macString = hexCharBytes;
  return macString;
}