#include <gtest/gtest.h>
#include <message.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

// #define SAMPLE_MESSAGE_STRING_1 "02473623A28527#34A33245#6523#234545#65948322"

TEST(messageMethods, messageConstruction) {
  sequencer generator8(0, 255);
  // message can be instantiated without arguments, resulting in a fully zero'd out message
  message mockMessageBlank;
  ASSERT_EQ(mockMessageBlank.getIdTyp(), idType::UNDEFINED);
  ASSERT_EQ(mockMessageBlank.getIdAdd().getArray(), mac(0x00, 0x00, 0x00, 0x00, 0x00, 0x00).getArray());
  ASSERT_EQ(mockMessageBlank.getPayload().size(), 0);

  // message can be instantiated with a vector<uint8_t>, resulting in a message derrived from the parsed string
  // undersized vector
  std::vector<uint8_t> undersizedVector;
  undersizedVector.push_back(generator8.next());
  undersizedVector.push_back(generator8.next());
  undersizedVector.push_back(generator8.next());
  message undersizedVectorMessage(undersizedVector);
  ASSERT_EQ(mockMessageBlank.getIdTyp(), idType::UNDEFINED);
  ASSERT_EQ(mockMessageBlank.getIdAdd().getArray(), mac(0x00, 0x00, 0x00, 0x00, 0x00, 0x00).getArray());
  ASSERT_EQ(mockMessageBlank.getPayload().size(), 0);

  // uint8_t messageRestartType = (uint8_t)idType::DEVICE_RESTART;
  // uint8_t messageRestartAddOctet0 = generator8.next();
  // uint8_t messageRestartAddOctet1 = generator8.next();
  // uint8_t messageRestartAddOctet2 = generator8.next();
  // uint8_t messageRestartAddOctet3 = generator8.next();
  // uint8_t messageRestartAddOctet4 = generator8.next();
  // uint8_t messageRestartAddOctet5 = generator8.next();
  // mac messageRestartAdd(messageRestartAddOctet0, messageRestartAddOctet1, messageRestartAddOctet2,
  //                       messageRestartAddOctet3, messageRestartAddOctet4, messageRestartAddOctet5);

  // std::string messageRestartString;
  // messageRestartString += uint8tToString(messageRestartType);
  // messageRestartString += uint8tToString(messageRestartAddOctet0);
  // messageRestartString += uint8tToString(messageRestartAddOctet1);
  // messageRestartString += uint8tToString(messageRestartAddOctet2);
  // messageRestartString += uint8tToString(messageRestartAddOctet3);
  // messageRestartString += uint8tToString(messageRestartAddOctet4);
  // messageRestartString += uint8tToString(messageRestartAddOctet5);
  // message mockMessageRestart(messageRestartString);
  // ASSERT_EQ(mockMessageRestart.getIdTyp(), idType::DEVICE_RESTART);
  // ASSERT_EQ(mockMessageRestart.getIdAdd().getArray(), messageRestartAdd.getArray());
  // ASSERT_EQ(mockMessageRestart.getPayload().size(), 0);
  // // DEVICE_PURGE
  // uint8_t messagePurgeType = (uint8_t)idType::DEVICE_PURGE;
  // uint8_t messagePurgeAddOctet0 = generator8.next();
  // uint8_t messagePurgeAddOctet1 = generator8.next();
  // uint8_t messagePurgeAddOctet2 = generator8.next();
  // uint8_t messagePurgeAddOctet3 = generator8.next();
  // uint8_t messagePurgeAddOctet4 = generator8.next();
  // uint8_t messagePurgeAddOctet5 = generator8.next();
  // mac messagePurgeAdd(messagePurgeAddOctet0, messagePurgeAddOctet1, messagePurgeAddOctet2, messagePurgeAddOctet3,
  //                     messagePurgeAddOctet4, messagePurgeAddOctet5);
  // std::string messagePurgeString;
  // messagePurgeString += uint8tToString(messagePurgeType);
  // messagePurgeString += uint8tToString(messagePurgeAddOctet0);
  // messagePurgeString += uint8tToString(messagePurgeAddOctet1);
  // messagePurgeString += uint8tToString(messagePurgeAddOctet2);
  // messagePurgeString += uint8tToString(messagePurgeAddOctet3);
  // messagePurgeString += uint8tToString(messagePurgeAddOctet4);
  // messagePurgeString += uint8tToString(messagePurgeAddOctet5);
  // message mockMessagePurge(messagePurgeString);
  // ASSERT_EQ(mockMessagePurge.getIdTyp(), idType::DEVICE_PURGE);
  // ASSERT_EQ(mockMessagePurge.getIdAdd().getArray(), messagePurgeAdd.getArray());
  // ASSERT_EQ(mockMessagePurge.getPayload().size(), 0);
  // // CONFIGBLOCK_REPORT
  // uint8_t messageCfgRptType = (uint8_t)idType::CONFIGBLOCK_REPORT;
  // uint8_t messageCfgRptAddOctet0 = generator8.next();
  // uint8_t messageCfgRptAddOctet1 = generator8.next();
  // uint8_t messageCfgRptAddOctet2 = generator8.next();
  // uint8_t messageCfgRptAddOctet3 = generator8.next();
  // uint8_t messageCfgRptAddOctet4 = generator8.next();
  // uint8_t messageCfgRptAddOctet5 = generator8.next();
  // mac messageCfgRptAdd(messageCfgRptAddOctet0, messageCfgRptAddOctet1, messageCfgRptAddOctet2,
  // messageCfgRptAddOctet3,
  //                      messageCfgRptAddOctet4, messageCfgRptAddOctet5);
  // uint8_t messageCfgRptData1 = generator8.next();
  // uint8_t messageCfgRptData2 = generator8.next();
  // std::string messageCfgRptString;
  // messageCfgRptString += uint8tToString(messageCfgRptType);
  // messageCfgRptString += uint8tToString(messageCfgRptAddOctet0);
  // messageCfgRptString += uint8tToString(messageCfgRptAddOctet1);
  // messageCfgRptString += uint8tToString(messageCfgRptAddOctet2);
  // messageCfgRptString += uint8tToString(messageCfgRptAddOctet3);
  // messageCfgRptString += uint8tToString(messageCfgRptAddOctet4);
  // messageCfgRptString += uint8tToString(messageCfgRptAddOctet5);
  // messageCfgRptString += '#';
  // messageCfgRptString += uint8tToString(messageCfgRptData1);
  // messageCfgRptString += '#';
  // messageCfgRptString += uint8tToString(messageCfgRptData2);
  // GTEST_COUT << printf("string: %s\n", messageCfgRptString.c_str()) << std::endl;
  // message mockMessageCfgRpt(messageCfgRptString);
  // ASSERT_EQ(mockMessageCfgRpt.getIdTyp(), idType::CONFIGBLOCK_REPORT);
  // ASSERT_EQ(mockMessageCfgRpt.getIdAdd().getArray(), messageCfgRptAdd.getArray());
  // ASSERT_EQ(mockMessageCfgRpt.getPayload().size(), 2);

  //    message mockMessage;
  //    mac blankMacAddress = mac(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
  //    EXPECT_EQ(mockMessage.getIdTyp(), idType::UNDEFINED);
  //    EXPECT_EQ(mockMessage.getIdAdd().getArray(), blankMacAddress.getArray());
  //    EXPECT_EQ(mockMessage.getPayload().size(), 0);
  //    // message can be instantiated with a std::string as an argument
  //    for (uint8_t i = 0; i < 255; i++) {
  //      std::string messageString;
  //      std::vector<idType> idTypeChoices = {
  //          idType::UNDEFINED,        idType::DEVICE_RESTART,    idType::DEVICE_PURGE, idType::CONFIGBLOCK_REPORT,
  //          idType::DATABLOCK_REPORT, idType::LOGICBLOCK_REPORT, idType::DISPLAYBLOCK_REPORT,
  //          idType::CONFIGBLOCK_UPDATE, idType::DATABLOCK_UPDATE, idType::LOGICBLOCK_UPDATE,
  //          idType::DISPLAYBLOCK_UPDATE};
  //      uint8_t idTypeChoicesSize = idTypeChoices.size();

  //     // idType randomIdType = idTypeChoices[rand() % 6];
  //     message mockMessageRandString;
  //   }
}

