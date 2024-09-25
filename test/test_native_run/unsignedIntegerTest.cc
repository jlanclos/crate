#include <gtest/gtest.h>
#include <sequencer.h>
#include <unsignedInteger/unsignedInteger.h>

#define GTEST_COUT std::cout

TEST(unsignedIntegerMethods, unsignedIntegerCreateRead) {
  sequencer generator32(0, 4294967255, 100000000);

  // unsigned integer can be instantiated without arguments, resulting in a value of 0
  unsignedInteger mockUnsignedInteger;
  ASSERT_EQ(mockUnsignedInteger.getValue(), 0);

  // unsigned integer can be instantiated with a value as an argument
  for (uint16_t i = 0; i < 256; i++) {
    uint32_t sequenceValue = generator32.next();
    unsignedInteger mockUnsignedIntegerSeq(sequenceValue);
    ASSERT_EQ(mockUnsignedIntegerSeq.getValue(), sequenceValue);
  }

  // unsigned integer can be instantiated with a serializedUnsignedInteger vector
  for (uint16_t i = 0; i < 256; i++) {
    union {
      uint32_t integer;
      uint8_t bytes[4];
    } number;
    uint32_t sequenceValue = generator32.next();
    number.integer = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    uint8_t byte2 = number.bytes[1];
    uint8_t byte3 = number.bytes[2];
    uint8_t byte4 = number.bytes[3];
    std::vector<uint8_t> serializedUnsignedInteger = {
        (uint8_t)entryType::UNSIGNED_INTEGER, 4, byte1, byte2, byte3, byte4};
    unsignedInteger mockUnsignedIntegerSeq(serializedUnsignedInteger);
    ASSERT_EQ(unsignedInteger::isValidSerial(serializedUnsignedInteger), true);
    ASSERT_EQ(mockUnsignedIntegerSeq.getValue(), sequenceValue);
  }
}

TEST(unsignedIntegerMethods, unsignedIntegerSerialization) {
  sequencer generator32(0, 4294967255, 100000000);

  for (uint16_t i = 0; i < 256; i++) {
    union {
      uint32_t integer;
      uint8_t bytes[4];
    } number;
    uint32_t sequenceValue = generator32.next();
    number.integer = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    uint8_t byte2 = number.bytes[1];
    uint8_t byte3 = number.bytes[2];
    uint8_t byte4 = number.bytes[3];
    unsignedInteger mockUnsignedIntegerSeq(sequenceValue);
    ASSERT_EQ(mockUnsignedIntegerSeq.getValue(), sequenceValue);

    std::vector<uint8_t> serializedUnsignedInteger = {
        (uint8_t)entryType::UNSIGNED_INTEGER, 4, byte1, byte2, byte3, byte4};
    ASSERT_EQ(mockUnsignedIntegerSeq.serialize(), serializedUnsignedInteger);
    unsignedInteger mockUnsignedIntegerSeqPrevious(sequenceValue);
    mockUnsignedIntegerSeq.deserialize(mockUnsignedIntegerSeq.serialize());
    ASSERT_EQ(mockUnsignedIntegerSeq.getValue(), mockUnsignedIntegerSeqPrevious.getValue());
  }
}