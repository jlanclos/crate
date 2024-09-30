#include <storage.h>

storageService& storageService::createStorageService() {
  static storageService storageServiceInstance;
  return storageServiceInstance;
}

storageService::storageService() { this->createConfiguration(); }

storageService::~storageService() {}

void storageService::saveFile(byteString_t data, string_t path) {
  if (!LittleFS.begin()) {
  } else {
    File saveFile = LittleFS.open(path.c_str(), "w+");
    if (!saveFile) {
    } else {
      uint8_t dataSize = data.size();
      for (uint8_t i = 0; i < dataSize; i++) {
        saveFile.write((byte*)&data[i], 1);
      }
      saveFile.close();
    }
    LittleFS.end();
  }
}

byteString_t storageService::loadFile(string_t path) {
  byteString_t bytes;
  if (!LittleFS.begin()) {
  } else {
    File loadFile = LittleFS.open(path.c_str(), "r");
    if (!loadFile) {
    } else {
      uint8_t loadFileSize = loadFile.size();
      if (loadFileSize > 0) {
        for (uint8_t i = 0; i < loadFileSize; i++) {
          uint8_t fileByte;
          loadFile.read((byte*)&fileByte, 1);
          bytes.push_back(fileByte);
        }
      }
      loadFile.close();
    }
    LittleFS.end();
  }
  return bytes;
}

configuration storageService::getConfiguration() {
  configuration config(this->loadFile(CONFIGURATION_PATH));
  return config;
}

void storageService::createConfiguration() {
  configuration config;
  config.setDefaults();
  this->saveFile(config.encode(), CONFIGURATION_PATH);
}
