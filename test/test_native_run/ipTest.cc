#include <gtest/gtest.h>
#include <ip.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(ipMethods, ipCreateRead) {
  sequencer generator8(0, 255);
  // ip can be instantiated without arguments, resulting in a fully zero'd out ip
  ip mockIp;
  std::array<uint8_t, 4> compareIp = {0, 0, 0, 0};
  ASSERT_EQ(mockIp.getArray(), compareIp);
  ASSERT_EQ(mockIp.getString(), "0.0.0.0");
  // ip can be instantiated with 4 uint8_t octets as arguments
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    ip mockIpSeq(octet0, octet1, octet2, octet3);
    std::array<uint8_t, 4> compareIpSeqArray = {octet0, octet1, octet2, octet3};
    char hexCharBytes[18];
    sprintf(hexCharBytes, "%hu.%hu.%hu.%hu", octet0, octet1, octet2, octet3);
    std::string compareIpSeqString = hexCharBytes;
    ASSERT_EQ(mockIpSeq.getArray(), compareIpSeqArray);
    ASSERT_EQ(mockIpSeq.getString(), compareIpSeqString);
  }
  // ip can be instantiated with a string argument in the format "X.X.X.X"
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    char hexCharBytes[18];
    sprintf(hexCharBytes, "%hu.%hu.%hu.%hu", octet0, octet1, octet2, octet3);
    std::string ipSeqString = hexCharBytes;
    ip mockIpSeq(ipSeqString);
    std::array<uint8_t, 4> compareIpSeqArray = {octet0, octet1, octet2, octet3};
    ASSERT_EQ(mockIpSeq.getArray(), compareIpSeqArray);
    ASSERT_EQ(mockIpSeq.getString(), ipSeqString);
  }
}