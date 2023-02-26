#pragma once

#include <stdint.h>

#include <array>
#include <string>

class ip {
 public:
  ip();
  ip(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4);
  ip(std::string ipString);

  std::array<uint8_t, 4> getArray();
  std::string getString();

 private:
  std::array<uint8_t, 4> value;
};