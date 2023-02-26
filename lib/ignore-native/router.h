#pragma once

#include <capsule.h>
#include <deviceInterface.h>
#include <message.h>
#include <wirelessInterface.h>

class router {
 public:
  router();

  void route(message currentMessage);

 private:
  capsule localDevice;
  wirelessService* wireless = wirelessService::wirelessCore(localDevice.getConfiguration());
};

void restartDevice();