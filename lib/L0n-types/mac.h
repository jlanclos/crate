#pragma once

#include <stdint.h>

#include <array>
#include <string>

class mac {
 public:
  mac();
  mac(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4, uint8_t octet5, uint8_t octet6);
  mac(std::string macString);

  std::array<uint8_t, 6> getArray();
  std::string getString();

 private:
  std::array<uint8_t, 6> value;
};