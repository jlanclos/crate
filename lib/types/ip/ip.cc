#include <ip/ip.h>

// ip class
ip::ip(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4) {
  this->value = {octet1, octet2, octet3, octet4};
}
ip::ip(string_t ipString) {
  ipArray_t ipBytes;
  if (sscanf(ipString.c_str(), "%hu.%hu.%hu.%hu", (short unsigned int*)&ipBytes[0], (short unsigned int*)&ipBytes[1],
             (short unsigned int*)&ipBytes[2], (short unsigned int*)&ipBytes[3]) == 4) {
    this->value = ipBytes;
  }
}
ip::ip(byteString_t bytes) { decode(bytes); }

ipArray_t ip::getArray() { return this->value; }

string_t ip::getString() {
  string_t ipString = "";
  ipString += std::to_string(this->value[0]);
  for (uint8_t i = 1; i < 4; i++) {
    ipString += ".";
    ipString += std::to_string(this->value[i]);
  }
  return ipString;
}

uint8_t ip::getOctet1() { return this->value[0]; }

uint8_t ip::getOctet2() { return this->value[1]; }

uint8_t ip::getOctet3() { return this->value[2]; }

uint8_t ip::getOctet4() { return this->value[3]; }

byteString_t ip::encode() {
  byteString_t bytes;
  bytes.push_back((uint8_t)entryType::IP);
  bytes.push_back(this->value[0]);
  bytes.push_back(this->value[1]);
  bytes.push_back(this->value[2]);
  bytes.push_back(this->value[3]);
  return bytes;
}

void ip::decode(byteString_t bytes) {
  if (isValidIp(bytes)) {
    this->value = {bytes[1], bytes[2], bytes[3], bytes[4]};
  }
}

// methods
bool isValidIp(byteString_t bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 5) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::IP) {
    return false;
  }
  return true;
}