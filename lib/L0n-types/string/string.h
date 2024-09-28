#pragma once

#include <types.h>

class string : public type {
 public:
  string(string_t value);
  string(byteString_t bytes);

  string_t getValue();

  byteString_t encode() override;

 private:
  string_t value = "";
};

static bool isValidString(byteString_t bytes);