#include <gtest/gtest.h>
#include <linteger/linteger.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(lintegerMethods, lintegerCreateRead) {
  sequencer generator32(0, 4294967255, 100000000);

  // linteger can be instantiated without arguments, resulting in a value of 0
  linteger mockLinteger;
  ASSERT_EQ(mockLinteger.getValue(), 0);

  // linteger can be instantiated with a value as an argument
  for (uint16_t i = 0; i < 256; i++) {
    int32_t sequenceValue = generator32.next() - 2147483648;
    linteger mockLintegerSeq(sequenceValue);
    ASSERT_EQ(mockLintegerSeq.getValue(), sequenceValue);
  }

  // linteger can be instantiated with a serializedLinteger vector
  for (uint16_t i = 0; i < 256; i++) {
    union {
      int32_t linteger;
      uint8_t bytes[4];
    } number;
    int32_t sequenceValue = generator32.next() - 2147483648;
    number.linteger = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    uint8_t byte2 = number.bytes[1];
    uint8_t byte3 = number.bytes[2];
    uint8_t byte4 = number.bytes[3];
    std::vector<uint8_t> serializedLinteger = {(uint8_t)entryType::LINTEGER, 4, byte1, byte2, byte3, byte4};
    linteger mockLintegerSeq(serializedLinteger);
    ASSERT_EQ(isValidLinteger(serializedLinteger), true);
    ASSERT_EQ(mockLintegerSeq.getValue(), sequenceValue);
  }
}

TEST(lintegerMethods, lintegerSerialization) {
  sequencer generator32(0, 4294967255, 100000000);

  for (uint16_t i = 0; i < 256; i++) {
    union {
      int32_t linteger;
      uint8_t bytes[4];
    } number;
    int32_t sequenceValue = generator32.next() - 2147483648;
    number.linteger = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    uint8_t byte2 = number.bytes[1];
    uint8_t byte3 = number.bytes[2];
    uint8_t byte4 = number.bytes[3];
    linteger mockLintegerSeq(sequenceValue);
    ASSERT_EQ(mockLintegerSeq.getValue(), sequenceValue);

    std::vector<uint8_t> serializedLinteger = {(uint8_t)entryType::LINTEGER, 4, byte1, byte2, byte3, byte4};
    ASSERT_EQ(mockLintegerSeq.serialize(), serializedLinteger);
    linteger mockLintegerSeqPrevious(sequenceValue);
    mockLintegerSeq.deserialize(mockLintegerSeq.serialize());
    ASSERT_EQ(mockLintegerSeq.getValue(), mockLintegerSeqPrevious.getValue());
  }
}