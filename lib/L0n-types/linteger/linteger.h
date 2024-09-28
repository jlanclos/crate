#pragma once

#include <types.h>

class linteger : public type {
 public:
  linteger(int32_t value);
  linteger(byteString_t bytes);

  int32_t getValue();

  byteString_t encode() override;

 private:
  int32_t value = 0;
};

static bool isValidLinteger(byteString_t bytes);