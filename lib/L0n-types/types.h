#pragma once

#include <stdint.h>

enum class entryType : uint8_t {
  UNKNOWN = 0,
  BOOLEAN = 1,
  UNSIGNED_INTEGER = 2,
  INTEGER = 3,
  REAL = 4,
  STRING = 5,
  MAC = 6,
  IP = 7
};