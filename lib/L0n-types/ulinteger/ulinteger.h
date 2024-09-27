#pragma once

#include <types.h>

class ulinteger : public type {
 public:
  ulinteger(uint32_t value);
  ulinteger(encoding_t bytes);

  uint32_t getValue();

  encoding_t encode() override;

 private:
  uint32_t value = 0;
};

static bool isValidUlinteger(encoding_t bytes);