// TEST(messageMethods, randomNumbers) { uint8_t something = rand() % 100; }

// TEST(messageMethods, messageSetGetIdTyp) {
//   message mockNewMessage;
//   mockNewMessage.setIdTyp(idType::CONFIGBLOCK_UPDATE);
//   EXPECT_EQ(mockNewMessage.getIdTyp(), idType::CONFIGBLOCK_UPDATE);
// }

// TEST(messageMethods, messageSetGetIdAdd) {
//   message mockNewMessage;
//   mockNewMessage.setIdAdd(mac(0x23, 0x34, 0xA3, 0x76, 0x43, 0x88));
//   EXPECT_EQ(mockNewMessage.getIdAdd().getArray(), mac(0x23, 0x34, 0xA3, 0x76, 0x43, 0x88).getArray());
// }

// TEST(messageMethods, messageSetGetPayload) {
//   message mockNewMessage;
//   std::vector<dataEntry> mockPayload;
//   dataEntry mockDataEntryDigital(0x00);
//   dataEntry mockDataEntryUInt8(0x01);
//   dataEntry mockDataEntryUInt16(0x02);
//   dataEntry mockDataEntryUInt32(0x03);
//   dataEntry mockDataEntryString(0x04);
//   dataEntry mockDataEntryMac(0x05);
//   dataEntry mockDataEntryIp(0x06);
//   mockDataEntryDigital.pushDigital(true);
//   mockDataEntryUInt8.pushAnalogUInt8(255);
//   mockDataEntryUInt16.pushAnalogUInt16(65535);
//   mockDataEntryUInt32.pushAnalogUInt32(4294967295);
//   mockDataEntryString.pushString("This is a string");
//   mockDataEntryMac.pushMac(mac(0x45, 0xA3, 0x87, 0x92, 0x12, 0x22));
//   mockDataEntryIp.pushIp(ip(192, 168, 10, 112));
//   mockPayload.push_back(mockDataEntryDigital);
//   mockPayload.push_back(mockDataEntryUInt8);
//   mockPayload.push_back(mockDataEntryUInt16);
//   mockPayload.push_back(mockDataEntryUInt32);
//   mockPayload.push_back(mockDataEntryString);
//   mockPayload.push_back(mockDataEntryMac);
//   mockPayload.push_back(mockDataEntryIp);
//   mockNewMessage.setPayload(mockPayload);
//   EXPECT_EQ(mockNewMessage.getPayload()[0].pullDigital().second, true);
//   EXPECT_EQ(mockNewMessage.getPayload()[1].pullAnalogUInt8().second, 255);
//   EXPECT_EQ(mockNewMessage.getPayload()[2].pullAnalogUInt16().second, 65535);
//   EXPECT_EQ(mockNewMessage.getPayload()[3].pullAnalogUInt32().second, 4294967295);
//   EXPECT_EQ(mockNewMessage.getPayload()[4].pullString().second, "This is a string");
//   EXPECT_EQ(mockNewMessage.getPayload()[5].pullMac().second.getArray(),
//             mac(0x45, 0xA3, 0x87, 0x92, 0x12, 0x22).getArray());
//   EXPECT_EQ(mockNewMessage.getPayload()[6].pullIp().second.getArray(), ip(192, 168, 10, 112).getArray());
// }

