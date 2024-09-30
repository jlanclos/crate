#pragma once

#include <types.h>

enum class channel : uint8_t {
  CH_1 = 1,
  CH_2 = 2,
  CH_3 = 3,
  CH_4 = 4,
  CH_5 = 5,
  CH_6 = 6,
  CH_7 = 7,
  CH_8 = 8,
  CH_9 = 9,
  CH_10 = 10,
  CH_11 = 11
};

class wifiChannel : public type {
 public:
  wifiChannel(channel value);
  wifiChannel(byteString_t bytes);

  channel getValue();

  byteString_t encode() override;
  void decode(byteString_t bytes) override;

 private:
  channel value = channel::CH_1;
};

static bool isValidWifiChannel(byteString_t bytes);