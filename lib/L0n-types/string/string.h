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
  bool isValidSerial(std::vector<uint8_t> serializedString);
  void deserialize(std::vector<uint8_t> serializedString);

 private:
  std::string value = 0;
};