#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class uinteger : public type {
 public:
  uinteger(uint16_t value);
  uinteger(std::vector<uint8_t> bytes);

  uint16_t getValue();

  std::vector<uint8_t> getBytes() override;

 private:
  uint16_t value = 0;
};

static bool isValidUinteger(std::vector<uint8_t> bytes);