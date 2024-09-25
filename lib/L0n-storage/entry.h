#pragma once

#include <boolean/boolean.h>
#include <ip/ip.h>
#include <linteger/linteger.h>
#include <mac/mac.h>
#include <real/real.h>
#include <stdint.h>
#include <string/string.h>
#include <types.h>
#include <ulinteger/ulinteger.h>

#include <string>
#include <vector>

class entry {
 public:
  entry();
  entry(uint16_t id);
  entry(std::vector<uint8_t> data);
  entry(uint16_t id, std::vector<uint8_t> data);

  void setId(uint16_t newId);
  uint16_t getId();
  entryType getType();

  void setData(std::vector<uint8_t> newData);
  std::vector<uint8_t> getData();

 private:
  uint16_t id = 0;
  std::vector<uint8_t> data = {(uint8_t)entryType::UNKNOWN};
};