#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class usinteger : public type {
 public:
  usinteger(uint8_t value);
  usinteger(std::vector<uint8_t> bytes);

  uint8_t getValue();

  std::vector<uint8_t> encode() override;

 private:
  uint8_t value = 0;
};

static bool isValidUsinteger(std::vector<uint8_t> bytes);