#include <convert.h>
#include <gtest/gtest.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(convertMethods, vectorToString) {
  sequencer generator8(0, 255);
  // test known case
  std::vector<uint8_t> mockVector = {116, 104, 105, 115, 32, 105, 115, 32, 97, 32, 116, 101, 115, 116};
  ASSERT_EQ(vectorUInt8ToString(mockVector), "this is a test");
  // test sequence cases
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t mockVectorLength = generator8.next();
    std::vector<uint8_t> mockVector;
    std::string compareString;
    for (uint16_t i = 0; i < mockVectorLength; i++) {
      uint8_t sequenceChar = generator8.next();
      char stringCharacter = sequenceChar;
      mockVector.push_back(stringCharacter);
      compareString += stringCharacter;
    }
    ASSERT_EQ(vectorUInt8ToString(mockVector), compareString);
  }
}

TEST(convertMethods, stringToVectorUInt8) {
  sequencer generator8(0, 255);
  // test known case
  std::vector<uint8_t> mockVector = {116, 104, 105, 115, 32, 105, 115, 32, 97, 32, 116, 101, 115, 116};
  ASSERT_EQ(stringToVectorUInt8("this is a test"), mockVector);
  // test sequence cases
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t mockStringLength = generator8.next();
    std::string mockString;
    std::vector<uint8_t> compareVector;
    for (uint16_t i = 0; i < mockStringLength; i++) {
      uint8_t sequenceChar = generator8.next();
      char stringCharacter = sequenceChar;
      mockString += stringCharacter;
      compareVector.push_back(stringCharacter);
    }
    ASSERT_EQ(stringToVectorUInt8(mockString), compareVector);
  }
}