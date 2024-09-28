#pragma once

#include <types.h>

class sinteger : public type {
 public:
  sinteger(int8_t value);
  sinteger(byteString_t bytes);

  int8_t getValue();

  byteString_t encode() override;

 private:
  int8_t value = 0;
};

static bool isValidSinteger(byteString_t bytes);