#include <file.h>
#include <gtest/gtest.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(fileMethods, fileUpdateReport) {
  sequencer generator8(0, 255);
  sequencer generator16(0, 65535, 500);
  sequencer generator32(0, 4294967255, 100000000);
  // create a mock file
  file mockfile;
  // update and read digital entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedUInt8 = generator8.next();
    // bool sequencedDigital = sequencedId > 127;
    bool sequencedDigital = true;
    mockfile.updateEntryDigital(sequencedId, sequencedDigital);
    ASSERT_EQ(mockfile.reportEntryDigital(sequencedId).exists, true);
    ASSERT_EQ(mockfile.reportEntryDigital(sequencedId).value, sequencedDigital);
  }
  // GTEST_COUT << printf(" -----digital--------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)][j];

  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getId(), entry.getType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)].size());
  // update and read analog8 entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedAnalog8 = generator8.next();
    mockfile.updateEntryAnalog8(sequencedId, sequencedAnalog8);
    ASSERT_EQ(mockfile.reportEntryAnalog8(sequencedId).exists, true);
    ASSERT_EQ(mockfile.reportEntryAnalog8(sequencedId).value, sequencedAnalog8);
  }
  // GTEST_COUT << printf(" -----analog8--------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)][j];
  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getId(), entry.getType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)].size());
  // update and read analog16 entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint16_t sequencedAnalog16 = generator16.next();
    mockfile.updateEntryAnalog16(sequencedId, sequencedAnalog16);
    ASSERT_EQ(mockfile.reportEntryAnalog16(sequencedId).exists, true);
    ASSERT_EQ(mockfile.reportEntryAnalog16(sequencedId).value, sequencedAnalog16);
  }
  // GTEST_COUT << printf(" ----analog16--------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)][j];
  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getId(), entry.getType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)].size());
  // update and read analog32 entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint32_t sequencedAnalog32 = generator32.next();
    mockfile.updateEntryAnalog32(sequencedId, sequencedAnalog32);
    ASSERT_EQ(mockfile.reportEntryAnalog32(sequencedId).exists, true);
    ASSERT_EQ(mockfile.reportEntryAnalog32(sequencedId).value, sequencedAnalog32);
  }
  // GTEST_COUT << printf(" ----analog32--------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)][j];
  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getId(), entry.getType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)].size());
  // update and read string entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedStringLength = generator8.next();
    std::string sequencedString;
    for (uint8_t i = 0; i < sequencedStringLength; i++) {
      char stringCharacter = generator8.next();
      sequencedString += stringCharacter;
    }
    mockfile.updateEntryString(sequencedId, sequencedString).exists;
    ASSERT_EQ(mockfile.reportEntryString(sequencedId).exists, true);
    ASSERT_EQ(mockfile.reportEntryString(sequencedId).value, sequencedString);
  }
  // GTEST_COUT << printf(" ----string--------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)][j];
  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getId(), entry.getType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)].size());
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
    mockfile.updateEntryMac(sequencedId, sequencedMac).exists;
    ASSERT_EQ(mockfile.reportEntryMac(sequencedId).exists, true);
    ASSERT_EQ(mockfile.reportEntryMac(sequencedId).value.getArray(), sequencedMac.getArray());
  }
  // GTEST_COUT << printf(" ----mac-------------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)][j];
  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getId(), entry.getType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)].size());
  // update and read ip entries
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    ip sequencedIp(octet0, octet1, octet2, octet3);
    mockfile.updateEntryIp(sequencedId, sequencedIp);
    ASSERT_EQ(mockfile.reportEntryIp(sequencedId).exists, true);
    ASSERT_EQ(mockfile.reportEntryIp(sequencedId).value.getArray(), sequencedIp.getArray());
  }
  // GTEST_COUT << printf(" ----ip--------------------------------------------------\n");
  // for (uint16_t j = 0; j < mockfile.blocks[(uint8_t)].size(); j++) {
  //   dataEntry entry = mockfile.blocks[(uint8_t)][j];
  //   GTEST_COUT << printf(" ENTRY[%d]>> id: %d --type: %d --size: %d\n", j, entry.getId(), entry.getType(),
  //                        entry.getDataSize());
  // }
  // GTEST_COUT << printf("       TOTAL ENTRIES: %d\n", mockfile.blocks[(uint8_t)].size());
}

