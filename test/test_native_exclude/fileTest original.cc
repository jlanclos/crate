#include <file.h>
#include <gtest/gtest.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(fileMethods, fileConstruction) {
  sequencer generator8(0, 255);
  // create a sequenced mac identifier
  uint8_t octet0 = generator8.next();
  uint8_t octet1 = generator8.next();
  uint8_t octet2 = generator8.next();
  uint8_t octet3 = generator8.next();
  uint8_t octet4 = generator8.next();
  uint8_t octet5 = generator8.next();
  mac mockMacSeq(octet0, octet1, octet2, octet3, octet4, octet5);
  // create a mock file
  file mockfile;
  mockfile.setIdentifier(mockMacSeq);
  ASSERT_EQ(mockfile.getIdentifier().getArray(), mockMacSeq.getArray());
  // set configuration with default values
  mockfile.setConfiguration();
  // check that default values were set correctly and can be read successfully
  mac defaultPlanetMac = DEFAULT_PLANET_MAC;
  ip defaultMqttHostIp = DEFAULT_MQTT_HOST_IP;
  ASSERT_EQ(mockfile.reportBlockAnalog8(blockType::CONFIG, configId::DEVICE_TYPE).success, true);
  ASSERT_EQ(mockfile.reportBlockAnalog8(blockType::CONFIG, configId::DEVICE_TYPE).value, DEFAULT_DEVICE_TYPE);
  ASSERT_EQ(mockfile.reportBlockAnalog8(blockType::CONFIG, configId::PROGRAM_MODE).success, true);
  ASSERT_EQ(mockfile.reportBlockAnalog8(blockType::CONFIG, configId::PROGRAM_MODE).value, DEFAULT_PROGRAM_MODE);
  ASSERT_EQ(mockfile.reportBlockAnalog8(blockType::CONFIG, configId::WIFI_CHANNEL).success, true);
  ASSERT_EQ(mockfile.reportBlockAnalog8(blockType::CONFIG, configId::WIFI_CHANNEL).value, DEFAULT_WIFI_CHANNEL);
  ASSERT_EQ(mockfile.reportBlockMac(blockType::CONFIG, configId::PLANET_MAC).success, true);
  ASSERT_EQ(mockfile.reportBlockMac(blockType::CONFIG, configId::PLANET_MAC).value.getArray(),
            defaultPlanetMac.getArray());
  ASSERT_EQ(mockfile.reportBlockString(blockType::CONFIG, configId::WIFI_SSID).success, true);
  ASSERT_EQ(mockfile.reportBlockString(blockType::CONFIG, configId::WIFI_SSID).value, DEFAULT_WIFI_SSID);
  ASSERT_EQ(mockfile.reportBlockString(blockType::CONFIG, configId::WIFI_PASSWORD).success, true);
  ASSERT_EQ(mockfile.reportBlockString(blockType::CONFIG, configId::WIFI_PASSWORD).value, DEFAULT_WIFI_PASSWORD);
  ASSERT_EQ(mockfile.reportBlockIp(blockType::CONFIG, configId::MQTT_HOST_IP).success, true);
  ASSERT_EQ(mockfile.reportBlockIp(blockType::CONFIG, configId::MQTT_HOST_IP).value.getArray(),
            defaultMqttHostIp.getArray());
  ASSERT_EQ(mockfile.reportBlockAnalog16(blockType::CONFIG, configId::MQTT_HOST_PORT).success, true);
  ASSERT_EQ(mockfile.reportBlockAnalog16(blockType::CONFIG, configId::MQTT_HOST_PORT).value, DEFAULT_MQTT_HOST_PORT);
  ASSERT_EQ(mockfile.reportBlockString(blockType::CONFIG, configId::MQTT_USERNAME).success, true);
  ASSERT_EQ(mockfile.reportBlockString(blockType::CONFIG, configId::MQTT_USERNAME).value, DEFAULT_MQTT_USERNAME);
  ASSERT_EQ(mockfile.reportBlockString(blockType::CONFIG, configId::MQTT_PASSWORD).success, true);
  ASSERT_EQ(mockfile.reportBlockString(blockType::CONFIG, configId::MQTT_PASSWORD).value, DEFAULT_MQTT_PASSWORD);
  ASSERT_EQ(mockfile.reportBlockString(blockType::CONFIG, configId::AP_SSID_HEADER).success, true);
  ASSERT_EQ(mockfile.reportBlockString(blockType::CONFIG, configId::AP_SSID_HEADER).value, DEFAULT_AP_SSID_HEADER);
  ASSERT_EQ(mockfile.reportBlockString(blockType::CONFIG, configId::AP_PASSWORD).success, true);
  ASSERT_EQ(mockfile.reportBlockString(blockType::CONFIG, configId::AP_PASSWORD).value, DEFAULT_AP_PASSWORD);
  ASSERT_EQ(mockfile.reportBlockAnalog16(blockType::CONFIG, configId::WEBSERVER_PORT).success, true);
  ASSERT_EQ(mockfile.reportBlockAnalog16(blockType::CONFIG, configId::WEBSERVER_PORT).value, DEFAULT_WEBSERVER_PORT);
  ASSERT_EQ(mockfile.reportBlockAnalog8(blockType::CONFIG, configId::SATELLITE_SEND_ATTEMPTS).success, true);
  ASSERT_EQ(mockfile.reportBlockAnalog8(blockType::CONFIG, configId::SATELLITE_SEND_ATTEMPTS).value,
            DEFAULT_SATELLITE_SEND_ATTEMPTS);
  ASSERT_EQ(mockfile.reportBlockAnalog8(blockType::CONFIG, configId::MESSAGE_QUEUE_MAX_SIZE).success, true);
  ASSERT_EQ(mockfile.reportBlockAnalog8(blockType::CONFIG, configId::MESSAGE_QUEUE_MAX_SIZE).value,
            DEFAULT_MESSAGE_QUEUE_MAX_SIZE);
  // get the configuration to ensure that values can be pulled
  deviceConfiguration mockConfiguration = mockfile.getConfiguration();
  ASSERT_EQ(mockConfiguration.deviceType, DEFAULT_DEVICE_TYPE);
  ASSERT_EQ(mockConfiguration.programMode, DEFAULT_PROGRAM_MODE);
  ASSERT_EQ(mockConfiguration.wifiChannel, DEFAULT_WIFI_CHANNEL);
  ASSERT_EQ(mockConfiguration.planetMac.getArray(), defaultPlanetMac.getArray());
  ASSERT_EQ(mockConfiguration.wifiSsid, DEFAULT_WIFI_SSID);
  ASSERT_EQ(mockConfiguration.wifiPassword, DEFAULT_WIFI_PASSWORD);
  ASSERT_EQ(mockConfiguration.mqttHostIp.getArray(), defaultMqttHostIp.getArray());
  ASSERT_EQ(mockConfiguration.mqttHostPort, DEFAULT_MQTT_HOST_PORT);
  ASSERT_EQ(mockConfiguration.mqttUsername, DEFAULT_MQTT_USERNAME);
  ASSERT_EQ(mockConfiguration.mqttPassword, DEFAULT_MQTT_PASSWORD);
  ASSERT_EQ(mockConfiguration.apSsidHeader, DEFAULT_AP_SSID_HEADER);
  ASSERT_EQ(mockConfiguration.webserverPort, DEFAULT_WEBSERVER_PORT);
  ASSERT_EQ(mockConfiguration.satelliteSendAttempts, DEFAULT_SATELLITE_SEND_ATTEMPTS);
  ASSERT_EQ(mockConfiguration.messageQueueMaxSize, DEFAULT_MESSAGE_QUEUE_MAX_SIZE);
}

