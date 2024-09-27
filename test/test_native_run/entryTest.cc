#include <entry/entry.h>
#include <gtest/gtest.h>
#include <sequencer.h>

#define GTEST_COUT std::cout
// TEST(entryMethods, entryCreateReadUnknown) {
//   boolean booleanData(true);

//   std::vector<uint8_t> data = booleanData.getBytes();
//   uint32_t dataSize = data.size();
//   GTEST_COUT << printf("       SIZE: %d\n", dataSize);
//   for (uint32_t i = 0; i < dataSize; i++) {
//     GTEST_COUT << printf("       BYTE: %d\n", data[i]);
//   }

//   entry booleanEntry(20, booleanData);

//   GTEST_COUT << printf("       ID: %d\n", booleanEntry.getId());
//   std::vector<uint8_t> bytes = booleanEntry.getBytes();
//   uint32_t bytesSize = bytes.size();
//   GTEST_COUT << printf("       SIZE: %d\n", bytesSize);
//   for (uint32_t i = 0; i < bytesSize; i++) {
//     GTEST_COUT << printf("       BYTE: %d\n", bytes[i]);
//   }

//   ASSERT_EQ(booleanEntry.getId(), 20);
//   boolean readBoolean(booleanEntry.getBytes());
//   bool booleanValue = readBoolean.getValue();
//   ASSERT_EQ(booleanValue, true);
//   ASSERT_EQ(booleanEntry.getType(), entryType::BOOLEAN);
// }
// TEST(entryMethods, entryCreateSetGetPushPull) {
//   sequencer generator8(0, 255);
//   sequencer generator16(0, 65535, 500);
//   sequencer generator32(0, 4294967255, 100000000);
//   // instantiate entry without arguments
//   entry mockEntry;
//   // base tests
//   // ensure that the entry object was created properly
//   ASSERT_EQ(mockEntry.getId(), 0);
//   ASSERT_EQ(mockEntry.getDataSize(), 0);
//   // assign and check all entryType cases
//   mockEntry.setType(entryType::UINT8);
//   ASSERT_EQ(mockEntry.getType(), entryType::UINT8);
//   mockEntry.setType(entryType::UINT32);
//   ASSERT_EQ(mockEntry.getType(), entryType::UINT32);
//   mockEntry.setType(entryType::UINT16);
//   ASSERT_EQ(mockEntry.getType(), entryType::UINT16);
//   mockEntry.setType(entryType::MAC);
//   ASSERT_EQ(mockEntry.getType(), entryType::MAC);
//   mockEntry.setType(entryType::IP);
//   ASSERT_EQ(mockEntry.getType(), entryType::IP);
//   mockEntry.setType(entryType::STRING);
//   ASSERT_EQ(mockEntry.getType(), entryType::STRING);
//   mockEntry.setType(entryType::DIGITAL);
//   ASSERT_EQ(mockEntry.getType(), entryType::DIGITAL);
//   // test that data can be freely assigned and read from the entry object
//   for (uint16_t i = 0; i < 256; i++) {
//     uint8_t mockVectorLength = generator8.next();
//     std::vector<uint8_t> mockVector;
//     for (uint16_t i = 0; i < mockVectorLength; i++) {
//       uint8_t sequenceByte = generator8.next();
//       mockVector.push_back(sequenceByte);
//     }
//     mockEntry.setData(mockVector);
//     ASSERT_EQ(mockEntry.getDataSize(), mockVector.size());
//     ASSERT_EQ(mockEntry.getData(), mockVector);
//   }
//   // test that digital data can be pushed and pulled
//   mockEntry.setDigital(true);
//   ASSERT_EQ(mockEntry.getDigital(), true);
//   mockEntry.setDigital(false);
//   ASSERT_EQ(mockEntry.getDigital(), false);
//   ASSERT_EQ(mockEntry.isType(entryType::UNKNOWN), false);
//   ASSERT_EQ(mockEntry.isType(entryType::DIGITAL), true);
//   ASSERT_EQ(mockEntry.isType(entryType::UINT8), false);
//   ASSERT_EQ(mockEntry.isType(entryType::UINT16), false);
//   ASSERT_EQ(mockEntry.isType(entryType::UINT32), false);
//   ASSERT_EQ(mockEntry.isType(entryType::STRING), false);
//   ASSERT_EQ(mockEntry.isType(entryType::MAC), false);
//   ASSERT_EQ(mockEntry.isType(entryType::IP), false);
//   // test that uint8 data can be pushed and pulled
//   for (uint16_t i = 0; i < 256; i++) {
//     uint8_t sequenceAnalog8 = generator8.next();
//     mockEntry.setAnalog8(sequenceAnalog8);
//     ASSERT_EQ(mockEntry.getAnalog8(), sequenceAnalog8);
//   }
//   ASSERT_EQ(mockEntry.isType(entryType::UNKNOWN), false);
//   ASSERT_EQ(mockEntry.isType(entryType::DIGITAL), false);
//   ASSERT_EQ(mockEntry.isType(entryType::UINT8), true);
//   ASSERT_EQ(mockEntry.isType(entryType::UINT16), false);
//   ASSERT_EQ(mockEntry.isType(entryType::UINT32), false);
//   ASSERT_EQ(mockEntry.isType(entryType::STRING), false);
//   ASSERT_EQ(mockEntry.isType(entryType::MAC), false);
//   ASSERT_EQ(mockEntry.isType(entryType::IP), false);
//   // test that uint16 data can be pushed and pulled
//   for (uint16_t i = 0; i < 256; i++) {
//     uint16_t sequenceAnalog16 = generator16.next();
//     mockEntry.setAnalog16(sequenceAnalog16);
//     ASSERT_EQ(mockEntry.getAnalog16(), sequenceAnalog16);
//   }
//   ASSERT_EQ(mockEntry.isType(entryType::UNKNOWN), false);
//   ASSERT_EQ(mockEntry.isType(entryType::DIGITAL), false);
//   ASSERT_EQ(mockEntry.isType(entryType::UINT8), false);
//   ASSERT_EQ(mockEntry.isType(entryType::UINT16), true);
//   ASSERT_EQ(mockEntry.isType(entryType::UINT32), false);
//   ASSERT_EQ(mockEntry.isType(entryType::STRING), false);
//   ASSERT_EQ(mockEntry.isType(entryType::MAC), false);
//   ASSERT_EQ(mockEntry.isType(entryType::IP), false);
//   // test that uint32 data can be pushed and pulled
//   for (uint16_t i = 0; i < 256; i++) {
//     uint32_t sequenceAnalog32 = generator32.next();
//     mockEntry.setAnalog32(sequenceAnalog32);
//     ASSERT_EQ(mockEntry.getAnalog32(), sequenceAnalog32);
//   }
//   ASSERT_EQ(mockEntry.isType(entryType::UNKNOWN), false);
//   ASSERT_EQ(mockEntry.isType(entryType::DIGITAL), false);
//   ASSERT_EQ(mockEntry.isType(entryType::UINT8), false);
//   ASSERT_EQ(mockEntry.isType(entryType::UINT16), false);
//   ASSERT_EQ(mockEntry.isType(entryType::UINT32), true);
//   ASSERT_EQ(mockEntry.isType(entryType::STRING), false);
//   ASSERT_EQ(mockEntry.isType(entryType::MAC), false);
//   ASSERT_EQ(mockEntry.isType(entryType::IP), false);
//   // test that string data can be pushed and pulled
//   for (uint16_t i = 0; i < 256; i++) {
//     uint8_t sequenceStringLength = generator8.next();
//     std::string sequenceString;
//     for (uint16_t i = 0; i < sequenceStringLength; i++) {
//       char stringCharacter = generator8.next();
//       sequenceString += stringCharacter;
//     }
//     mockEntry.setString(sequenceString);
//     ASSERT_EQ(mockEntry.getString(), sequenceString);
//     ASSERT_EQ(mockEntry.isType(entryType::UNKNOWN), false);
//     ASSERT_EQ(mockEntry.isType(entryType::DIGITAL), false);
//     ASSERT_EQ(mockEntry.isType(entryType::UINT8), false);
//     ASSERT_EQ(mockEntry.isType(entryType::UINT16), false);
//     ASSERT_EQ(mockEntry.isType(entryType::UINT32), false);
//     ASSERT_EQ(mockEntry.isType(entryType::STRING), true);
//     ASSERT_EQ(mockEntry.isType(entryType::MAC), false);
//     ASSERT_EQ(mockEntry.isType(entryType::IP), false);
//   }
//   // test that mac data can be pushed and pulled
//   for (uint16_t i = 0; i < 256; i++) {
//     uint8_t octet0 = generator8.next();
//     uint8_t octet1 = generator8.next();
//     uint8_t octet2 = generator8.next();
//     uint8_t octet3 = generator8.next();
//     uint8_t octet4 = generator8.next();
//     uint8_t octet5 = generator8.next();
//     mac sequenceMac(octet0, octet1, octet2, octet3, octet4, octet5);
//     mockEntry.setMac(sequenceMac);
//     ASSERT_EQ(mockEntry.getMac().getArray(), sequenceMac.getArray());
//     ASSERT_EQ(mockEntry.isType(entryType::UNKNOWN), false);
//     ASSERT_EQ(mockEntry.isType(entryType::DIGITAL), false);
//     ASSERT_EQ(mockEntry.isType(entryType::UINT8), false);
//     ASSERT_EQ(mockEntry.isType(entryType::UINT16), false);
//     ASSERT_EQ(mockEntry.isType(entryType::UINT32), false);
//     ASSERT_EQ(mockEntry.isType(entryType::STRING), false);
//     ASSERT_EQ(mockEntry.isType(entryType::MAC), true);
//     ASSERT_EQ(mockEntry.isType(entryType::IP), false);
//   }
//   // test that ip data can be pushed and pulled
//   for (uint16_t i = 0; i < 256; i++) {
//     uint8_t octet0 = generator8.next();
//     uint8_t octet1 = generator8.next();
//     uint8_t octet2 = generator8.next();
//     uint8_t octet3 = generator8.next();
//     ip sequenceIp(octet0, octet1, octet2, octet3);
//     mockEntry.setIp(sequenceIp);
//     ASSERT_EQ(mockEntry.getIp().getArray(), sequenceIp.getArray());
//     ASSERT_EQ(mockEntry.isType(entryType::UNKNOWN), false);
//     ASSERT_EQ(mockEntry.isType(entryType::DIGITAL), false);
//     ASSERT_EQ(mockEntry.isType(entryType::UINT8), false);
//     ASSERT_EQ(mockEntry.isType(entryType::UINT16), false);
//     ASSERT_EQ(mockEntry.isType(entryType::UINT32), false);
//     ASSERT_EQ(mockEntry.isType(entryType::STRING), false);
//     ASSERT_EQ(mockEntry.isType(entryType::MAC), false);
//     ASSERT_EQ(mockEntry.isType(entryType::IP), true);
//   }
// }

