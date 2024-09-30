#pragma once

#include <types.h>

class integer : public type {
 public:
  integer(int16_t value);
  integer(byteString_t bytes);

  int16_t getValue();

  byteString_t encode() override;
  void decode(byteString_t bytes) override;

 private:
  int16_t value = 0;
};

static bool isValidInteger(byteString_t bytes);