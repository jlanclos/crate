#include <file.h>

// file class
file::file() {}

void file::clear() {
  for (uint16_t i = 0; i < this->entries.size(); i++) {
    this->entries.clear();
  }
}

reportSummary file::reportEntry(uint8_t id) {
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

updateSummary file::updateEntry(entry entryIn) {
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

saveSummary file::save() {
  saveSummary summary;
  summary.success = false;
  std::vector<entry> entries = this->entries;
  uint16_t entriesSize = entries.size();
  for (uint8_t i = 0; i < 2; i++) {
    summary.package.push_back(entriesSize >> (i * 8));
  }
  for (uint16_t i = 0; i < entriesSize; i++) {
    std::vector<uint8_t> entryData = entries[i].getData();
    summary.package.push_back(entries[i].getId());
    summary.package.push_back((uint8_t)entries[i].getType());
    uint16_t entrySize = entries[i].getDataSize();
    for (uint8_t j = 0; j < 2; j++) {
      summary.package.push_back(entrySize >> (j * 8));
    }
    for (uint16_t j = 0; j < entrySize; j++) {
      summary.package.push_back(entryData[j]);
    }
  }
  summary.success = true;
  return summary;
}

loadSummary file::load(std::vector<uint8_t> fileDataIn) {
  loadSummary summary;
  summary.success = false;
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
    summary.success = true;
  }
  return summary;
}

updateSummary file::updateEntryDigital(uint8_t id, bool value) {
  return this->updateEntry(createDigitalEntry(id, value));
}

updateSummary file::updateEntryAnalog8(uint8_t id, uint8_t value) {
  return this->updateEntry(createAnalog8Entry(id, value));
}

updateSummary file::updateEntryAnalog16(uint8_t id, uint16_t value) {
  return this->updateEntry(createAnalog16Entry(id, value));
}

updateSummary file::updateEntryAnalog32(uint8_t id, uint32_t value) {
  return this->updateEntry(createAnalog32Entry(id, value));
}

updateSummary file::updateEntryString(uint8_t id, std::string value) {
  return this->updateEntry(createStringEntry(id, value));
}

updateSummary file::updateEntryMac(uint8_t id, mac value) { return this->updateEntry(createMacEntry(id, value)); }

updateSummary file::updateEntryIp(uint8_t id, ip value) { return this->updateEntry(createIpEntry(id, value)); }

reportSummaryDigital file::reportEntryDigital(uint8_t id) {
  reportSummaryDigital summary;
  reportSummary pull = this->reportEntry(id);
  if (not pull.exists or not pull.resultEntry.isType(entryType::DIGITAL)) {
    return summary;
  }
  summary.value = pull.resultEntry.getDigital();
  summary.exists = true;
  return summary;
}

reportSummaryAnalog8 file::reportEntryAnalog8(uint8_t id) {
  reportSummaryAnalog8 summary;
  reportSummary pull = this->reportEntry(id);
  if (not pull.exists or not pull.resultEntry.isType(entryType::UINT8)) {
    return summary;
  }
  summary.value = pull.resultEntry.getAnalog8();
  summary.exists = true;
  return summary;
}

reportSummaryAnalog16 file::reportEntryAnalog16(uint8_t id) {
  reportSummaryAnalog16 summary;
  reportSummary pull = this->reportEntry(id);
  if (not pull.exists or not pull.resultEntry.isType(entryType::UINT16)) {
    return summary;
  }
  summary.value = pull.resultEntry.getAnalog16();
  summary.exists = true;
  return summary;
}

reportSummaryAnalog32 file::reportEntryAnalog32(uint8_t id) {
  reportSummaryAnalog32 summary;
  reportSummary pull = this->reportEntry(id);
  if (not pull.exists or not pull.resultEntry.isType(entryType::UINT32)) {
    return summary;
  }
  summary.value = pull.resultEntry.getAnalog32();
  summary.exists = true;
  return summary;
}

reportSummaryString file::reportEntryString(uint8_t id) {
  reportSummaryString summary;
  reportSummary pull = this->reportEntry(id);
  if (not pull.exists or not pull.resultEntry.isType(entryType::STRING)) {
    return summary;
  }
  summary.value = pull.resultEntry.getString();
  summary.exists = true;
  return summary;
}

reportSummaryMac file::reportEntryMac(uint8_t id) {
  reportSummaryMac summary;
  reportSummary pull = this->reportEntry(id);
  if (not pull.exists or not pull.resultEntry.isType(entryType::MAC)) {
    return summary;
  }
  summary.value = pull.resultEntry.getMac();
  summary.exists = true;
  return summary;
}

reportSummaryIp file::reportEntryIp(uint8_t id) {
  reportSummaryIp summary;
  reportSummary pull = this->reportEntry(id);
  if (not pull.exists or not pull.resultEntry.isType(entryType::IP)) {
    return summary;
  }
  summary.value = pull.resultEntry.getIp();
  summary.exists = true;
  return summary;
}

entrySearchSummary file::entrySearch(uint8_t id, entryType identryType) {
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
