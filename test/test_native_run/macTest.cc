#include <gtest/gtest.h>
#include <mac.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(macMethods, macCreateRead) {
  sequencer generator8(0, 255);
  // mac can be instantiated without arguments, resulting in a fully zero'd out mac
  mac mockMac;
  std::array<uint8_t, 6> compareMac = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  ASSERT_EQ(mockMac.getArray(), compareMac);
  ASSERT_EQ(mockMac.getString(), "00:00:00:00:00:00");
  // mac can be instantiated with 6 uint8_t octets as arguments
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    uint8_t octet5 = generator8.next();
    mac mockMacSeq(octet0, octet1, octet2, octet3, octet4, octet5);
    std::array<uint8_t, 6> compareMacSeqArray = {octet0, octet1, octet2, octet3, octet4, octet5};
    char hexCharBytes[18];
    sprintf(hexCharBytes, "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX", octet0, octet1, octet2, octet3, octet4, octet5);
    std::string compareMacSeqString = hexCharBytes;
    ASSERT_EQ(mockMacSeq.getArray(), compareMacSeqArray);
    ASSERT_EQ(mockMacSeq.getString(), compareMacSeqString);
  }
  // mac can be instantiated with a string argument in the format "XX:XX:XX:XX:XX:XX"
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    uint8_t octet5 = generator8.next();
    char hexCharBytes[18];
    sprintf(hexCharBytes, "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX", octet0, octet1, octet2, octet3, octet4, octet5);
    std::string macSeqString = hexCharBytes;
    mac mockMacSeq(macSeqString);
    std::array<uint8_t, 6> compareMacSeqArray = {octet0, octet1, octet2, octet3, octet4, octet5};
    ASSERT_EQ(mockMacSeq.getArray(), compareMacSeqArray);
    ASSERT_EQ(mockMacSeq.getString(), macSeqString);
  }
}