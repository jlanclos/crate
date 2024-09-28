#pragma once

#include <boolean/boolean.h>
#include <integer/integer.h>
#include <ip/ip.h>
#include <linteger/linteger.h>
#include <mac/mac.h>
#include <real/real.h>
#include <sinteger/sinteger.h>
#include <stdint.h>
#include <string/string.h>
#include <uinteger/uinteger.h>
#include <ulinteger/ulinteger.h>
#include <usinteger/usinteger.h>

#include <vector>

class entry {
 public:
  entry(uint16_t id, type &object);

  uint16_t getId();
  entryType getType();

  byteString_t getBytes();

 private:
  uint16_t id;
  byteString_t bytes;
};