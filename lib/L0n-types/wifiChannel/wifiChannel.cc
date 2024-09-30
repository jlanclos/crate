#include <wifiChannel/wifiChannel.h>

// unsigned integer class
wifiChannel::wifiChannel(channel value) { this->value = value; }
wifiChannel::wifiChannel(byteString_t bytes) { decode(bytes); }

channel wifiChannel::getValue() { return this->value; }

byteString_t wifiChannel::encode() {
  byteString_t bytes;
  bytes.push_back((uint8_t)entryType::WIFI_CHANNEL);
  bytes.push_back((uint8_t)this->value);
  return bytes;
}

void wifiChannel::decode(byteString_t bytes) {
  if (isValidWifiChannel(bytes)) {
    this->value = (channel)bytes[1];
  };
}

// methods
bool isValidWifiChannel(byteString_t bytes) {
  uint32_t dataSize = bytes.size();
  if (dataSize != 2) {
    return false;
  }
  if ((entryType)bytes[0] != entryType::WIFI_CHANNEL) {
    return false;
  }
  channel value = (channel)bytes[1];
  switch (value) {
    case channel::CH_1:
      return true;
    case channel::CH_2:
      return true;
    case channel::CH_3:
      return true;
    case channel::CH_4:
      return true;
    case channel::CH_5:
      return true;
    case channel::CH_6:
      return true;
    case channel::CH_7:
      return true;
    case channel::CH_8:
      return true;
    case channel::CH_9:
      return true;
    case channel::CH_10:
      return true;
    case channel::CH_11:
      return true;
    default:
      return false;
  }
}