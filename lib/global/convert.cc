#include <convert.h>

std::string vectorUInt8ToString(std::vector<uint8_t> vectorIn) {
  std::string stringResult = "";
  for (uint32_t i = 0; i < vectorIn.size(); i++) {
    stringResult += vectorIn[i];
  }
  return stringResult;
}

std::vector<uint8_t> stringToVectorUInt8(std::string stringIn) {
  std::vector<uint8_t> vectorResult;
  for (uint32_t i = 0; i < stringIn.length(); i++) {
    vectorResult.push_back(stringIn[i]);
  }
  return vectorResult;
}