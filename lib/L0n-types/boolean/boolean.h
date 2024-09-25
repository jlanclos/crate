#pragma once

#include <stdint.h>
#include <types.h>

#include <vector>

class boolean {
 public:
  boolean();
  boolean(bool value);
  boolean(std::vector<uint8_t> serializedBoolean);

  bool getValue();

  std::vector<uint8_t> serialize();
  void deserialize(std::vector<uint8_t> serializedBoolean);
  static bool isValidSerial(std::vector<uint8_t> serializedBoolean);

 private:
  bool value = false;
};