TEST(fileMethods, fileSaveLoad) {
  sequencer generator8(0, 255);
  sequencer generator16(0, 65535, 500);
  sequencer generator32(0, 4294967255, 100000000);
  // create a mock file
  file mockfile;
  // update and read digital entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedAnalog8 = generator8.next();
    bool sequencedDigital = sequencedAnalog8 > 127;
    mockfile.updateEntryDigital(sequencedId, sequencedDigital);
  }
  // update and read analog8 entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedAnalog8 = generator8.next();
    mockfile.updateEntryAnalog8(sequencedId, sequencedAnalog8);
  }
  // update and read analog16 entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint16_t sequencedAnalog16 = generator16.next();
    mockfile.updateEntryAnalog16(sequencedId, sequencedAnalog16);
  }
  // update and read analog32 entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint32_t sequencedAnalog32 = generator32.next();
    mockfile.updateEntryAnalog32(sequencedId, sequencedAnalog32);
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
    mockfile.updateEntryString(sequencedId, sequencedString);
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
    mockfile.updateEntryMac(sequencedId, sequencedMac);
  }
  // update and read ip entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    ip sequencedIp(octet0, octet1, octet2, octet3);
    mockfile.updateEntryIp(sequencedId, sequencedIp).exists;
  }
  // create a copy of the mockfile
  file mockfileNew;
  // save blocks
  saveSummary saveFile = mockfile.save();
  ASSERT_EQ(saveFile.success, true);
  loadSummary loadFile = mockfileNew.load(saveFile.package);
  ASSERT_EQ(loadFile.success, true);
  // compare files
  for (uint16_t i = 0; i < 256; i++) {
    reportSummary entryReportNew = mockfileNew.reportEntry(i);
    reportSummary entryReport = mockfile.reportEntry(i);
    ASSERT_EQ(entryReport.exists, entryReportNew.exists);

    if (entryReport.exists or entryReportNew.exists) {
      ASSERT_EQ(entryReport.resultEntry.getId(), entryReportNew.resultEntry.getId());
      ASSERT_EQ(entryReport.resultEntry.getType(), entryReportNew.resultEntry.getType());
      ASSERT_EQ(entryReport.resultEntry.getData(), entryReportNew.resultEntry.getData());
      // GTEST_COUT << printf("id: %d\n   dataReport: %s\ndataReportNew: %s\n", dataReport.resultEntry.getId(),
      //                      vectorUInt8ToString(dataReport.resultEntry.getData()).c_str(),
      //                      vectorUInt8ToString(dataReportNew.resultEntry.getData()).c_str())
      //            << std::endl;
    }
  }
}

TEST(fileMethods, filePurge) {
  sequencer generator8(0, 255);
  sequencer generator16(0, 65535, 500);
  sequencer generator32(0, 4294967255, 100000000);
  // create a mock file
  file mockfile;
  // update and read digital entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedAnalog8 = generator8.next();
    bool sequencedDigital = sequencedAnalog8 > 127;
    mockfile.updateEntryDigital(sequencedId, sequencedDigital);
  }
  // update and read analog8 entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t sequencedAnalog8 = generator8.next();
    mockfile.updateEntryAnalog8(sequencedId, sequencedAnalog8);
  }
  // update and read analog16 entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint16_t sequencedAnalog16 = generator16.next();
    mockfile.updateEntryAnalog16(sequencedId, sequencedAnalog16);
  }
  // update and read analog32 entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint32_t sequencedAnalog32 = generator32.next();
    mockfile.updateEntryAnalog32(sequencedId, sequencedAnalog32);
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
    mockfile.updateEntryString(sequencedId, sequencedString);
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
    mockfile.updateEntryMac(sequencedId, sequencedMac).exists;
  }
  // update and read ip entries
  for (uint16_t i = 0; i < 50; i++) {
    uint8_t sequencedId = generator8.next();
    uint8_t octet0 = generator8.next();
    uint8_t octet1 = generator8.next();
    uint8_t octet2 = generator8.next();
    uint8_t octet3 = generator8.next();
    ip sequencedIp(octet0, octet1, octet2, octet3);
    mockfile.updateEntryIp(sequencedId, sequencedIp);
  }
  // create a copy of the mockfile
  file mockfileNew;
  mockfile.clear();
  //  compare files

  for (uint16_t i = 0; i < 256; i++) {
    reportSummary entryReportNew = mockfileNew.reportEntry(i);
    reportSummary entryReport = mockfile.reportEntry(i);
    ASSERT_EQ(entryReport.exists, entryReportNew.exists);

    if (entryReport.exists or entryReportNew.exists) {
      ASSERT_EQ(entryReport.resultEntry.getId(), entryReportNew.resultEntry.getId());
      ASSERT_EQ(entryReport.resultEntry.getType(), entryReportNew.resultEntry.getType());
      ASSERT_EQ(entryReport.resultEntry.getData(), entryReportNew.resultEntry.getData());
      // GTEST_COUT << printf("id: %d\n   dataReport: %s\ndataReportNew: %s\n", dataReport.resultEntry.getId(),
      //                      vectorUInt8ToString(dataReport.resultEntry.getData()).c_str(),
      //                      vectorUInt8ToString(dataReportNew.resultEntry.getData()).c_str())
      //            << std::endl;
    }
  }
}