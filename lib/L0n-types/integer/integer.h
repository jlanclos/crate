#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class integer {
 public:
  integer();
  integer(int32_t value);
  integer(std::vector<uint8_t> serializedInteger);

  int32_t getValue();

  std::vector<uint8_t> serialize();
  void deserialize(std::vector<uint8_t> serializedInteger);
  static bool isValidSerial(std::vector<uint8_t> serializedInteger);

 private:
  int32_t value = 0;
};