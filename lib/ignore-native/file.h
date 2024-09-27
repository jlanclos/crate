#pragma once

#include <entry/entry.h>
#include <stdint.h>

#include <array>
#include <vector>

struct reportSummary {
  bool exists = false;
  entry resultEntry;
  uint8_t index;
};

struct updateSummary {
  uint8_t index;
  bool exists = false;
  entry resultEntry;
};

struct saveSummary {
  bool success = false;
  std::vector<uint8_t> package;
};

struct loadSummary {
  bool success = false;
};

struct entrySearchSummary {
  bool exists = false;
  uint8_t index;
  bool typeMatch;
};

class file {
 public:
  file();

  void clear();

  std::vector<uint8_t> reportEntry(uint8_t id);
  void updateEntry(entry entryIn);
  void removeEntry(uint8_t);
  saveSummary save();
  loadSummary load(std::vector<uint8_t> fileDataIn);

  bool entryExists(uint16_t id);

 private:
  std::vector<entry> entries;
};