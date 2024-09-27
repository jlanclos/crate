#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class integer : public type {
 public:
  integer(int16_t value);
  integer(std::vector<uint8_t> bytes);

  int16_t getValue();

  std::vector<uint8_t> getBytes() override;

 private:
  int16_t value = 0;
};

static bool isValidInteger(std::vector<uint8_t> bytes);