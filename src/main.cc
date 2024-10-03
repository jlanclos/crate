// #include <Arduino.h>
#include <config/config.h>
// #include <network.h>
#include <storage.h>

storageService& storage = storageService::createStorageService();
// networkService& network = networkService::createNetworkService();

void setup() {
  configuration config = storage.getConfiguration();
  // network.connect(config);
}

void loop() {}