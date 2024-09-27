#include <entry/entry.h>

// entry class
entry::entry() {}
entry::entry(uint16_t id) { this->id = id; }
entry::entry(std::vector<uint8_t> data) { this->data = data; }
entry::entry(uint16_t id, std::vector<uint8_t> data) {
  this->id = id;
  this->data = data;
}

void entry::setId(uint16_t newId) { this->id = newId; }

uint16_t entry::getId() { return this->id; }

entryType entry::getType() {
  if (isValidData(this->data)) {
    return (entryType)this->data[0];
  } else {
    return entryType::UNKNOWN;
  }
}

void entry::setData(std::vector<uint8_t> newData) { this->data = newData; }

std::vector<uint8_t> entry::getData() { return this->data; }

// methods
bool isValidData(std::vector<uint8_t> data) {
  uint32_t dataSize = data.size();
  if (dataSize == 0) {
    return false;
  }
  entryType type = (entryType)data[0];
  switch (type) {
    case entryType::BOOLEAN:
      return isValidBoolean(data);
      break;
    case entryType::USINTEGER:
      return isValidUsinteger(data);
      break;
    case entryType::SINTEGER:
      return isValidSinteger(data);
      break;
    case entryType::UINTEGER:
      return isValidUinteger(data);
      break;
    case entryType::INTEGER:
      return isValidInteger(data);
      break;
    case entryType::ULINTEGER:
      return isValidUlinteger(data);
      break;
    case entryType::LINTEGER:
      return isValidLinteger(data);
      break;
    case entryType::REAL:
      return isValidReal(data);
      break;
    case entryType::STRING:
      return isValidString(data);
      break;
    case entryType::MAC:
      return isValidMac(data);
      break;
    case entryType::IP:
      return isValidIp(data);
      break;
    default:
      return false;
      break;
  }
}