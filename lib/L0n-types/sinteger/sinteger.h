#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class sinteger : public type {
 public:
  sinteger(int8_t value);
  sinteger(std::vector<uint8_t> bytes);

  int8_t getValue();

  std::vector<uint8_t> getBytes() override;

 private:
  int8_t value = 0;
};

static bool isValidSinteger(std::vector<uint8_t> bytes);