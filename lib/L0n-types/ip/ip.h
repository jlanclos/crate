#pragma once

#include <types.h>

class ip : public type {
 public:
  ip(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4);
  ip(string_t ipString);
  ip(byteString_t bytes);

  ipArray_t getArray();
  string_t getString();
  uint8_t getOctet1();
  uint8_t getOctet2();
  uint8_t getOctet3();
  uint8_t getOctet4();

  byteString_t encode() override;

 private:
  ipArray_t value;
};

static bool isValidIp(byteString_t bytes);