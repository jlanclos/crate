#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class integer {
 public:
  integer();
  integer(int16_t value);
  integer(std::vector<uint8_t> serializedInteger);

  int16_t getValue();

  std::vector<uint8_t> serialize();
  void deserialize(std::vector<uint8_t> serializedInteger);

 private:
  int16_t value = 0;
};

bool isValidInteger(std::vector<uint8_t> serializedInteger);