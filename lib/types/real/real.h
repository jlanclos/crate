#pragma once

#include <types.h>

class real : public type {
 public:
  real(float value);
  real(byteString_t bytes);

  float getValue();

  byteString_t encode() override;
  void decode(byteString_t bytes) override;

 private:
  float value = 0.0;
};

static bool isValidReal(byteString_t bytes);