#pragma once

#define CONFIGURATION_PATH "config"

#include <LittleFS.h>
#include <config/config.h>

class storageService {
 public:
  static storageService& createStorageService();

  void saveFile(byteString_t data, string_t path);
  byteString_t loadFile(string_t path);
  configuration getConfiguration();

 private:
  storageService();
  ~storageService();

  void createConfiguration();
};
