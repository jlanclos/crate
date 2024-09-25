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
  bool isValidSerial(std::vector<uint8_t> serializedUnsignedInteger);
  void deserialize(std::vector<uint8_t> serializedUnsignedInteger);

 private:
  uint32_t value = 0;
};