TEST(fileMethods, fileUpdateReport) {
  sequencer generator8(0, 255);
  sequencer generator16(0, 65535, 500);
  sequencer generator32(0, 4294967255, 100000000);
  // create a sequenced mac identifier
  uint8_t octet0 = generator8.next();
  uint8_t octet1 = generator8.next();
  uint8_t octet2 = generator8.next();
  uint8_t octet3 = generator8.next();
  uint8_t octet4 = generator8.next();
  uint8_t octet5 = generator8.next();
  mac mockMacSeq(octet0, octet1, octet2, octet3, octet4, octet5);
  // create a mock file
  file mockfile;
  mockfile.setIdentifier(mockMacSeq);
  // set configuration with default values
  mockfile.setConfiguration();
  // update and read digital entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedUInt8 = generator8.next();
    // bool sequencedDigital = sequencedId > 127;
    bool sequencedDigital = true;
    ASSERT_EQ(mockfile.updateBlockDigital(blockType::DATA, sequencedId, sequencedDigital).success, true);
    ASSERT_EQ(mockfile.reportBlockDigital(blockType::DATA, sequencedId).success, true);
    ASSERT_EQ(mockfile.reportBlockDigital(blockType::DATA, sequencedId).value, sequencedDigital);
  }
  // GTEST_COUT << printf(" -----digital--------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)blockType::DATA].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)blockType::DATA][j];

  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getIdTgt(), entry.getIdentryType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)blockType::DATA].size());
  // update and read analog8 entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedAnalog8 = generator8.next();
    ASSERT_EQ(mockfile.updateBlockAnalog8(blockType::DATA, sequencedId, sequencedAnalog8).success, true);
    ASSERT_EQ(mockfile.reportBlockAnalog8(blockType::DATA, sequencedId).success, true);
    ASSERT_EQ(mockfile.reportBlockAnalog8(blockType::DATA, sequencedId).value, sequencedAnalog8);
  }
  // GTEST_COUT << printf(" -----analog8--------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)blockType::DATA].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)blockType::DATA][j];
  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getIdTgt(), entry.getIdentryType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)blockType::DATA].size());
  // update and read analog16 entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint16_t sequencedAnalog16 = generator16.next();
    ASSERT_EQ(mockfile.updateBlockAnalog16(blockType::DATA, sequencedId, sequencedAnalog16).success, true);
    ASSERT_EQ(mockfile.reportBlockAnalog16(blockType::DATA, sequencedId).success, true);
    ASSERT_EQ(mockfile.reportBlockAnalog16(blockType::DATA, sequencedId).value, sequencedAnalog16);
  }
  // GTEST_COUT << printf(" ----analog16--------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)blockType::DATA].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)blockType::DATA][j];
  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getIdTgt(), entry.getIdentryType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)blockType::DATA].size());
  // update and read analog32 entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint32_t sequencedAnalog32 = generator32.next();
    ASSERT_EQ(mockfile.updateBlockAnalog32(blockType::DATA, sequencedId, sequencedAnalog32).success, true);
    ASSERT_EQ(mockfile.reportBlockAnalog32(blockType::DATA, sequencedId).success, true);
    ASSERT_EQ(mockfile.reportBlockAnalog32(blockType::DATA, sequencedId).value, sequencedAnalog32);
  }
  // GTEST_COUT << printf(" ----analog32--------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)blockType::DATA].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)blockType::DATA][j];
  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getIdTgt(), entry.getIdentryType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)blockType::DATA].size());
  // update and read string entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedStringLength = generator8.next();
    std::string sequencedString;
    for (uint8_t i = 0; i < sequencedStringLength; i++) {
      char stringCharacter = generator8.next();
      sequencedString += stringCharacter;
    }
    ASSERT_EQ(mockfile.updateBlockString(blockType::DATA, sequencedId, sequencedString).success, true);
    ASSERT_EQ(mockfile.reportBlockString(blockType::DATA, sequencedId).success, true);
    ASSERT_EQ(mockfile.reportBlockString(blockType::DATA, sequencedId).value, sequencedString);
  }
  // GTEST_COUT << printf(" ----string--------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)blockType::DATA].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)blockType::DATA][j];
  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getIdTgt(), entry.getIdentryType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)blockType::DATA].size());
  // update and read mac entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    uint8_t octet5 = generator8.next();
    mac sequencedMac(octet0, octet1, octet2, octet3, octet4, octet5);
    ASSERT_EQ(mockfile.updateBlockMac(blockType::DATA, sequencedId, sequencedMac).success, true);
    ASSERT_EQ(mockfile.reportBlockMac(blockType::DATA, sequencedId).success, true);
    ASSERT_EQ(mockfile.reportBlockMac(blockType::DATA, sequencedId).value.getArray(), sequencedMac.getArray());
  }
  // GTEST_COUT << printf(" ----mac-------------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)blockType::DATA].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)blockType::DATA][j];
  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getIdTgt(), entry.getIdentryType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)blockType::DATA].size());
  // update and read ip entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    ip sequencedIp(octet0, octet1, octet2, octet3);
    ASSERT_EQ(mockfile.updateBlockIp(blockType::DATA, sequencedId, sequencedIp).success, true);
    ASSERT_EQ(mockfile.reportBlockIp(blockType::DATA, sequencedId).success, true);
    ASSERT_EQ(mockfile.reportBlockIp(blockType::DATA, sequencedId).value.getArray(), sequencedIp.getArray());
  }
  // GTEST_COUT << printf(" ----ip--------------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)blockType::DATA].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)blockType::DATA][j];
  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getIdTgt(), entry.getIdentryType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)blockType::DATA].size());
}

