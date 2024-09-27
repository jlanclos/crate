#pragma once

#include <stdint.h>
#include <types.h>

#include <string>
#include <vector>

class string : public type {
 public:
  string(std::string value);
  string(std::vector<uint8_t> bytes);

  std::string getValue();

  std::vector<uint8_t> getBytes() override;

 private:
  std::string value = "";
};

static bool isValidString(std::vector<uint8_t> bytes);