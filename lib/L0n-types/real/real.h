#pragma once

#include <types.h>

class real : public type {
 public:
  real(float value);
  real(encoding_t bytes);

  float getValue();

  encoding_t encode() override;

 private:
  float value = 0.0;
};

static bool isValidReal(encoding_t bytes);