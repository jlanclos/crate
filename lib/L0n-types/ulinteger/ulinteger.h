#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class ulinteger : public type {
 public:
  ulinteger(uint32_t value);
  ulinteger(std::vector<uint8_t> bytes);

  uint32_t getValue();

  std::vector<uint8_t> getBytes() override;

 private:
  uint32_t value = 0;
};

static bool isValidUlinteger(std::vector<uint8_t> bytes);