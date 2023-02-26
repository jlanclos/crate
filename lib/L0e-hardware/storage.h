#pragma once

#define CONFIGURATION_PATH "config"

#include <LittleFS.h>
#include <config.h>

#include <string>
#include <vector>

class storageService {
 public:
  static storageService& createStorageService();

  void saveFile(std::vector<uint8_t> data, std::string path);
  std::vector<uint8_t> loadFile(std::string path);
  configuration getConfiguration();

 private:
  storageService();
  ~storageService();

  void createConfiguration();
};
