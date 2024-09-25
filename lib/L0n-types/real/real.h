#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class real {
 public:
  real();
  real(float value);
  real(std::vector<uint8_t> serializedReal);

  int32_t getValue();

  std::vector<uint8_t> serialize();
  bool isValidSerial(std::vector<uint8_t> serializedReal);
  void deserialize(std::vector<uint8_t> serializedReal);

 private:
  float value = 0;
};