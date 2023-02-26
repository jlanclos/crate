#pragma once

#include <array>
#include <string>
#include <vector>

enum class idType : uint8_t {
  UNDEFINED = 0x00,
  DEVICE_RESTART = 0x01,
  DEVICE_PURGE = 0x02,
  DATABLOCK_REPORT = 0x0A,
  CONFIGBLOCK_REPORT = 0x0B,
  DATABLOCK_UPDATE = 0x14,
  CONFIGBLOCK_UPDATE = 0x15
};

enum configId : uint8_t {
  TYPE = 0x00,
  PROGRAM = 0x01,
  CHANNEL = 0x02,
  PLANET_MAC_ADDRESS = 0x03,
  WIFI_SSID = 0x04,
  WIFI_PASSWORD = 0x05,
  MQTT_HOST = 0x06,
  MQTT_PORT = 0x07,
  MQTT_USERNAME = 0x08,
  MQTT_PASSWORD = 0x09
};

enum configType : uint8_t { PLANET = 0x00, SATELLITE = 0x01 };

enum configProgram : bool { TRUE = true, FALSE = false };

enum configChannel : uint8_t {
  CHANNEL_1 = 0x00,
  CHANNEL_2 = 0x01,
  CHANNEL_3 = 0x02,
  CHANNEL_4 = 0x03,
  CHANNEL_5 = 0x04,
  CHANNEL_6 = 0x05,
  CHANNEL_7 = 0x06,
  CHANNEL_8 = 0x07,
  CHANNEL_9 = 0x08,
  CHANNEL_10 = 0x09,
  CHANNEL_11 = 0x0A,
  CHANNEL_12 = 0x0B,
  CHANNEL_13 = 0x0C,
  CHANNEL_14 = 0x0D,
};

enum class operationStatus : uint8_t { FAIL = 0x00, SUCCESS = 0x01 };

class mac {
 public:
  mac();
  mac(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4, uint8_t octet5,
      uint8_t octet6);

  std::array<uint8_t, 6> getArray();

 private:
  std::array<uint8_t, 6> value;
};

class ip {
 public:
  ip();
  ip(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4);

  std::array<uint8_t, 4> getArray();

 private:
  std::array<uint8_t, 4> value;
};

class dataEntry {
 public:
  dataEntry();
  dataEntry(uint8_t idTgt);

  void setIdTgt(uint8_t newIdTgt);
  uint8_t getIdTgt();

  void setData(std::vector<uint8_t> newData);
  uint8_t getDataSize();
  std::vector<uint8_t> getData();

  void pushDigital(bool newValue);
  std::pair<operationStatus, bool> pullDigital();
  void pushAnalogUInt8(uint8_t newValue);
  std::pair<operationStatus, uint8_t> pullAnalogUInt8();
  void pushAnalogUInt16(uint16_t newValue);
  std::pair<operationStatus, uint16_t> pullAnalogUInt16();
  void pushAnalogUInt32(uint32_t newValue);
  std::pair<operationStatus, uint32_t> pullAnalogUInt32();
  void pushString(std::string newValue);
  std::pair<operationStatus, std::string> pullString();
  void pushMac(mac newValue);
  std::pair<operationStatus, mac> pullMac();
  void pushIp(ip newValue);
  std::pair<operationStatus, ip> pullIp();

 private:
  uint8_t idTgt;
  std::vector<uint8_t> data;
};

dataEntry createDigitalEntry(uint8_t idTgt, bool value);
dataEntry createAnalogUInt8Entry(uint8_t idTgt, uint8_t value);
dataEntry createAnalogUInt16Entry(uint8_t idTgt, uint16_t value);
dataEntry createAnalogUInt32Entry(uint8_t idTgt, uint32_t value);
dataEntry createStringEntry(uint8_t idTgt, std::string value);
dataEntry createMacEntry(uint8_t idTgt, mac value);
dataEntry createIpEntry(uint8_t idTgt, ip value);