TEST(fileMethods, fileSaveLoad) {
  sequencer generator8(0, 255);
  sequencer generator16(0, 65535, 500);
  sequencer generator32(0, 4294967255, 100000000);
  // create a sequenced mac identifier
  uint8_t octet0 = generator8.next();
  uint8_t octet1 = generator8.next();
  uint8_t octet2 = generator8.next();
  uint8_t octet3 = generator8.next();
  uint8_t octet4 = generator8.next();
  uint8_t octet5 = generator8.next();
  mac mockMacSeq(octet0, octet1, octet2, octet3, octet4, octet5);
  // create a mock file
  file mockfile;
  mockfile.setIdentifier(mockMacSeq);
  // set configuration with default values
  mockfile.setConfiguration();
  // update and read digital entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedAnalog8 = generator8.next();
    bool sequencedDigital = sequencedAnalog8 > 127;
    ASSERT_EQ(mockfile.updateBlockDigital(blockType::DATA, sequencedId, sequencedDigital).success, true);
  }
  // update and read analog8 entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedAnalog8 = generator8.next();
    ASSERT_EQ(mockfile.updateBlockAnalog8(blockType::DATA, sequencedId, sequencedAnalog8).success, true);
  }
  // update and read analog16 entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint16_t sequencedAnalog16 = generator16.next();
    ASSERT_EQ(mockfile.updateBlockAnalog16(blockType::DATA, sequencedId, sequencedAnalog16).success, true);
  }
  // update and read analog32 entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint32_t sequencedAnalog32 = generator32.next();
    ASSERT_EQ(mockfile.updateBlockAnalog32(blockType::DATA, sequencedId, sequencedAnalog32).success, true);
  }
  // update and read string entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedStringLength = generator8.next();
    std::string sequencedString;
    for (uint8_t i = 0; i < sequencedStringLength; i++) {
      char stringCharacter = generator8.next();
      sequencedString += stringCharacter;
    }
    ASSERT_EQ(mockfile.updateBlockString(blockType::DATA, sequencedId, sequencedString).success, true);
  }
  // update and read mac entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    uint8_t octet5 = generator8.next();
    mac sequencedMac(octet0, octet1, octet2, octet3, octet4, octet5);
    ASSERT_EQ(mockfile.updateBlockMac(blockType::DATA, sequencedId, sequencedMac).success, true);
  }
  // update and read ip entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    ip sequencedIp(octet0, octet1, octet2, octet3);
    ASSERT_EQ(mockfile.updateBlockIp(blockType::DATA, sequencedId, sequencedIp).success, true);
  }
  // create a copy of the mockfile
  file mockfileNew;
  // save blocks
  saveSummary saveConfigFile = mockfile.save(blockType::CONFIG);
  saveSummary saveDataFile = mockfile.save(blockType::DATA);
  ASSERT_EQ(saveConfigFile.success, true);
  ASSERT_EQ(saveDataFile.success, true);
  loadSummary loadConfigFile = mockfileNew.load(blockType::CONFIG, saveConfigFile.package);
  loadSummary loadDataFile = mockfileNew.load(blockType::DATA, saveDataFile.package);
  ASSERT_EQ(loadConfigFile.success, true);
  ASSERT_EQ(loadDataFile.success, true);
  // compare files
  for (uint16_t i = 0; i < 256; i++) {
    // compare config block between the loaded and the old file
    reportSummary configReportNew = mockfileNew.reportBlock(blockType::CONFIG, i);
    reportSummary configReport = mockfile.reportBlock(blockType::CONFIG, i);
    ASSERT_EQ(configReport.success, configReportNew.success);

    if (configReport.success || configReportNew.success) {
      ASSERT_EQ(configReport.entry.getIdTgt(), configReportNew.entry.getIdTgt());
      ASSERT_EQ(configReport.entry.getIdentryType(), configReportNew.entry.getIdentryType());
      ASSERT_EQ(configReport.entry.getData(), configReportNew.entry.getData());
      // GTEST_COUT << printf("id: %d\n   configReport: %s\nconfigReportNew: %s\n", configReport.entry.getIdTgt(),
      //                      vectorUInt8ToString(configReport.entry.getData()).c_str(),
      //                      vectorUInt8ToString(configReportNew.entry.getData()).c_str())
      //            << std::endl;
    }

    reportSummary dataReportNew = mockfileNew.reportBlock(blockType::DATA, i);
    reportSummary dataReport = mockfile.reportBlock(blockType::DATA, i);
    ASSERT_EQ(dataReport.success, dataReportNew.success);

    if (dataReport.success || dataReportNew.success) {
      ASSERT_EQ(dataReport.entry.getIdTgt(), dataReportNew.entry.getIdTgt());
      ASSERT_EQ(dataReport.entry.getIdentryType(), dataReportNew.entry.getIdentryType());
      ASSERT_EQ(dataReport.entry.getData(), dataReportNew.entry.getData());
      // GTEST_COUT << printf("id: %d\n   dataReport: %s\ndataReportNew: %s\n", dataReport.entry.getIdTgt(),
      //                      vectorUInt8ToString(dataReport.entry.getData()).c_str(),
      //                      vectorUInt8ToString(dataReportNew.entry.getData()).c_str())
      //            << std::endl;
    }
  }
}

