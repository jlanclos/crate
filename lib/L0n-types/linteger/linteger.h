#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class linteger : public type {
 public:
  linteger(int32_t value);
  linteger(std::vector<uint8_t> bytes);

  int32_t getValue();

  std::vector<uint8_t> encode() override;

 private:
  int32_t value = 0;
};

static bool isValidLinteger(std::vector<uint8_t> bytes);