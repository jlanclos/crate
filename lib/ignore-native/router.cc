#include <fileInterface.h>
#include <router.h>
#include <universalDef.h>

// router class
router::router() {
  std::string macString = WiFi.macAddress().c_str();
  mac identifier(macString);
  this->localDevice.setIdentifier(identifier);
  this->localDevice.load(blockType::CONFIG, loadFile(blockType::CONFIG));
  this->localDevice.setConfiguration();
}

void router::route(message currentMessage) {
  idType messageIdTyp = currentMessage.getIdTyp();
  mac messageIdAdd = currentMessage.getIdAdd();
  mac localDeviceIdAdd = this->localDevice.getIdentifier();
  std::vector<dataEntry> payload = currentMessage.getPayload();
  configType deviceType = this->localDevice.getConfiguration().deviceType;
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
          this->localDevice.updateBlock(blockType::DATA, payload[i]);
        }
        saveFile(blockType::DATA, this->localDevice.save(blockType::DATA));
        break;
      case idType::CONFIGBLOCK_UPDATE:
        for (uint8_t i = 0; i < payload.size(); i++) {
          this->localDevice.updateBlock(blockType::CONFIG, payload[i]);
        }
        saveFile(blockType::CONFIG, this->localDevice.save(blockType::CONFIG));
        break;
      default:
        break;
    }
  } else {
    switch (messageIdTyp) {
      case idType::DEVICE_RESTART:
        if (deviceType == configType::PLANET) {
          wireless->forwardMessageEspNow(currentMessage);
        }
        break;
      case idType::DEVICE_PURGE:
        if (deviceType == configType::PLANET) {
          wireless->forwardMessageEspNow(currentMessage);
        }
        break;
      case idType::DATABLOCK_REPORT:
        if (deviceType == configType::PLANET) {
          wireless->forwardMessageMqtt(currentMessage);
        } else if (deviceType == configType::SATELLITE) {
          wireless->forwardMessageEspNow(currentMessage);
        }
        break;
      case idType::DATABLOCK_UPDATE:
        if (deviceType == configType::PLANET) {
          wireless->forwardMessageEspNow(currentMessage);
        }
        break;
      case idType::CONFIGBLOCK_REPORT:
        if (deviceType == configType::PLANET) {
          wireless->forwardMessageMqtt(currentMessage);
        } else if (deviceType == configType::SATELLITE) {
          wireless->forwardMessageEspNow(currentMessage);
        }
        break;
      case idType::CONFIGBLOCK_UPDATE:
        if (deviceType == configType::PLANET) {
          wireless->forwardMessageEspNow(currentMessage);
        }
        break;
      default:
        break;
    }
  }
}

void restartDevice() { deviceRestart(); }