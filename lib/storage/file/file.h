#pragma once

#include <entry/entry.h>

typedef std::vector<entry> entryString_t;

struct searchIdResult {
  bool exists = false;
  uint16_t index = 0;
  entryType type = entryType::UNKNOWN;
  entry entryPackage;
};

class file : public encodable {
 public:
  file();
  file(byteString_t bytes);

  void clear();

  byteString_t getEntryData(uint16_t id);
  void setEntry(uint16_t id, type &object);
  void clearEntry(uint16_t id);
  searchIdResult searchId(uint16_t id);

  byteString_t encode() override;
  void decode(byteString_t bytes) override;

 private:
  entryString_t entries;
};