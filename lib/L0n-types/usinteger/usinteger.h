#pragma once

#include <types.h>

class usinteger : public type {
 public:
  usinteger(uint8_t value);
  usinteger(encoding_t bytes);

  uint8_t getValue();

  encoding_t encode() override;

 private:
  uint8_t value = 0;
};

static bool isValidUsinteger(encoding_t bytes);