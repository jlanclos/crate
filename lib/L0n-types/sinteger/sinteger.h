#pragma once

#include <types.h>

class sinteger : public type {
 public:
  sinteger(int8_t value);
  sinteger(encoding_t bytes);

  int8_t getValue();

  encoding_t encode() override;

 private:
  int8_t value = 0;
};

static bool isValidSinteger(encoding_t bytes);