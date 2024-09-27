#include <gtest/gtest.h>
#include <mac/mac.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(macMethods, macCreateRead) {
  sequencer generator8(0, 255);

  // mac can be instantiated with 6 uint8_t octets as arguments
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    uint8_t octet5 = generator8.next();
    uint8_t octet6 = generator8.next();
    char hexCharBytes[18];
    sprintf(hexCharBytes, "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX", octet1, octet2, octet3, octet4, octet5, octet6);
    std::string compareMacSeqString = hexCharBytes;
    std::array<uint8_t, 6> compareMacSeqArray = {octet1, octet2, octet3, octet4, octet5, octet6};
    mac mockMacSeq(octet1, octet2, octet3, octet4, octet5, octet6);
    ASSERT_EQ(mockMacSeq.getArray(), compareMacSeqArray);
    ASSERT_EQ(mockMacSeq.getString(), compareMacSeqString);
    ASSERT_EQ(mockMacSeq.getOctet1(), octet1);
    ASSERT_EQ(mockMacSeq.getOctet2(), octet2);
    ASSERT_EQ(mockMacSeq.getOctet3(), octet3);
    ASSERT_EQ(mockMacSeq.getOctet4(), octet4);
    ASSERT_EQ(mockMacSeq.getOctet5(), octet5);
    ASSERT_EQ(mockMacSeq.getOctet6(), octet6);
  }

  // mac can be instantiated with a string argument in the format "XX:XX:XX:XX:XX:XX"
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    uint8_t octet5 = generator8.next();
    uint8_t octet6 = generator8.next();
    char hexCharBytes[18];
    sprintf(hexCharBytes, "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX", octet1, octet2, octet3, octet4, octet5, octet6);
    std::string macSeqString = hexCharBytes;
    std::array<uint8_t, 6> compareMacSeqArray = {octet1, octet2, octet3, octet4, octet5, octet6};
    mac mockMacSeq(macSeqString);
    ASSERT_EQ(mockMacSeq.getArray(), compareMacSeqArray);
    ASSERT_EQ(mockMacSeq.getString(), macSeqString);
    ASSERT_EQ(mockMacSeq.getOctet1(), octet1);
    ASSERT_EQ(mockMacSeq.getOctet2(), octet2);
    ASSERT_EQ(mockMacSeq.getOctet3(), octet3);
    ASSERT_EQ(mockMacSeq.getOctet4(), octet4);
    ASSERT_EQ(mockMacSeq.getOctet5(), octet5);
    ASSERT_EQ(mockMacSeq.getOctet6(), octet6);
  }

  // mac can be instantiated with a serializedMac vector
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    uint8_t octet5 = generator8.next();
    uint8_t octet6 = generator8.next();
    char hexCharBytes[18];
    sprintf(hexCharBytes, "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX", octet1, octet2, octet3, octet4, octet5, octet6);
    std::string macSeqString = hexCharBytes;
    std::array<uint8_t, 6> compareMacSeqArray = {octet1, octet2, octet3, octet4, octet5, octet6};
    std::vector<uint8_t> serializedMac = {(uint8_t)entryType::MAC, 6, octet1, octet2, octet3, octet4, octet5, octet6};
    mac mockMacSeq(serializedMac);
    ASSERT_EQ(mockMacSeq.getArray(), compareMacSeqArray);
    ASSERT_EQ(mockMacSeq.getString(), macSeqString);
    ASSERT_EQ(mockMacSeq.getOctet1(), octet1);
    ASSERT_EQ(mockMacSeq.getOctet2(), octet2);
    ASSERT_EQ(mockMacSeq.getOctet3(), octet3);
    ASSERT_EQ(mockMacSeq.getOctet4(), octet4);
    ASSERT_EQ(mockMacSeq.getOctet5(), octet5);
    ASSERT_EQ(mockMacSeq.getOctet6(), octet6);
  }
}

TEST(macMethods, macSerialization) {
  sequencer generator8(0, 255);

  for (uint16_t i = 0; i < 256; i++) {
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    uint8_t octet5 = generator8.next();
    uint8_t octet6 = generator8.next();
    std::array<uint8_t, 6> compareMacSeqArray = {octet1, octet2, octet3, octet4, octet5, octet6};
    mac mockMacSeq(octet1, octet2, octet3, octet4, octet5, octet6);
    ASSERT_EQ(mockMacSeq.getArray(), compareMacSeqArray);

    std::vector<uint8_t> serializedMac = {(uint8_t)entryType::MAC, 6, octet1, octet2, octet3, octet4, octet5, octet6};
    ASSERT_EQ(mockMacSeq.getBytes(), serializedMac);
    mac mockMacSeqPrevious(octet1, octet2, octet3, octet4, octet5, octet6);
    mac mockMacSeqNew(mockMacSeq.getBytes());
    ASSERT_EQ(mockMacSeqNew.getOctet1(), mockMacSeqPrevious.getOctet1());
    ASSERT_EQ(mockMacSeqNew.getOctet2(), mockMacSeqPrevious.getOctet2());
    ASSERT_EQ(mockMacSeqNew.getOctet3(), mockMacSeqPrevious.getOctet3());
    ASSERT_EQ(mockMacSeqNew.getOctet4(), mockMacSeqPrevious.getOctet4());
    ASSERT_EQ(mockMacSeqNew.getOctet5(), mockMacSeqPrevious.getOctet5());
    ASSERT_EQ(mockMacSeqNew.getOctet6(), mockMacSeqPrevious.getOctet6());
  }
}