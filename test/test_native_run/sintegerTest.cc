#include <gtest/gtest.h>
#include <sequencer.h>
#include <sinteger/sinteger.h>

#define GTEST_COUT std::cout

TEST(sintegerMethods, sintegerCreateRead) {
  sequencer generator8(0, 255);

  // sinteger can be instantiated with a value as an argument
  for (uint16_t i = 0; i < 256; i++) {
    int8_t sequenceValue = generator8.next() - 127;
    sinteger mockSintegerSeq(sequenceValue);
    ASSERT_EQ(mockSintegerSeq.getValue(), sequenceValue);
  }

  // sinteger can be instantiated with a serializedSinteger vector
  for (uint16_t i = 0; i < 256; i++) {
    union {
      int8_t sinteger;
      uint8_t bytes[1];
    } number;
    int8_t sequenceValue = generator8.next() - 127;
    number.sinteger = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    std::vector<uint8_t> serializedSinteger = {(uint8_t)entryType::SINTEGER, 1, byte1};
    sinteger mockSintegerSeq(serializedSinteger);
    ASSERT_EQ(mockSintegerSeq.getValue(), sequenceValue);
  }
}

TEST(sintegerMethods, sintegerSerialization) {
  sequencer generator8(0, 255);

  for (uint16_t i = 0; i < 256; i++) {
    union {
      int8_t sinteger;
      uint8_t bytes[1];
    } number;
    int8_t sequenceValue = generator8.next() - 127;
    number.sinteger = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    sinteger mockSintegerSeq(sequenceValue);
    ASSERT_EQ(mockSintegerSeq.getValue(), sequenceValue);

    std::vector<uint8_t> serializedSinteger = {(uint8_t)entryType::SINTEGER, 1, byte1};
    ASSERT_EQ(mockSintegerSeq.getBytes(), serializedSinteger);
    sinteger mockSintegerSeqPrevious(sequenceValue);
    sinteger mockSintegerSeqNew(mockSintegerSeq.getBytes());
    ASSERT_EQ(mockSintegerSeqNew.getValue(), mockSintegerSeqPrevious.getValue());
  }
}