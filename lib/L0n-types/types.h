#pragma once

#include <stdint.h>

enum class entryType : uint8_t {
  UNKNOWN = 0,
  BOOLEAN = 1,
  USINTEGER = 2,
  SINTEGER = 3,
  UINTEGER = 4,
  INTEGER = 5,
  ULINTEGER = 6,
  LINTEGER = 7,
  REAL = 8,
  STRING = 9,
  MAC = 10,
  IP = 11
};