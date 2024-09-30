#pragma once

#include <types.h>

class ulinteger : public type {
 public:
  ulinteger(uint32_t value);
  ulinteger(byteString_t bytes);

  uint32_t getValue();

  byteString_t encode() override;
  void decode(byteString_t bytes) override;

 private:
  uint32_t value = 0;
};

static bool isValidUlinteger(byteString_t bytes);