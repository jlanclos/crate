#include <gtest/gtest.h>
#include <real/real.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(realMethods, realCreateRead) {
  sequencer generator32(0, 4294967255, 100000000);
  sequencer generator8(0, 255);

  // real can be instantiated without arguments, resulting in a value of 0
  real mockReal;
  ASSERT_EQ(mockReal.getValue(), 0.0);

  // real can be instantiated with a value as an argument
  for (uint16_t i = 0; i < 256; i++) {
    float sequenceValue = (generator32.next() - 2147483648) / (generator8.next() + 0.00001);
    real mockRealSeq(sequenceValue);
    ASSERT_EQ(mockRealSeq.getValue(), sequenceValue);
  }

  // real can be instantiated with a serializedReal vector
  for (uint16_t i = 0; i < 256; i++) {
    union {
      float decimal;
      uint8_t bytes[4];
    } number;
    float sequenceValue = (generator32.next() - 2147483648) / (generator8.next() + 0.00001);
    number.decimal = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    uint8_t byte2 = number.bytes[1];
    uint8_t byte3 = number.bytes[2];
    uint8_t byte4 = number.bytes[3];
    std::vector<uint8_t> serializedReal = {(uint8_t)entryType::REAL, 4, byte1, byte2, byte3, byte4};
    real mockRealSeq(serializedReal);
    ASSERT_EQ(isValidReal(serializedReal), true);
    ASSERT_EQ(mockRealSeq.getValue(), sequenceValue);
  }
}

TEST(realMethods, realSerialization) {
  sequencer generator32(0, 4294967255, 100000000);
  sequencer generator8(0, 255);

  for (uint16_t i = 0; i < 256; i++) {
    union {
      float decimal;
      uint8_t bytes[4];
    } number;
    float sequenceValue = (generator32.next() - 2147483648) / (generator8.next() + 0.00001);
    number.decimal = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    uint8_t byte2 = number.bytes[1];
    uint8_t byte3 = number.bytes[2];
    uint8_t byte4 = number.bytes[3];
    real mockRealSeq(sequenceValue);
    ASSERT_EQ(mockRealSeq.getValue(), sequenceValue);

    std::vector<uint8_t> serializedReal = {(uint8_t)entryType::REAL, 4, byte1, byte2, byte3, byte4};
    ASSERT_EQ(mockRealSeq.serialize(), serializedReal);
    real mockRealSeqPrevious(sequenceValue);
    mockRealSeq.deserialize(mockRealSeq.serialize());
    ASSERT_EQ(mockRealSeq.getValue(), mockRealSeqPrevious.getValue());
  }
}