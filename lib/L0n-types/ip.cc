#include <ip.h>

// ip class
ip::ip() { this->value = {0, 0, 0, 0}; }
ip::ip(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4) {
  this->value = {octet1, octet2, octet3, octet4};
}
ip::ip(std::string ipString) {
  std::array<uint8_t, 4> ipBytes;
  if (sscanf(ipString.c_str(), "%hu.%hu.%hu.%hu", (short unsigned int*)&ipBytes[0], (short unsigned int*)&ipBytes[1],
             (short unsigned int*)&ipBytes[2], (short unsigned int*)&ipBytes[3]) == 4) {
    this->value = ipBytes;
  } else {
    this->value = {0, 0, 0, 0};
  }
}

std::array<uint8_t, 4> ip::getArray() { return this->value; }

std::string ip::getString() {
  std::string ipString = "";
  ipString += std::to_string(this->value[0]);
  for (uint8_t i = 1; i < 4; i++) {
    ipString += ".";
    ipString += std::to_string(this->value[i]);
  }
  return ipString;
}