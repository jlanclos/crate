#include <gtest/gtest.h>
#include <sequencer.h>
#include <uinteger/uinteger.h>

#define GTEST_COUT std::cout

TEST(uintegerMethods, uintegerCreateRead) {
  sequencer generator16(0, 65535, 500);

  // unsigned long can be instantiated with a value as an argument
  for (uint16_t i = 0; i < 256; i++) {
    uint16_t sequenceValue = generator16.next();
    uinteger mockUintegerSeq(sequenceValue);
    ASSERT_EQ(mockUintegerSeq.getValue(), sequenceValue);
  }

  // unsigned long can be instantiated with a serializedUinteger vector
  for (uint16_t i = 0; i < 256; i++) {
    union {
      uint16_t integer;
      uint8_t bytes[2];
    } number;
    uint16_t sequenceValue = generator16.next();
    number.integer = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    uint8_t byte2 = number.bytes[1];
    encoding_t serializedUinteger = {(uint8_t)entryType::UINTEGER, byte1, byte2};
    uinteger mockUintegerSeq(serializedUinteger);
    ASSERT_EQ(mockUintegerSeq.getValue(), sequenceValue);
  }
}

TEST(uintegerMethods, uintegerSerialization) {
  sequencer generator16(0, 65535, 500);

  for (uint16_t i = 0; i < 256; i++) {
    union {
      uint16_t integer;
      uint8_t bytes[2];
    } number;
    uint16_t sequenceValue = generator16.next();
    number.integer = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    uint8_t byte2 = number.bytes[1];
    uinteger mockUintegerSeq(sequenceValue);
    ASSERT_EQ(mockUintegerSeq.getValue(), sequenceValue);

    encoding_t serializedUinteger = {(uint8_t)entryType::UINTEGER, byte1, byte2};
    ASSERT_EQ(mockUintegerSeq.encode(), serializedUinteger);
    uinteger mockUintegerSeqPrevious(sequenceValue);
    uinteger mockUintegerSeqNew(mockUintegerSeq.encode());
    ASSERT_EQ(mockUintegerSeqNew.getValue(), mockUintegerSeqPrevious.getValue());
  }
}