#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class ulinteger {
 public:
  ulinteger();
  ulinteger(uint32_t value);
  ulinteger(std::vector<uint8_t> serializedUnsignedLong);

  uint32_t getValue();

  std::vector<uint8_t> serialize();
  void deserialize(std::vector<uint8_t> serializedUnsignedLong);
  
 private:
  uint32_t value = 0;
};

bool isValidUlinteger(std::vector<uint8_t> serializedUnsignedLong);