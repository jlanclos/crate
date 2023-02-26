#pragma once

#include <Arduino.h>

#define AHT20_ADDRESS 0x38
#define BMP280_ADDRESS 0x77

class BUS {
 public:
  // Constructor
  BUS();

  // Variables

  // Methods
  double temperature();
  double humidity();
  double pressure();
  void readSensors();

 private:
  // Variables
  std::vector<uint8_t> bmp280Cal;
  double temperatureRaw;
  double humidityRaw;
  double pressureRaw;

  // Methods
  void scanBus();
  void initAHT20(uint8_t address);
  void initBMP280(uint8_t address);
  void writeData(uint8_t address, uint8_t pointer, uint8_t sendDelay, std::vector<uint8_t> data);
  std::vector<uint8_t> readData(uint8_t address, uint8_t pointer, uint8_t responseDelay,
                                uint8_t bytes);
};
