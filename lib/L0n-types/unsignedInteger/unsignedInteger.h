#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class unsignedInteger {
 public:
  unsignedInteger();
  unsignedInteger(uint32_t value);
  unsignedInteger(std::vector<uint8_t> serializedUnsignedInteger);

  uint32_t getValue();

  std::vector<uint8_t> serialize();
  void deserialize(std::vector<uint8_t> serializedUnsignedInteger);
  static bool isValidSerial(std::vector<uint8_t> serializedUnsignedInteger);

 private:
  uint32_t value = 0;
};