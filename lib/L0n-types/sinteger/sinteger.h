#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class sinteger {
 public:
  sinteger();
  sinteger(int8_t value);
  sinteger(std::vector<uint8_t> serializedInteger);

  int8_t getValue();

  std::vector<uint8_t> serialize();
  void deserialize(std::vector<uint8_t> serializedInteger);

 private:
  int8_t value = 0;
};

bool isValidSinteger(std::vector<uint8_t> serializedInteger);