// TEST(entryMethods, createNewDigitalEntry) {
//   sequencer generator8(0, 255);
//   for (uint16_t i = 0; i < 256; i++) {
//     uint8_t target = generator8.next();
//     bool value = true;
//     entry mockEntry = createDigitalEntry(target, value);
//     ASSERT_EQ(mockEntry.getId(), target);
//     ASSERT_EQ(mockEntry.getType(), entryType::DIGITAL);
//     ASSERT_EQ(mockEntry.getDigital(), value);
//     value = false;
//     mockEntry = createDigitalEntry(target, value);
//     ASSERT_EQ(mockEntry.getId(), target);
//     ASSERT_EQ(mockEntry.getType(), entryType::DIGITAL);
//     ASSERT_EQ(mockEntry.getDigital(), value);
//   }
// }

// TEST(entryMethods, createNewAnalog8Entry) {
//   sequencer generator8(0, 255);
//   for (uint16_t i = 0; i < 256; i++) {
//     uint8_t target = generator8.next();
//     uint8_t value = generator8.next();
//     entry mockEntry = createAnalog8Entry(target, value);
//     ASSERT_EQ(mockEntry.getId(), target);
//     ASSERT_EQ(mockEntry.getType(), entryType::UINT8);
//     ASSERT_EQ(mockEntry.getAnalog8(), value);
//   }
// }

