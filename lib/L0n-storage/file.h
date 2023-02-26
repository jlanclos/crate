#pragma once

#include <entry.h>
#include <stdint.h>

#include <array>

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

struct reportSummaryDigital {
  bool exists = false;
  bool value;
};

struct reportSummaryAnalog8 {
  bool exists = false;
  uint8_t value;
};

struct reportSummaryAnalog16 {
  bool exists = false;
  uint16_t value;
};

struct reportSummaryAnalog32 {
  bool exists = false;
  uint32_t value;
};

struct reportSummaryString {
  bool exists = false;
  std::string value;
};

struct reportSummaryMac {
  bool exists = false;
  mac value;
};

struct reportSummaryIp {
  bool exists = false;
  ip value;
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

  reportSummary reportEntry(uint8_t id);
  updateSummary updateEntry(entry entryIn);
  saveSummary save();
  loadSummary load(std::vector<uint8_t> fileDataIn);

  updateSummary updateEntryDigital(uint8_t id, bool value);
  updateSummary updateEntryAnalog8(uint8_t id, uint8_t value);
  updateSummary updateEntryAnalog16(uint8_t id, uint16_t value);
  updateSummary updateEntryAnalog32(uint8_t id, uint32_t value);
  updateSummary updateEntryString(uint8_t id, std::string value);
  updateSummary updateEntryMac(uint8_t id, mac value);
  updateSummary updateEntryIp(uint8_t id, ip value);

  reportSummaryDigital reportEntryDigital(uint8_t id);
  reportSummaryAnalog8 reportEntryAnalog8(uint8_t id);
  reportSummaryAnalog16 reportEntryAnalog16(uint8_t id);
  reportSummaryAnalog32 reportEntryAnalog32(uint8_t id);
  reportSummaryString reportEntryString(uint8_t id);
  reportSummaryMac reportEntryMac(uint8_t id);
  reportSummaryIp reportEntryIp(uint8_t id);

  entrySearchSummary entrySearch(uint8_t id, entryType identryType = entryType::UNKNOWN);

  std::vector<entry> entries;

 private:
};