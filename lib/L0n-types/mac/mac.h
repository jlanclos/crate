#pragma once

#include <stdint.h>
#include <types.h>

#include <array>
#include <string>
#include <vector>

class mac : public type {
 public:
  mac(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4, uint8_t octet5, uint8_t octet6);
  mac(std::string macString);
  mac(std::vector<uint8_t> bytes);

  std::array<uint8_t, 6> getArray();
  std::string getString();
  uint8_t getOctet1();
  uint8_t getOctet2();
  uint8_t getOctet3();
  uint8_t getOctet4();
  uint8_t getOctet5();
  uint8_t getOctet6();

  std::vector<uint8_t> getBytes() override;

 private:
  std::array<uint8_t, 6> value;
};

static bool isValidMac(std::vector<uint8_t> bytes);