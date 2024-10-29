#pragma once

#include <stdint.h>

#include <array>
#include <string>
#include <vector>

typedef std::vector<uint8_t> byteString_t;
typedef std::string string_t;
typedef std::array<uint8_t, 4> ipArray_t;
typedef std::array<uint8_t, 6> macArray_t;

enum class entryType : uint8_t {
  UNKNOWN = 0,
  TOGGLE = 1,
  USINTEGER = 2,
  SINTEGER = 3,
  UINTEGER = 4,
  INTEGER = 5,
  ULINTEGER = 6,
  LINTEGER = 7,
  REAL = 8,
  STRING = 9,
  MAC = 10,
  IP = 11,
  WIFI_CHANNEL = 12
};

class encodable {
 public:
  virtual byteString_t encode() = 0;
  virtual void decode(byteString_t bytes) = 0;

 private:
};

class type : public encodable {
 public:
 private:
};
