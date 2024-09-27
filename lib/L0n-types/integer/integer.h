#pragma once

#include <types.h>

class integer : public type {
 public:
  integer(int16_t value);
  integer(encoding_t bytes);

  int16_t getValue();

  encoding_t encode() override;

 private:
  int16_t value = 0;
};

static bool isValidInteger(encoding_t bytes);