// TEST(entryMethods, createNewAnalog16Entry) {
//   sequencer generator8(0, 255);
//   sequencer generator16(0, 65535, 500);
//   for (uint16_t i = 0; i < 256; i++) {
//     uint8_t target = generator8.next();
//     uint16_t value = generator16.next();
//     entry mockEntry = createAnalog16Entry(target, value);
//     ASSERT_EQ(mockEntry.getId(), target);
//     ASSERT_EQ(mockEntry.getType(), entryType::UINT16);
//     ASSERT_EQ(mockEntry.getAnalog16(), value);
//   }
// }

// TEST(entryMethods, createNewAnalog32Entry) {
//   sequencer generator8(0, 255);
//   sequencer generator32(0, 4294967255, 100000000);
//   for (uint16_t i = 0; i < 256; i++) {
//     uint8_t target = generator8.next();
//     uint32_t value = generator32.next();
//     entry mockEntry = createAnalog32Entry(target, value);
//     ASSERT_EQ(mockEntry.getId(), target);
//     ASSERT_EQ(mockEntry.getType(), entryType::UINT32);
//     ASSERT_EQ(mockEntry.getAnalog32(), value);
//   }
// }

// TEST(entryMethods, createNewStringEntry) {
//   sequencer generator8(0, 255);
//   for (uint16_t i = 0; i < 256; i++) {
//     uint8_t target = generator8.next();
//     uint8_t sequenceStringLength = generator8.next();
//     std::string sequenceString;
//     for (uint16_t i = 0; i < sequenceStringLength; i++) {
//       char stringCharacter = generator8.next();
//       sequenceString += stringCharacter;
//     }
//     std::string value = sequenceString;
//     entry mockEntry = createStringEntry(target, value);
//     ASSERT_EQ(mockEntry.getId(), target);
//     ASSERT_EQ(mockEntry.getType(), entryType::STRING);
//     ASSERT_EQ(mockEntry.getString(), value);
//   }
// }

