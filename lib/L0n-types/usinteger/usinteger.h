#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class usinteger {
 public:
  usinteger();
  usinteger(uint8_t value);
  usinteger(std::vector<uint8_t> serializedUinteger);

  uint8_t getValue();

  std::vector<uint8_t> serialize();
  void deserialize(std::vector<uint8_t> serializedUinteger);
  static bool isValidSerial(std::vector<uint8_t> serializedUinteger);

 private:
  uint8_t value = 0;
};