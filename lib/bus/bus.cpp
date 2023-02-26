#include "bus.h"

#include <Wire.h>

BUS ::BUS() {
  Serial.printf(
      "Initiating I2C communications with:\n    SDA = Pin %i\n    SCL = Pin "
      "%i\n",
      SDA, SCL);
  Wire.begin();
  scanBus();
  initAHT20(AHT20_ADDRESS);
  initBMP280(BMP280_ADDRESS);
}

void BUS::scanBus() {
  Serial.printf("Scanning I2C bus...\n");
  uint8_t deviceCount = 0;
  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    uint8_t returnStatus = Wire.endTransmission();
    switch (returnStatus) {
      case 0:
        Serial.printf("    Device found at 0x%X.\n", address);
        deviceCount++;
        break;
      case 4:
        Serial.printf("    Unknown error at 0x%X.\n", address);
        break;
      default:
        break;
    }
  }
  if (deviceCount == 0) {
    Serial.printf("    No devices found on the I2C bus.\n");
  }
}

void BUS::initAHT20(uint8_t address) {
  std::vector<uint8_t> state = readData(address, 0x71, 20, 1);
  if (!(state[0] & (1 << 3))) {
    this->writeData(address, 0xBE, 12, {0x08, 0x00});
  }
}

void BUS::initBMP280(uint8_t address) { this->bmp280Cal = readData(BMP280_ADDRESS, 0xF7, 8, 6); }

void BUS::readSensors() {
  // AHT20 Measurments
  this->writeData(AHT20_ADDRESS, 0xAC, 80, {0x33, 0x00});
  std::vector<uint8_t> aht20Raw = readData(AHT20_ADDRESS, 0x71, 8, 6);
  this->humidityRaw =
      (((aht20Raw[1] << 16 | aht20Raw[2] << 8 | aht20Raw[3]) >> 4) / pow(2, 20)) * 100.0;
  this->temperatureRaw =
      (((aht20Raw[3] << 16 | aht20Raw[4] << 8 | aht20Raw[5]) & ~(0xFFF00000)) / pow(2, 20)) * 200 -
      50;

  // BMP280 Measurments
  // std::vector<uint8_t> bmp280Raw = readData(BMP280_ADDRESS, 0xF7, 8, 6);
  // int32_t adcTemperature =
  //     (bmp280Raw[3] << 16 | bmp280Raw[4] << 8 | bmp280Raw[5]) >> 4;
  // int32_t adcPressure =
  //     (bmp280Raw[0] << 16 | bmp280Raw[1] << 8 | bmp280Raw[2]) >> 4;
  // int32_t t_fine;
  // double var1, var2, t, p;
  // var1 = ((adcTemperature) / 16384.0 - cal[])

  //     var1 = ((double)t_fine / 2.0) - 64000.0;
  // var2 = var1 * var1 * (double)params.dig_P6;
  // var2 = var2 + ((var1 * (int64_t)params.dig_P5) << 17);
  // var2 = var2 + (((int64_t)params.dig_P4) << 35);
  // var1 = ((var1 * var1 * (int64_t)params.dig_P3) >> 8) +
  //        ((var1 * (int64_t)params.dig_P2) << 12);
  // var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)params.dig_P1) >> 33;
  // if (var1 == 0) {
  //   p = 0;
  // }
  // p = 1048576 - adcPressure;
  // p = (((p << 31) - var2) * 3125) / var1;
  // var1 = (((int64_t)params.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
  // var2 = (((int64_t)params.dig_P8) * p) >> 19;
  // p = ((p + var1 + var2) >> 8) + (((int64_t)params.dig_P7) << 4);
  // this->pressureRaw = (uint32_t)p;
}

void BUS::writeData(uint8_t address, uint8_t pointer, uint8_t sendDelay,
                    std::vector<uint8_t> data) {
  Wire.beginTransmission(address);
  Wire.write(pointer);
  for (int i = 0; i < (int)data.size(); i++) {
    Wire.write(data[i]);
  }
  Wire.endTransmission();
  delay(sendDelay);
}

std::vector<uint8_t> BUS::readData(uint8_t address, uint8_t pointer, uint8_t responseDelay,
                                   uint8_t bytes) {
  Wire.beginTransmission(address);
  Wire.write(pointer);
  Wire.endTransmission();
  delay(responseDelay);
  Wire.requestFrom(address, (uint8_t)bytes);
  std::vector<uint8_t> readBytes;
  for (int i = 0; i < bytes; i++) {
    readBytes.push_back(Wire.read());
  }
  return readBytes;
}

double BUS::temperature() { return this->temperatureRaw; }
double BUS::humidity() { return this->humidityRaw; }
double BUS::pressure() { return this->pressureRaw; }