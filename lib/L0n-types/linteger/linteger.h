#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class linteger {
 public:
  linteger();
  linteger(int32_t value);
  linteger(std::vector<uint8_t> serializedInteger);

  int32_t getValue();

  std::vector<uint8_t> serialize();
  void deserialize(std::vector<uint8_t> serializedInteger);
  static bool isValidSerial(std::vector<uint8_t> serializedInteger);

 private:
  int32_t value = 0;
};