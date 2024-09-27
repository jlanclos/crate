#pragma once

#include <stdint.h>
#include <types.h>

#include <array>
#include <string>
#include <vector>

class ip : public type {
 public:
  ip(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4);
  ip(std::string ipString);
  ip(std::vector<uint8_t> bytes);

  std::array<uint8_t, 4> getArray();
  std::string getString();
  uint8_t getOctet1();
  uint8_t getOctet2();
  uint8_t getOctet3();
  uint8_t getOctet4();

  std::vector<uint8_t> encode() override;

 private:
  std::array<uint8_t, 4> value;
};

static bool isValidIp(std::vector<uint8_t> bytes);