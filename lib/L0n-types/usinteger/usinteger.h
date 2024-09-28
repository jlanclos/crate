#pragma once

#include <types.h>

class usinteger : public type {
 public:
  usinteger(uint8_t value);
  usinteger(byteString_t bytes);

  uint8_t getValue();

  byteString_t encode() override;

 private:
  uint8_t value = 0;
};

static bool isValidUsinteger(byteString_t bytes);