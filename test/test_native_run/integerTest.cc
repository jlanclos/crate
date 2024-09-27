#include <gtest/gtest.h>
#include <integer/integer.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(integerMethods, integerCreateRead) {
  sequencer generator16(0, 65535, 500);

  // integer can be instantiated with a value as an argument
  for (uint16_t i = 0; i < 256; i++) {
    int16_t sequenceValue = generator16.next() - 32768;
    integer mockIntegerSeq(sequenceValue);
    ASSERT_EQ(mockIntegerSeq.getValue(), sequenceValue);
  }

  // integer can be instantiated with a serializedInteger vector
  for (uint16_t i = 0; i < 256; i++) {
    union {
      int16_t integer;
      uint8_t bytes[2];
    } number;
    int16_t sequenceValue = generator16.next() - 32768;
    number.integer = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    uint8_t byte2 = number.bytes[1];
    std::vector<uint8_t> serializedInteger = {(uint8_t)entryType::INTEGER, byte1, byte2};
    integer mockIntegerSeq(serializedInteger);
    ASSERT_EQ(mockIntegerSeq.getValue(), sequenceValue);
  }
}

TEST(integerMethods, integerSerialization) {
  sequencer generator16(0, 65535, 500);

  for (uint16_t i = 0; i < 256; i++) {
    union {
      int16_t integer;
      uint8_t bytes[2];
    } number;
    int16_t sequenceValue = generator16.next() - 32768;
    number.integer = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    uint8_t byte2 = number.bytes[1];
    integer mockIntegerSeq(sequenceValue);
    ASSERT_EQ(mockIntegerSeq.getValue(), sequenceValue);

    std::vector<uint8_t> serializedInteger = {(uint8_t)entryType::INTEGER, byte1, byte2};
    ASSERT_EQ(mockIntegerSeq.getBytes(), serializedInteger);
    integer mockIntegerSeqPrevious(sequenceValue);
    integer mockIntegerSeqNew(mockIntegerSeq.getBytes());
    ASSERT_EQ(mockIntegerSeqNew.getValue(), mockIntegerSeqPrevious.getValue());
  }
}