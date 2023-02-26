#include "mem.h"

#include <gtest/gtest.h>

TEST(capsuleMethods, capsuleConstruction) {
  capsule mockCapsule;
  mockCapsule.setIdentifier(mac(0x02, 0x5C, 0x67, 0xDC, 0x87, 0x43));
  EXPECT_EQ(mockCapsule.getIdentifier().getArray(),
            mac(0x02, 0x5C, 0x67, 0xDC, 0x87, 0x43).getArray());
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::TYPE).first,
            operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::TYPE)
                .second.pullAnalogUInt8()
                .second,
            configType::PLANET);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::PROGRAM).first,
            operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::PROGRAM)
                .second.pullDigital()
                .second,
            configProgram::TRUE);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::CHANNEL).first,
            operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::CHANNEL)
                .second.pullAnalogUInt8()
                .second,
            configChannel::CHANNEL_3);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::PLANET_MAC_ADDRESS).first,
            operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::PLANET_MAC_ADDRESS)
                .second.pullMac()
                .second.getArray(),
            mac(0x32, 0x42, 0xB4, 0x87, 0x99, 0x23).getArray());
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::WIFI_SSID).first,
            operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::WIFI_SSID)
                .second.pullString()
                .second,
            "safe wifi ssid");
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::WIFI_PASSWORD).first,
            operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::WIFI_PASSWORD)
                .second.pullString()
                .second,
            "safe wifi password");
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::MQTT_HOST).first,
            operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::MQTT_HOST)
                .second.pullIp()
                .second.getArray(),
            ip(192, 168, 2, 153).getArray());
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::MQTT_PORT).first,
            operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::MQTT_PORT)
                .second.pullAnalogUInt16()
                .second,
            1883);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::MQTT_USERNAME).first,
            operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::MQTT_USERNAME)
                .second.pullString()
                .second,
            "safe mqtt username");
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::MQTT_PASSWORD).first,
            operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::CONFIGBLOCK, configId::MQTT_PASSWORD)
                .second.pullString()
                .second,
            "safe mqtt password");
}

TEST(capsuleMethods, capsuleSaveLoad) {
  capsule mockCapsule;
  mockCapsule.setIdentifier(mac(0x02, 0x5C, 0x67, 0xDC, 0x87, 0x43));
  mockCapsule.updateBlock(blockType::DATABLOCK, createAnalogUInt16Entry(0x40, 3452));
  mockCapsule.updateBlock(blockType::DATABLOCK, createStringEntry(0x2A, "some sample text"));
  EXPECT_EQ(mockCapsule.reportBlock(blockType::DATABLOCK, 0x40).first, operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::DATABLOCK, 0x40).second.pullAnalogUInt16().second,
            3452);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::DATABLOCK, 0x2A).first, operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::DATABLOCK, 0x2A).second.pullString().second,
            "some sample text");
  mockCapsule.save();
  mockCapsule.purge();
  EXPECT_EQ(mockCapsule.reportBlock(blockType::DATABLOCK, 0x40).first, operationStatus::FAIL);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::DATABLOCK, 0x2A).first, operationStatus::FAIL);
  mockCapsule.load();
  EXPECT_EQ(mockCapsule.reportBlock(blockType::DATABLOCK, 0x40).first, operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::DATABLOCK, 0x40).second.pullAnalogUInt16().second,
            3452);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::DATABLOCK, 0x2A).first, operationStatus::SUCCESS);
  EXPECT_EQ(mockCapsule.reportBlock(blockType::DATABLOCK, 0x2A).second.pullString().second,
            "some sample text");
}