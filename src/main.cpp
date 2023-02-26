
#include <Arduino.h>
#include <Ticker.h>

#include "bus.h"
#include "dev.h"
#include "svc.h"

// DEV device;
DEV* device = DEV::lunaCore();
BUS i2c;
Ticker broadcastTimer;

void broadcast() {}

void setup() {
  device->init();
  broadcastTimer.attach_ms(1000, broadcast);
}

void loop() { i2c.readSensors(); }