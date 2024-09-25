#pragma once

#include <stdint.h>
#include <types.h>

#include <string>
#include <vector>

class string {
 public:
  string();
  string(std::string value);
  string(std::vector<uint8_t> serializedString);

  std::string getValue();

  std::vector<uint8_t> serialize();
  void deserialize(std::vector<uint8_t> serializedString);

  static bool isValidSerial(std::vector<uint8_t> serializedString);

 private:
  std::string value = "default";
};