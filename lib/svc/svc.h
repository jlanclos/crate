#pragma once

#include <fstream>

#include "mem.h"
#include "msg.h"

class router {
 public:
  router(mac identifier);

  void receiveMessage(message receivedMessage);
  void route();

 private:
  capsule localDevice;
  messageQueue routingQueue;
};

void restartDevice();

void forwardMessageEspNow(message forwardedMessage);

void forwardMessageMqtt(message forwardedMessage);