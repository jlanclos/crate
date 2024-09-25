#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class real {
 public:
  real();
  real(float value);
  real(std::vector<uint8_t> serializedReal);

  float getValue();

  std::vector<uint8_t> serialize();
  void deserialize(std::vector<uint8_t> serializedReal);

 private:
  float value = 0.0;
};

bool isValidReal(std::vector<uint8_t> serializedReal);