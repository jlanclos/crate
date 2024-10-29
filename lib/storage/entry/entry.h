#pragma once

#include <toggle/toggle.h>
#include <integer/integer.h>
#include <ip/ip.h>
#include <linteger/linteger.h>
#include <mac/mac.h>
#include <real/real.h>
#include <sinteger/sinteger.h>
#include <string/string.h>
#include <types.h>
#include <uinteger/uinteger.h>
#include <ulinteger/ulinteger.h>
#include <usinteger/usinteger.h>
#include <wifiChannel/wifiChannel.h>

class entry {
 public:
  entry();
  entry(uint16_t id, type &object);

  uint16_t getId();
  entryType getType();
  byteString_t getData();

 private:
  uint16_t id;
  byteString_t bytes;
};