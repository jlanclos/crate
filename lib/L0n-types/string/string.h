#pragma once

#include <types.h>

class string : public type {
 public:
  string(string_t value);
  string(encoding_t bytes);

  string_t getValue();

  encoding_t encode() override;

 private:
  string_t value = "";
};

static bool isValidString(encoding_t bytes);