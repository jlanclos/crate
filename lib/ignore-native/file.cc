#include <file.h>

// file class
file::file() {}

void file::clear() { this->entries.clear(); }

std::vector<uint8_t> file::getEntry(uint16t id) {
  reportSummary summary;
  summary.exists = false;
  summary.index = 0;
  entrySearchSummary entry = this->entrySearch(id);
  if (entry.exists) {
    summary.index = entry.index;
    summary.resultEntry = this->entries[entry.index];
    summary.exists = true;
  }
  return summary;
}

void file::updateEntry(entry entryIn) {
  updateSummary summary;
  summary.exists = false;
  summary.index = 0;
  summary.resultEntry = entryIn;
  uint8_t entryId = entryIn.getId();
  entryType entryType = entryIn.getType();
  std::vector<uint8_t> entryData = entryIn.getData();
  entrySearchSummary entry = this->entrySearch(entryId);
  summary.exists = entry.exists;
  summary.index = entry.index;
  if (not entry.exists) {
    this->entries.push_back(entryIn);
  } else {
    this->entries[entry.index].setType(entryType);
    this->entries[entry.index].setData(entryData);
  }
  return summary;
}

std::vector<uint8_t> file::getBytes() {
  std::vector<uint8_t> bytes;
  std::vector<entry> entries = this->entries;
  union {
    uint16_t value;
    uint8_t bytes[2];
  } entriesSize;
  entriesSize.value = entries.size();
  bytes.push_back(entriesSize.bytes[0]);
  bytes.push_back(entriesSize.bytes[1]);
  for (uint16_t i = 0; i < entriesSize.value; i++) {
    uint16_t entryId = entries[i].getId();
    std::vector<uint8_t> entryBytes = entries[i].getBytes();
    uint32_t entryBytesSize = entryBytes.size();
    bytes.push_back(entryId);
    for (uint32_t j = 0; j < entryBytesSize; j++) {
      bytes.push_back(entryBytes[j]);
    }
  }
  return bytes;
}

void file::load(std::vector<uint8_t> fileDataIn) {
  std::vector<uint8_t> loadImage = fileDataIn;
  std::vector<entry> loadEntries;
  if (loadImage.size() > 0) {
    uint16_t iterator = 0;
    uint16_t loadEntriesSize = 0;
    for (uint8_t i = 0; i < 2; i++) {
      loadEntriesSize |= loadImage[iterator] << (i * 8);
      iterator++;
    }
    for (uint16_t i = 0; i < loadEntriesSize; i++) {
      uint8_t id = loadImage[iterator];
      entry entry(id);
      iterator++;
      entry.setType((entryType)loadImage[iterator]);
      iterator++;
      uint16_t entrySize = 0;
      for (uint8_t j = 0; j < 2; j++) {
        entrySize |= loadImage[iterator] << (j * 8);
        iterator++;
      }
      std::vector<uint8_t> entryData;
      for (uint16_t j = 0; j < entrySize; j++) {
        entryData.push_back(loadImage[iterator]);
        iterator++;
      }
      entry.setData(entryData);
      loadEntries.push_back(entry);
    }
    this->entries = loadEntries;
  }
}

bool file::entryExists(uint16_t id) {
  entrySearchSummary summary;
  summary.exists = false;
  summary.index = 0;
  summary.typeMatch = false;
  uint16_t entriesSize = this->entries.size();
  if (entriesSize > 0) {
    for (uint16_t i = 0; i < entriesSize; i++) {
      if (this->entries[i].getId() == id) {
        summary.exists = true;
        summary.index = i;
        summary.typeMatch = this->entries[i].isType(identryType);
        break;
      }
    }
  }
  return summary;
}
