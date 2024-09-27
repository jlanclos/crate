#pragma once

#include <types.h>

class uinteger : public type {
 public:
  uinteger(uint16_t value);
  uinteger(encoding_t bytes);

  uint16_t getValue();

  encoding_t encode() override;

 private:
  uint16_t value = 0;
};

static bool isValidUinteger(encoding_t bytes);