// TEST(messageMethods, messageFromStringToString) {
//   message mockNewMessage;
//   mockNewMessage.fromString(SAMPLE_MESSAGE_STRING_1);
//   std::string mockString = mockNewMessage.toString();
//   EXPECT_EQ(mockString, SAMPLE_MESSAGE_STRING_1);
// }

// TEST(messageQueueMethods, messageQueueConstruction) {
//   messageQueue mockNewMessageQueue;
//   EXPECT_EQ(mockNewMessageQueue.read().first, operationStatus::FAIL);
// }

// TEST(messageQueueMethods, messageQueuePushPopReadPurge) {
//   messageQueue mockNewMessageQueue;
//   std::vector<dataEntry> mockPayload1;
//   dataEntry mockDataEntryUInt8(0x01);
//   mockDataEntryUInt8.pushAnalogUInt8(255);
//   mockPayload1.push_back(mockDataEntryUInt8);

//   std::vector<dataEntry> mockPayload2;
//   dataEntry mockDataEntryString(0x04);
//   mockDataEntryString.pushString("This is a string");
//   mockPayload2.push_back(mockDataEntryString);

//   mockNewMessageQueue.push(idType::DATABLOCK_UPDATE, mac(0x23, 0x43, 0xA3, 0x89, 0x12, 0x45), mockPayload1);
//   mockNewMessageQueue.push(idType::CONFIGBLOCK_REPORT, mac(0x34, 0x65, 0xB4, 0x78, 0x35, 0x90), mockPayload2);

//   EXPECT_EQ(mockNewMessageQueue.read().first, operationStatus::SUCCESS);
//   EXPECT_EQ(mockNewMessageQueue.read().second.getIdAdd().getArray(),
//             mac(0x23, 0x43, 0xA3, 0x89, 0x12, 0x45).getArray());
//   EXPECT_EQ(mockNewMessageQueue.read().second.getPayload()[0].getIdTgt(), 0x01);
//   EXPECT_EQ(mockNewMessageQueue.read().second.getPayload()[0].getData().size(), 1);
//   EXPECT_EQ(mockNewMessageQueue.read().second.getPayload()[0].pullAnalogUInt8().second, 255);

//   mockNewMessageQueue.pop();

//   EXPECT_EQ(mockNewMessageQueue.read().first, operationStatus::SUCCESS);
//   EXPECT_EQ(mockNewMessageQueue.read().second.getIdAdd().getArray(),
//             mac(0x34, 0x65, 0xB4, 0x78, 0x35, 0x90).getArray());
//   EXPECT_EQ(mockNewMessageQueue.read().second.getPayload()[0].getIdTgt(), 0x04);
//   EXPECT_GE(mockNewMessageQueue.read().second.getPayload()[0].getData().size(), 1);
//   EXPECT_EQ(mockNewMessageQueue.read().second.getPayload()[0].pullString().second, "This is a string");

//   mockNewMessageQueue.purge();

//   EXPECT_EQ(mockNewMessageQueue.read().first, operationStatus::FAIL);
// }