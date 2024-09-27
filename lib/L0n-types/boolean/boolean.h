#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class boolean : public type {
 public:
  boolean(bool value);
  boolean(std::vector<uint8_t> bytes);

  bool getValue();
  std::vector<uint8_t> encode() override;

 private:
  bool value = false;
};

static bool isValidBoolean(std::vector<uint8_t> bytes);