// TEST(entryMethods, createNewMacEntry) {
//   sequencer generator8(0, 255);
//   for (uint16_t i = 0; i < 256; i++) {
//     uint8_t target = generator8.next();
//     uint8_t octet0 = generator8.next();
//     uint8_t octet1 = generator8.next();
//     uint8_t octet2 = generator8.next();
//     uint8_t octet3 = generator8.next();
//     uint8_t octet4 = generator8.next();
//     uint8_t octet5 = generator8.next();
//     mac sequenceMac(octet0, octet1, octet2, octet3, octet4, octet5);
//     mac value = sequenceMac;
//     entry mockEntry = createMacEntry(target, value);
//     ASSERT_EQ(mockEntry.getId(), target);
//     ASSERT_EQ(mockEntry.getType(), entryType::MAC);
//     ASSERT_EQ(mockEntry.getMac().getArray(), value.getArray());
//   }
// }

// TEST(entryMethods, createNewIpEntry) {
//   sequencer generator8(0, 255);
//   for (uint16_t i = 0; i < 256; i++) {
//     uint8_t target = generator8.next();
//     uint8_t octet0 = generator8.next();
//     uint8_t octet1 = generator8.next();
//     uint8_t octet2 = generator8.next();
//     uint8_t octet3 = generator8.next();
//     ip sequenceIp(octet0, octet1, octet2, octet3);
//     ip value = sequenceIp;
//     entry mockEntry = createIpEntry(target, value);
//     ASSERT_EQ(mockEntry.getId(), target);
//     ASSERT_EQ(mockEntry.getType(), entryType::IP);
//     ASSERT_EQ(mockEntry.getIp().getArray(), value.getArray());
//   }
// }