#include <convert.h>
#include <gtest/gtest.h>
#include <sequencer.h>
#include <string/string.h>

#define GTEST_COUT std::cout

TEST(stringMethods, stringCreateRead) {
  sequencer generator8(0, 255);

  // string can be instantiated with a string as an argument
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequenceStringLength = generator8.next();
    string_t sequenceString;
    for (uint32_t i = 0; i < sequenceStringLength; i++) {
      char stringCharacter = generator8.next();
      sequenceString += stringCharacter;
    }
    string mockStringSeq(sequenceString);
    ASSERT_EQ(mockStringSeq.getValue(), sequenceString);
  }

  // string can be instantiated with a serializedString vector
  for (uint16_t i = 0; i < 256; i++) {
    union {
      uint32_t integer;
      uint8_t bytes[4];
    } dataSize;
    dataSize.integer = generator8.next();
    string_t sequenceString;
    encoding_t serializedString;
    serializedString.push_back((uint8_t)entryType::STRING);
    serializedString.push_back(dataSize.bytes[0]);
    serializedString.push_back(dataSize.bytes[1]);
    serializedString.push_back(dataSize.bytes[2]);
    serializedString.push_back(dataSize.bytes[3]);
    for (uint32_t i = 0; i < dataSize.integer; i++) {
      char stringCharacter = generator8.next();
      sequenceString += stringCharacter;
      serializedString.push_back((uint8_t)stringCharacter);
    }
    string mockStringSeq(serializedString);
    ASSERT_EQ(mockStringSeq.getValue(), sequenceString);
  }
}

TEST(stringMethods, stringSerialization) {
  sequencer generator8(0, 255);

  for (uint16_t i = 0; i < 256; i++) {
    union {
      uint32_t integer;
      uint8_t bytes[4];
    } dataSize;
    dataSize.integer = generator8.next();
    string_t sequenceString;
    encoding_t serializedString;
    serializedString.push_back((uint8_t)entryType::STRING);
    serializedString.push_back(dataSize.bytes[0]);
    serializedString.push_back(dataSize.bytes[1]);
    serializedString.push_back(dataSize.bytes[2]);
    serializedString.push_back(dataSize.bytes[3]);
    for (uint32_t i = 0; i < dataSize.integer; i++) {
      char stringCharacter = generator8.next();
      sequenceString += stringCharacter;
      serializedString.push_back((uint8_t)stringCharacter);
    }
    string mockStringSeq(sequenceString);
    ASSERT_EQ(mockStringSeq.getValue(), sequenceString);

    ASSERT_EQ(mockStringSeq.encode(), serializedString);
    string mockStringSeqPrevious(sequenceString);
    string mockStringSeqNew(mockStringSeq.encode());
    ASSERT_EQ(mockStringSeqNew.getValue(), mockStringSeqPrevious.getValue());
  }
}