TEST(fileMethods, filePurge) {
  sequencer generator8(0, 255);
  sequencer generator16(0, 65535, 500);
  sequencer generator32(0, 4294967255, 100000000);
  // create a sequenced mac identifier
  uint8_t octet0 = generator8.next();
  uint8_t octet1 = generator8.next();
  uint8_t octet2 = generator8.next();
  uint8_t octet3 = generator8.next();
  uint8_t octet4 = generator8.next();
  uint8_t octet5 = generator8.next();
  mac mockMacSeq(octet0, octet1, octet2, octet3, octet4, octet5);
  // create a mock file
  file mockfile;
  mockfile.setIdentifier(mockMacSeq);
  // set configuration with default values
  mockfile.setConfiguration();
  // update and read digital entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedAnalog8 = generator8.next();
    bool sequencedDigital = sequencedAnalog8 > 127;
    ASSERT_EQ(mockfile.updateBlockDigital(blockType::DATA, sequencedId, sequencedDigital).success, true);
  }
  // update and read analog8 entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedAnalog8 = generator8.next();
    ASSERT_EQ(mockfile.updateBlockAnalog8(blockType::DATA, sequencedId, sequencedAnalog8).success, true);
  }
  // update and read analog16 entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint16_t sequencedAnalog16 = generator16.next();
    ASSERT_EQ(mockfile.updateBlockAnalog16(blockType::DATA, sequencedId, sequencedAnalog16).success, true);
  }
  // update and read analog32 entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint32_t sequencedAnalog32 = generator32.next();
    ASSERT_EQ(mockfile.updateBlockAnalog32(blockType::DATA, sequencedId, sequencedAnalog32).success, true);
  }
  // update and read string entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedStringLength = generator8.next();
    std::string sequencedString;
    for (uint16_t i = 0; i < sequencedStringLength; i++) {
      char stringCharacter = generator8.next();
      sequencedString += stringCharacter;
    }
    ASSERT_EQ(mockfile.updateBlockString(blockType::DATA, sequencedId, sequencedString).success, true);
  }
  // update and read mac entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    uint8_t octet4 = generator8.next();
    uint8_t octet5 = generator8.next();
    mac sequencedMac(octet0, octet1, octet2, octet3, octet4, octet5);
    ASSERT_EQ(mockfile.updateBlockMac(blockType::DATA, sequencedId, sequencedMac).success, true);
  }
  // update and read ip entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    ip sequencedIp(octet0, octet1, octet2, octet3);
    ASSERT_EQ(mockfile.updateBlockIp(blockType::DATA, sequencedId, sequencedIp).success, true);
  }
  // create a copy of the mockfile
  file mockfileNew;
  mockfile.purge();
  //  compare files

  for (uint16_t i = 0; i < 256; i++) {
    // compare config block between the loaded and the old file
    reportSummary configReportNew = mockfileNew.reportBlock(blockType::CONFIG, i);
    reportSummary configReport = mockfile.reportBlock(blockType::CONFIG, i);
    ASSERT_EQ(configReport.success, configReportNew.success);

    if (configReport.success || configReportNew.success) {
      ASSERT_EQ(configReport.entry.getIdTgt(), configReportNew.entry.getIdTgt());
      ASSERT_EQ(configReport.entry.getIdentryType(), configReportNew.entry.getIdentryType());
      ASSERT_EQ(configReport.entry.getData(), configReportNew.entry.getData());
      // GTEST_COUT << printf("id: %d\n   configReport: %s\nconfigReportNew: %s\n", configReport.entry.getIdTgt(),
      //                      vectorUInt8ToString(configReport.entry.getData()).c_str(),
      //                      vectorUInt8ToString(configReportNew.entry.getData()).c_str())
      //            << std::endl;
    }

    reportSummary dataReportNew = mockfileNew.reportBlock(blockType::DATA, i);
    reportSummary dataReport = mockfile.reportBlock(blockType::DATA, i);
    ASSERT_EQ(dataReport.success, dataReportNew.success);

    if (dataReport.success || dataReportNew.success) {
      ASSERT_EQ(dataReport.entry.getIdTgt(), dataReportNew.entry.getIdTgt());
      ASSERT_EQ(dataReport.entry.getIdentryType(), dataReportNew.entry.getIdentryType());
      ASSERT_EQ(dataReport.entry.getData(), dataReportNew.entry.getData());
      // GTEST_COUT << printf("id: %d\n   dataReport: %s\ndataReportNew: %s\n", dataReport.entry.getIdTgt(),
      //                      vectorUInt8ToString(dataReport.entry.getData()).c_str(),
      //                      vectorUInt8ToString(dataReportNew.entry.getData()).c_str())
      //            << std::endl;
    }
  }
}