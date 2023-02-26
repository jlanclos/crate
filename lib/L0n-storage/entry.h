#pragma once

#include <ip.h>
#include <mac.h>
#include <stdint.h>

#include <string>
#include <vector>

enum class entryType : uint8_t {
  UNKNOWN = 0,
  DIGITAL = 1,
  UINT8 = 2,
  UINT16 = 3,
  UINT32 = 4,
  STRING = 5,
  MAC = 6,
  IP = 7
};

class entry {
 public:
  entry();
  entry(uint8_t id);
  entry(uint8_t id, entryType type);

  void setId(uint8_t newId);
  uint8_t getId();
  void setType(entryType newType);
  entryType getType();

  void setData(std::vector<uint8_t> newData);
  uint8_t getDataSize();
  std::vector<uint8_t> getData();

  bool isType(entryType typeExpected);

  void setDigital(bool newValue);
  bool getDigital();
  void setAnalog8(uint8_t newValue);
  uint8_t getAnalog8();
  void setAnalog16(uint16_t newValue);
  uint16_t getAnalog16();
  void setAnalog32(uint32_t newValue);
  uint32_t getAnalog32();
  void setString(std::string newValue);
  std::string getString();
  void setMac(mac newValue);
  mac getMac();
  void setIp(ip newValue);
  ip getIp();

 private:
  uint8_t id;
  entryType type;
  std::vector<uint8_t> data;
};

entry createDigitalEntry(uint8_t id, bool value);
entry createAnalog8Entry(uint8_t id, uint8_t value);
entry createAnalog16Entry(uint8_t id, uint16_t value);
entry createAnalog32Entry(uint8_t id, uint32_t value);
entry createStringEntry(uint8_t id, std::string value);
entry createMacEntry(uint8_t id, mac value);
entry createIpEntry(uint8_t id, ip value);