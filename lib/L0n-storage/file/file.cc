#include <file/file.h>

// file class
file::file() {}
file::file(byteString_t bytes) { decode(bytes); }

void file::clear() { this->entries.clear(); }

byteString_t file::getEntryData(uint16_t id) {
  searchIdResult searchResult = this->searchId(id);
  if (searchResult.exists) {
    byteString_t entryData = this->entries[searchResult.index].getData();
    return entryData;
  }
  return {};
}

void file::setEntry(uint16_t id, type& object) {
  clearEntry(id);
  entry newEntry(id, object);
  this->entries.push_back(newEntry);
}

void file::clearEntry(uint16_t id) {
  searchIdResult searchResult = this->searchId(id);
  if (searchResult.exists) {
    this->entries.erase(this->entries.begin() + searchResult.index);
  }
}

searchIdResult file::searchId(uint16_t id) {
  searchIdResult result;
  uint16_t entriesSize = this->entries.size();
  if (entriesSize > 0) {
    for (uint16_t i = 0; i < entriesSize; i++) {
      if (this->entries[i].getId() == id) {
        result.exists = true;
        result.index = i;
        result.type = entries[i].getType();
        result.entry = entries[i];
      }
    }
  }
  return result;
}

byteString_t file::encode() {
  byteString_t bytes;
  entryString_t entries = this->entries;
  union {
    uint16_t value;
    uint8_t bytes[2];
  } entriesSize;
  entriesSize.value = entries.size();
  bytes.push_back(entriesSize.bytes[0]);
  bytes.push_back(entriesSize.bytes[1]);
  for (uint16_t i = 0; i < entriesSize.value; i++) {
    union {
      uint16_t value;
      uint8_t bytes[2];
    } entryId;
    union {
      uint32_t value;
      uint8_t bytes[4];
    } entryDataSize;
    byteString_t entryData = entries[i].getData();
    entryId.value = entries[i].getId();
    entryDataSize.value = entryData.size();
    bytes.push_back(entryId.bytes[0]);
    bytes.push_back(entryId.bytes[1]);
    bytes.push_back(entryDataSize.bytes[0]);
    bytes.push_back(entryDataSize.bytes[1]);
    bytes.push_back(entryDataSize.bytes[2]);
    bytes.push_back(entryDataSize.bytes[3]);
    for (uint32_t j = 0; j < entryDataSize.value; j++) {
      bytes.push_back(entryData[j]);
    }
  }
  return bytes;
}

void file::decode(byteString_t bytes) {
  if (bytes.size() >= 9) {
    union {
      uint16_t value;
      uint8_t bytes[2];
    } entriesSize;
    entriesSize.bytes[0] = bytes[0];
    entriesSize.bytes[1] = bytes[1];
    uint32_t readIndex = 2;
    for (uint16_t i = 0; i < entriesSize.value; i++) {
      union {
        uint16_t value;
        uint8_t bytes[2];
      } entryId;
      union {
        uint32_t value;
        uint8_t bytes[4];
      } entryDataSize;
      entryId.bytes[0] = bytes[readIndex];
      entryId.bytes[1] = bytes[readIndex + 1];
      entryDataSize.bytes[0] = bytes[readIndex + 2];
      entryDataSize.bytes[1] = bytes[readIndex + 3];
      entryDataSize.bytes[2] = bytes[readIndex + 4];
      entryDataSize.bytes[3] = bytes[readIndex + 5];
      byteString_t entryData;
      for (uint32_t j = 0; j < entryDataSize.value; j++) {
        entryData.push_back(bytes[readIndex + 5 + j]);
      }
      if (entryDataSize.value >= 2) {
        entryType type = (entryType)entryData[0];
        switch (type) {
          case entryType::BOOLEAN: {
            boolean newBoolean(entryData);
            entry newEntry(entryId.value, newBoolean);
            this->entries.push_back(newEntry);
          } break;
          case entryType::INTEGER: {
            integer newInteger(entryData);
            entry newEntry(entryId.value, newInteger);
            this->entries.push_back(newEntry);
          } break;
          case entryType::IP: {
            ip newIp(entryData);
            entry newEntry(entryId.value, newIp);
            this->entries.push_back(newEntry);
          } break;
          case entryType::LINTEGER: {
            linteger newLinteger(entryData);
            entry newEntry(entryId.value, newLinteger);
            this->entries.push_back(newEntry);
          } break;
          case entryType::MAC: {
            mac newMac(entryData);
            entry newEntry(entryId.value, newMac);
            this->entries.push_back(newEntry);
          } break;
          case entryType::REAL: {
            real newReal(entryData);
            entry newEntry(entryId.value, newReal);
            this->entries.push_back(newEntry);
          } break;
          case entryType::SINTEGER: {
            sinteger newSinteger(entryData);
            entry newEntry(entryId.value, newSinteger);
            this->entries.push_back(newEntry);
          } break;
          case entryType::STRING: {
            string newString(entryData);
            entry newEntry(entryId.value, newString);
            this->entries.push_back(newEntry);
          } break;
          case entryType::UINTEGER: {
            uinteger newUinteger(entryData);
            entry newEntry(entryId.value, newUinteger);
            this->entries.push_back(newEntry);
          } break;
          case entryType::ULINTEGER: {
            ulinteger newUlinteger(entryData);
            entry newEntry(entryId.value, newUlinteger);
            this->entries.push_back(newEntry);
          } break;
          case entryType::USINTEGER: {
            usinteger newUsinteger(entryData);
            entry newEntry(entryId.value, newUsinteger);
            this->entries.push_back(newEntry);
          } break;
          case entryType::WIFI_CHANNEL: {
            wifiChannel newWifiChannel(entryData);
            entry newEntry(entryId.value, newWifiChannel);
            this->entries.push_back(newEntry);
          }
          default:
            break;
        }
      }
      readIndex += 5 + entryDataSize.value;
    }
  }
}
