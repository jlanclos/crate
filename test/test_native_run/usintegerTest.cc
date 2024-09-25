#include <gtest/gtest.h>
#include <sequencer.h>
#include <usinteger/usinteger.h>

#define GTEST_COUT std::cout

TEST(usintegerMethods, usintegerCreateRead) {
  sequencer generator8(0, 255);

  // unsigned long can be instantiated without arguments, resulting in a value of 0
  usinteger mockUsinteger;
  ASSERT_EQ(mockUsinteger.getValue(), 0);

  // unsigned long can be instantiated with a value as an argument
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequenceValue = generator8.next();
    usinteger mockUsintegerSeq(sequenceValue);
    ASSERT_EQ(mockUsintegerSeq.getValue(), sequenceValue);
  }

  // unsigned long can be instantiated with a serializedUsinteger vector
  for (uint16_t i = 0; i < 256; i++) {
    union {
      uint8_t integer;
      uint8_t bytes[1];
    } number;
    uint8_t sequenceValue = generator8.next();
    number.integer = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    std::vector<uint8_t> serializedUsinteger = {(uint8_t)entryType::USINTEGER, 1, byte1};
    usinteger mockUsintegerSeq(serializedUsinteger);
    ASSERT_EQ(isValidUsinteger(serializedUsinteger), true);
    ASSERT_EQ(mockUsintegerSeq.getValue(), sequenceValue);
  }
}

TEST(usintegerMethods, usintegerSerialization) {
  sequencer generator8(0, 255);

  for (uint16_t i = 0; i < 256; i++) {
    union {
      uint8_t integer;
      uint8_t bytes[1];
    } number;
    uint8_t sequenceValue = generator8.next();
    number.integer = sequenceValue;
    uint8_t byte1 = number.bytes[0];
    usinteger mockUsintegerSeq(sequenceValue);
    ASSERT_EQ(mockUsintegerSeq.getValue(), sequenceValue);

    std::vector<uint8_t> serializedUsinteger = {(uint8_t)entryType::USINTEGER, 1, byte1};
    ASSERT_EQ(mockUsintegerSeq.serialize(), serializedUsinteger);
    usinteger mockUsintegerSeqPrevious(sequenceValue);
    mockUsintegerSeq.deserialize(mockUsintegerSeq.serialize());
    ASSERT_EQ(mockUsintegerSeq.getValue(), mockUsintegerSeqPrevious.getValue());
  }
}