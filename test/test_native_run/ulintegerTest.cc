#include <gtest/gtest.h>
#include <sequencer.h>
#include <ulinteger/ulinteger.h>

#define GTEST_COUT std::cout

TEST(ulintegerMethods, ulintegerCreateRead) {
  sequencer generator32(0, 4294967255, 100000000);

  // unsigned long can be instantiated with a value as an argument
  for (uint16_t i = 0; i < 256; i++) {
    uint32_t sequenceValue = generator32.next();
    ulinteger mockUlintegerSeq(sequenceValue);
    ASSERT_EQ(mockUlintegerSeq.getValue(), sequenceValue);
  }

  // unsigned long can be instantiated with a serializedUlinteger vector
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
    std::vector<uint8_t> serializedUlinteger = {(uint8_t)entryType::ULINTEGER, 4, byte1, byte2, byte3, byte4};
    ulinteger mockUlintegerSeq(serializedUlinteger);
    ASSERT_EQ(isValidUlinteger(serializedUlinteger), true);
    ASSERT_EQ(mockUlintegerSeq.getValue(), sequenceValue);
  }
}

TEST(ulintegerMethods, ulintegerSerialization) {
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
    ulinteger mockUlintegerSeq(sequenceValue);
    ASSERT_EQ(mockUlintegerSeq.getValue(), sequenceValue);

    std::vector<uint8_t> serializedUlinteger = {(uint8_t)entryType::ULINTEGER, 4, byte1, byte2, byte3, byte4};
    ASSERT_EQ(mockUlintegerSeq.getBytes(), serializedUlinteger);
    ulinteger mockUlintegerSeqPrevious(sequenceValue);
    ulinteger mockUlintegerSeqNew(mockUlintegerSeq.getBytes());
    ASSERT_EQ(mockUlintegerSeqNew.getValue(), mockUlintegerSeqPrevious.getValue());
  }
}