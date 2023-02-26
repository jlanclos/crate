#include "svc.h"

// router class
router::router(mac identifier) { this->localDevice.setIdentifier(identifier); }

void router::receiveMessage(message receivedMessage) { this->routingQueue.push(receivedMessage); }

void router::route() {
  if (this->routingQueue.read().first == operationStatus::SUCCESS) {
    if (this->localDevice.reportBlock(blockType::CONFIGBLOCK, configId::TYPE).first ==
        operationStatus::SUCCESS) {
      message currentMessage = this->routingQueue.read().second;
      idType messageIdTyp = currentMessage.getIdTyp();
      mac messageIdAdd = currentMessage.getIdAdd();
      mac localDeviceIdAdd = this->localDevice.getIdentifier();
      std::vector<dataEntry> payload = currentMessage.getPayload();
      configType deviceType =
          (configType)this->localDevice.reportBlock(blockType::CONFIGBLOCK, configId::TYPE)
              .second.pullAnalogUInt8()
              .second;
      this->localDevice.reportBlock(blockType::CONFIGBLOCK, configId::TYPE).first;
      if (messageIdAdd.getArray() == localDeviceIdAdd.getArray()) {
        switch (messageIdTyp) {
          case idType::DEVICE_RESTART:
            restartDevice();
            break;
          case idType::DEVICE_PURGE:
            this->localDevice.purge();
            break;
          case idType::DATABLOCK_UPDATE:
            for (uint8_t i = 0; i < payload.size(); i++) {
              this->localDevice.updateBlock(blockType::DATABLOCK, payload[i]);
            }
            this->localDevice.save();
            break;
          case idType::CONFIGBLOCK_UPDATE:
            for (uint8_t i = 0; i < payload.size(); i++) {
              this->localDevice.updateBlock(blockType::CONFIGBLOCK, payload[i]);
            }
            this->localDevice.save();
            break;
          default:
            break;
        }
      } else {
        switch (messageIdTyp) {
          case idType::DEVICE_RESTART:
            if (deviceType == configType::PLANET) {
              forwardMessageEspNow(currentMessage);
            }
            break;
          case idType::DEVICE_PURGE:
            if (deviceType == configType::PLANET) {
              forwardMessageEspNow(currentMessage);
            }
            break;
          case idType::DATABLOCK_REPORT:
            if (deviceType == configType::PLANET) {
              forwardMessageMqtt(currentMessage);
            } else if (deviceType == configType::SATELLITE) {
              forwardMessageEspNow(currentMessage);
            }
            break;
          case idType::DATABLOCK_UPDATE:
            if (deviceType == configType::PLANET) {
              forwardMessageEspNow(currentMessage);
            }
            break;
          case idType::CONFIGBLOCK_REPORT:
            if (deviceType == configType::PLANET) {
              forwardMessageMqtt(currentMessage);
            } else if (deviceType == configType::SATELLITE) {
              forwardMessageEspNow(currentMessage);
            }
            break;
          case idType::CONFIGBLOCK_UPDATE:
            if (deviceType == configType::PLANET) {
              forwardMessageEspNow(currentMessage);
            }
            break;
          default:
            break;
        }
      }
    }
  }
}

void restartDevice() { printf("Device is restarting..."); }

void forwardMessageEspNow() { printf("Forwarding message over esp-now"); }

void forwardMessageMqtt() { printf("Forwarding message to mqtt"); }