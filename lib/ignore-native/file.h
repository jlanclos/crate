#pragma once

#include <entry/entry.h>
#include <stdint.h>

#include <array>
#include <vector>

struct entrySearchSummary {
  bool exists = false;
  uint8_t index;
  bool typeMatch;
};

class file {
 public:
  file();

  void clear();

  std::vector<uint8_t> getEntry(uint16_t id);
  void updateEntry(entry entryIn);
  void removeEntry(uint16_t id);
  std::vector<uint8_t> getBytes();
  void load(std::vector<uint8_t> fileDataIn);

  bool entryExists(uint16_t id);

 private:
  std::vector<entry> entries;
};