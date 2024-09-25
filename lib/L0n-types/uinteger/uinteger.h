#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class uinteger {
 public:
  uinteger();
  uinteger(uint16_t value);
  uinteger(std::vector<uint8_t> serializedUinteger);

  uint16_t getValue();

  std::vector<uint8_t> serialize();
  void deserialize(std::vector<uint8_t> serializedUinteger);

 private:
  uint16_t value = 0;
}; 

bool isValidUinteger(std::vector<uint8_t> serializedUinteger);