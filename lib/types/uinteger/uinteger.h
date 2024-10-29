#pragma once

#include <types.h>

class uinteger : public type {
 public:
  uinteger(uint16_t value);
  uinteger(byteString_t bytes);

  uint16_t getValue();

  byteString_t encode() override;
  void decode(byteString_t bytes) override;

 private:
  uint16_t value = 0;
};

static bool isValidUinteger(byteString_t bytes);