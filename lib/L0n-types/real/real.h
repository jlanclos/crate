#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class real : public type {
 public:
  real(float value);
  real(std::vector<uint8_t> bytes);

  float getValue();

  std::vector<uint8_t> getBytes() override;

 private:
  float value = 0.0;
};

static bool isValidReal(std::vector<uint8_t> bytes);