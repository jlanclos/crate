#include <file.h>
#include <gtest/gtest.h>
#include <storage.h>

TEST(fileMethods, fileSaveLoad) {
  storageService& storage = storageService::createStorageService();
  file mockFile;
  mockFile.updateEntry(createAnalog16Entry(0x40, 3452));
  mockFile.updateEntry(createStringEntry(0x2A, "some sample text"));
  EXPECT_EQ(mockFile.reportEntry(0x40).resultEntry.getAnalog16(), 3452);
  EXPECT_EQ(mockFile.reportEntry(0x2A).resultEntry.getString(), "some sample text");
  storage.saveFile(mockFile.save().package, "data");
  mockFile.clear();
  EXPECT_EQ(mockFile.reportEntry(0x40).exists, false);
  EXPECT_EQ(mockFile.reportEntry(0x2A).exists, false);
  mockFile.load(storage.loadFile("data"));
  EXPECT_EQ(mockFile.reportEntry(0x40).resultEntry.getAnalog16(), 3452);
  EXPECT_EQ(mockFile.reportEntry(0x2A).resultEntry.getString(), "some sample text");
}