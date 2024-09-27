#include <gtest/gtest.h>
#include <ip/ip.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(ipMethods, ipCreateRead) {
  sequencer generator8(0, 255);

  // ip can be instantiated with 4 uint8_t octets as arguments
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    char hexCharBytes[18];
    sprintf(hexCharBytes, "%hu.%hu.%hu.%hu", octet1, octet2, octet3, octet4);
    std::string compareIpSeqString = hexCharBytes;
    std::array<uint8_t, 4> compareIpSeqArray = {octet1, octet2, octet3, octet4};
    ip mockIpSeq(octet1, octet2, octet3, octet4);
    ASSERT_EQ(mockIpSeq.getArray(), compareIpSeqArray);
    ASSERT_EQ(mockIpSeq.getString(), compareIpSeqString);
    ASSERT_EQ(mockIpSeq.getOctet1(), octet1);
    ASSERT_EQ(mockIpSeq.getOctet2(), octet2);
    ASSERT_EQ(mockIpSeq.getOctet3(), octet3);
    ASSERT_EQ(mockIpSeq.getOctet4(), octet4);
  }

  // ip can be instantiated with a string argument in the format "X.X.X.X"
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    char hexCharBytes[18];
    sprintf(hexCharBytes, "%hu.%hu.%hu.%hu", octet1, octet2, octet3, octet4);
    std::string ipSeqString = hexCharBytes;
    std::array<uint8_t, 4> compareIpSeqArray = {octet1, octet2, octet3, octet4};
    ip mockIpSeq(ipSeqString);
    ASSERT_EQ(mockIpSeq.getArray(), compareIpSeqArray);
    ASSERT_EQ(mockIpSeq.getString(), ipSeqString);
    ASSERT_EQ(mockIpSeq.getOctet1(), octet1);
    ASSERT_EQ(mockIpSeq.getOctet2(), octet2);
    ASSERT_EQ(mockIpSeq.getOctet3(), octet3);
    ASSERT_EQ(mockIpSeq.getOctet4(), octet4);
  }

  // ip can be instantiated with a serializedIp vector
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    char hexCharBytes[18];
    sprintf(hexCharBytes, "%hu.%hu.%hu.%hu", octet1, octet2, octet3, octet4);
    std::string ipSeqString = hexCharBytes;
    std::array<uint8_t, 4> compareIpSeqArray = {octet1, octet2, octet3, octet4};
    std::vector<uint8_t> serializedIp = {(uint8_t)entryType::IP, 4, octet1, octet2, octet3, octet4};
    ip mockIpSeq(serializedIp);
    ASSERT_EQ(mockIpSeq.getArray(), compareIpSeqArray);
    ASSERT_EQ(mockIpSeq.getString(), ipSeqString);
    ASSERT_EQ(mockIpSeq.getOctet1(), octet1);
    ASSERT_EQ(mockIpSeq.getOctet2(), octet2);
    ASSERT_EQ(mockIpSeq.getOctet3(), octet3);
    ASSERT_EQ(mockIpSeq.getOctet4(), octet4);
  }
}

TEST(ipMethods, ipSerialization) {
  sequencer generator8(0, 255);

  for (uint16_t i = 0; i < 256; i++) {
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    std::array<uint8_t, 4> compareIpSeqArray = {octet1, octet2, octet3, octet4};
    ip mockIpSeq(octet1, octet2, octet3, octet4);
    ASSERT_EQ(mockIpSeq.getArray(), compareIpSeqArray);

    std::vector<uint8_t> serializedIp = {(uint8_t)entryType::IP, 4, octet1, octet2, octet3, octet4};
    ASSERT_EQ(mockIpSeq.getBytes(), serializedIp);
    ip mockIpSeqPrevious(octet1, octet2, octet3, octet4);
    ip mockIpSeqNew(mockIpSeq.getBytes());
    ASSERT_EQ(mockIpSeqNew.getOctet1(), mockIpSeqPrevious.getOctet1());
    ASSERT_EQ(mockIpSeqNew.getOctet2(), mockIpSeqPrevious.getOctet2());
    ASSERT_EQ(mockIpSeqNew.getOctet3(), mockIpSeqPrevious.getOctet3());
    ASSERT_EQ(mockIpSeqNew.getOctet4(), mockIpSeqPrevious.getOctet4());
  }
}