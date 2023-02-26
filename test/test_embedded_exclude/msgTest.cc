#include <message.h>
#include <gtest/gtest.h>

#define SAMPLE_MESSAGE_STRING_1 "02473623A28527#34A33245#6523#234545#65948322"

TEST(messageMethods, messageConstruction) {
  message mockNewMessage;
  EXPECT_EQ(mockNewMessage.getIdTyp(), idType::UNDEFINED);
  EXPECT_EQ(mockNewMessage.getIdAdd().getArray(), mac(0x00, 0x00, 0x00, 0x00, 0x00, 0x00).getArray());
  EXPECT_EQ(mockNewMessage.getPayload().size(), 0);
}

TEST(messageMethods, messageSetGetIdTyp) {
  message mockNewMessage;
  mockNewMessage.setIdTyp(idType::CONFIGBLOCK_UPDATE);
  EXPECT_EQ(mockNewMessage.getIdTyp(), idType::CONFIGBLOCK_UPDATE);
}

TEST(messageMethods, messageSetGetIdAdd) {
  message mockNewMessage;
  mockNewMessage.setIdAdd(mac(0x23, 0x34, 0xA3, 0x76, 0x43, 0x88));
  EXPECT_EQ(mockNewMessage.getIdAdd().getArray(), mac(0x23, 0x34, 0xA3, 0x76, 0x43, 0x88).getArray());
}

TEST(messageMethods, messageSetGetPayload) {
  message mockNewMessage;
  std::vector<dataEntry> mockPayload;
  dataEntry mockDataEntryDigital(0x00);
  dataEntry mockDataEntryUInt8(0x01);
  dataEntry mockDataEntryUInt16(0x02);
  dataEntry mockDataEntryUInt32(0x03);
  dataEntry mockDataEntryString(0x04);
  dataEntry mockDataEntryMac(0x05);
  dataEntry mockDataEntryIp(0x06);
  mockDataEntryDigital.pushDigital(true);
  mockDataEntryUInt8.pushAnalogUInt8(255);
  mockDataEntryUInt16.pushAnalogUInt16(65535);
  mockDataEntryUInt32.pushAnalogUInt32(4294967295);
  mockDataEntryString.pushString("This is a string");
  mockDataEntryMac.pushMac(mac(0x45, 0xA3, 0x87, 0x92, 0x12, 0x22));
  mockDataEntryIp.pushIp(ip(192, 168, 10, 112));
  mockPayload.push_back(mockDataEntryDigital);
  mockPayload.push_back(mockDataEntryUInt8);
  mockPayload.push_back(mockDataEntryUInt16);
  mockPayload.push_back(mockDataEntryUInt32);
  mockPayload.push_back(mockDataEntryString);
  mockPayload.push_back(mockDataEntryMac);
  mockPayload.push_back(mockDataEntryIp);
  mockNewMessage.setPayload(mockPayload);
  EXPECT_EQ(mockNewMessage.getPayload()[0].pullDigital().second, true);
  EXPECT_EQ(mockNewMessage.getPayload()[1].pullAnalogUInt8().second, 255);
  EXPECT_EQ(mockNewMessage.getPayload()[2].pullAnalogUInt16().second, 65535);
  EXPECT_EQ(mockNewMessage.getPayload()[3].pullAnalogUInt32().second, 4294967295);
  EXPECT_EQ(mockNewMessage.getPayload()[4].pullString().second, "This is a string");
  EXPECT_EQ(mockNewMessage.getPayload()[5].pullMac().second.getArray(),
            mac(0x45, 0xA3, 0x87, 0x92, 0x12, 0x22).getArray());
  EXPECT_EQ(mockNewMessage.getPayload()[6].pullIp().second.getArray(), ip(192, 168, 10, 112).getArray());
}

TEST(messageMethods, messageFromStringToString) {
  message mockNewMessage;
  mockNewMessage.fromString(SAMPLE_MESSAGE_STRING_1);
  std::string mockString = mockNewMessage.toString();
  EXPECT_EQ(mockString, SAMPLE_MESSAGE_STRING_1);
}

TEST(messageQueueMethods, messageQueueConstruction) {
  messageQueue mockNewMessageQueue;
  EXPECT_EQ(mockNewMessageQueue.read().first, operationStatus::FAIL);
}

TEST(messageQueueMethods, messageQueuePushPopReadPurge) {
  messageQueue mockNewMessageQueue;
  std::vector<dataEntry> mockPayload1;
  dataEntry mockDataEntryUInt8(0x01);
  mockDataEntryUInt8.pushAnalogUInt8(255);
  mockPayload1.push_back(mockDataEntryUInt8);

  std::vector<dataEntry> mockPayload2;
  dataEntry mockDataEntryString(0x04);
  mockDataEntryString.pushString("This is a string");
  mockPayload2.push_back(mockDataEntryString);

  mockNewMessageQueue.push(idType::DATABLOCK_UPDATE, mac(0x23, 0x43, 0xA3, 0x89, 0x12, 0x45), mockPayload1);
  mockNewMessageQueue.push(idType::CONFIGBLOCK_REPORT, mac(0x34, 0x65, 0xB4, 0x78, 0x35, 0x90), mockPayload2);

  EXPECT_EQ(mockNewMessageQueue.read().first, operationStatus::SUCCESS);
  EXPECT_EQ(mockNewMessageQueue.read().second.getIdAdd().getArray(),
            mac(0x23, 0x43, 0xA3, 0x89, 0x12, 0x45).getArray());
  EXPECT_EQ(mockNewMessageQueue.read().second.getPayload()[0].getIdTgt(), 0x01);
  EXPECT_EQ(mockNewMessageQueue.read().second.getPayload()[0].getData().size(), 1);
  EXPECT_EQ(mockNewMessageQueue.read().second.getPayload()[0].pullAnalogUInt8().second, 255);

  mockNewMessageQueue.pop();

  EXPECT_EQ(mockNewMessageQueue.read().first, operationStatus::SUCCESS);
  EXPECT_EQ(mockNewMessageQueue.read().second.getIdAdd().getArray(),
            mac(0x34, 0x65, 0xB4, 0x78, 0x35, 0x90).getArray());
  EXPECT_EQ(mockNewMessageQueue.read().second.getPayload()[0].getIdTgt(), 0x04);
  EXPECT_GE(mockNewMessageQueue.read().second.getPayload()[0].getData().size(), 1);
  EXPECT_EQ(mockNewMessageQueue.read().second.getPayload()[0].pullString().second, "This is a string");

  mockNewMessageQueue.purge();

  EXPECT_EQ(mockNewMessageQueue.read().first, operationStatus::FAIL);
}