#include <gtest/gtest.h>
#include <integer/integer.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(integerMethods, integerCreateRead) {
  sequencer generator32(0, 4294967255, 100000000);

  // integer can be instantiated without arguments, resulting in a value of 0
  integer mockInteger;
  ASSERT_EQ(mockInteger.getValue(), 0);

  // integer can be instantiated with a value as an argument
  for (uint16_t i = 0; i < 256; i++) {
    int32_t sequenceValue = generator32.next() - 2147483648;
    integer mockIntegerSeq(sequenceValue);
    ASSERT_EQ(mockIntegerSeq.getValue(), sequenceValue);
  }

  // integer can be instantiated with a serializedInteger vector
  for (uint16_t i = 0; i < 256; i++) {
    union {
      int32_t integer;
      uint8_t bytes[4];
    } number;
    int32_t sequenceValue = generator32.next() - 2147483648;
    number.integer = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    uint8_t byte2 = number.bytes[1];
    uint8_t byte3 = number.bytes[2];
    uint8_t byte4 = number.bytes[3];
    std::vector<uint8_t> serializedInteger = {(uint8_t)entryType::INTEGER, 4, byte1, byte2, byte3, byte4};
    integer mockIntegerSeq(serializedInteger);
    ASSERT_EQ(integer::isValidSerial(serializedInteger), true);
    ASSERT_EQ(mockIntegerSeq.getValue(), sequenceValue);
  }
}

TEST(integerMethods, integerSerialization) {
  sequencer generator32(0, 4294967255, 100000000);

  for (uint16_t i = 0; i < 256; i++) {
    union {
      int32_t integer;
      uint8_t bytes[4];
    } number;
    int32_t sequenceValue = generator32.next() - 2147483648;
    number.integer = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    uint8_t byte2 = number.bytes[1];
    uint8_t byte3 = number.bytes[2];
    uint8_t byte4 = number.bytes[3];
    integer mockIntegerSeq(sequenceValue);
    ASSERT_EQ(mockIntegerSeq.getValue(), sequenceValue);

    std::vector<uint8_t> serializedInteger = {(uint8_t)entryType::INTEGER, 4, byte1, byte2, byte3, byte4};
    ASSERT_EQ(mockIntegerSeq.serialize(), serializedInteger);
    integer mockIntegerSeqPrevious(sequenceValue);
    mockIntegerSeq.deserialize(mockIntegerSeq.serialize());
    ASSERT_EQ(mockIntegerSeq.getValue(), mockIntegerSeqPrevious.getValue());
  }
}