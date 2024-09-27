#pragma once

#include <types.h>

class linteger : public type {
 public:
  linteger(int32_t value);
  linteger(encoding_t bytes);

  int32_t getValue();

  encoding_t encode() override;

 private:
  int32_t value = 0;
};

static bool isValidLinteger(encoding_t bytes);