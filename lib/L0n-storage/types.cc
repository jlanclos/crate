#include <types.h>

bool isValidDataType(std::vector<uint8_t> data) {
  uint32_t dataSize = data.size();
  if (dataSize == 0) {
    return false;
  }
  entryType type = (entryType)data[0];
  switch (type) {
    case entryType::BOOLEAN:
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