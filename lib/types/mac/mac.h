#pragma once

#include <types.h>

class mac : public type {
 public:
  mac(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4, uint8_t octet5, uint8_t octet6);
  mac(string_t macString);
  mac(byteString_t bytes);

  macArray_t getArray();
  string_t getString();
  uint8_t getOctet1();
  uint8_t getOctet2();
  uint8_t getOctet3();
  uint8_t getOctet4();
  uint8_t getOctet5();
  uint8_t getOctet6();

  byteString_t encode() override;
  void decode(byteString_t bytes) override;

 private:
  macArray_t value = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};;
};

static bool isValidMac(byteString_t bytes);