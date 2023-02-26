#include "mem.h"

#include "LittleFS.h"

// capsule class
capsule::capsule() {
  this->setIdentifier(mac(0x00, 0x00, 0x00, 0x00, 0x00, 0x00));
  this->mountFileSystem();
  this->load();
  this->setSafeMode();
}

void capsule::purge() {
  this->dataBlock.clear();
  this->configBlock.clear();
  this->setSafeMode();
}

mac capsule::getIdentifier() { return this->identifier; }

void capsule::setIdentifier(mac identifier) { this->identifier = identifier; }

void capsule::updateBlock(blockType block, dataEntry entryIn) {
  switch (block) {
    case blockType::DATABLOCK:
      this->blockPush(this->dataBlock, entryIn);
      break;
    case blockType::CONFIGBLOCK:
      this->blockPush(this->configBlock, entryIn);
      break;
    default:
      break;
  }
}

std::pair<operationStatus, dataEntry> capsule::reportBlock(blockType block, uint8_t id) {
  std::pair<operationStatus, dataEntry> blockPullResult;
  blockPullResult.first = operationStatus::FAIL;
  switch (block) {
    case blockType::DATABLOCK:
      blockPullResult = this->blockPull(this->dataBlock, id);
      break;
    case blockType::CONFIGBLOCK:
      blockPullResult = this->blockPull(this->configBlock, id);
      break;
    default:
      break;
  }
  return blockPullResult;
}

void capsule::save() {
  this->memory.clear();
  uint8_t identifierSize = this->identifier.getArray().size();
  uint8_t dataBlockSize = this->dataBlock.size();
  uint8_t configBlockSize = this->configBlock.size();
  this->memory.push_back(identifierSize);
  this->memory.push_back(dataBlockSize);
  this->memory.push_back(configBlockSize);
  for (uint8_t i = 0; i < identifierSize; i++) {
    this->memory.push_back(this->identifier.getArray()[i]);
  }
  for (uint8_t i = 0; i < dataBlockSize; i++) {
    uint8_t entryDataSize = this->dataBlock[i].getDataSize();
    this->memory.push_back(this->dataBlock[i].getIdTgt());
    this->memory.push_back(entryDataSize);
    for (uint8_t j = 0; j < entryDataSize; j++) {
      this->memory.push_back(this->dataBlock[i].getData()[j]);
    }
  }
  for (uint8_t i = 0; i < configBlockSize; i++) {
    uint8_t entryDataSize = this->configBlock[i].getDataSize();
    this->memory.push_back(this->configBlock[i].getIdTgt());
    this->memory.push_back(entryDataSize);
    for (uint8_t j = 0; j < entryDataSize; j++) {
      this->memory.push_back(this->configBlock[i].getData()[j]);
    }
  }
  File capsuleFile = LittleFS.open(CAPSULE_FILE_PATH, "w+");
  if (!capsuleFile) {
    Serial.printf("Failed to open file.\n");
  } else {
    Serial.printf("Opened file successfully.\n");
    for (uint16_t i = 0; i < this->memory.size(); i++) {
      capsuleFile.write(this->memory[i]);
    }
  }
  capsuleFile.close();
}

void capsule::load() {
  this->memory.clear();
  this->dataBlock.clear();
  this->configBlock.clear();
  File capsuleFile = LittleFS.open(CAPSULE_FILE_PATH, "r");
  if (!capsuleFile) {
    Serial.printf("Failed to open file.\n");
  } else {
    Serial.printf("Opened file successfully.\n");
    for (uint16_t i = 0; i < capsuleFile.size(); i++) {
      this->memory.push_back(capsuleFile.read());
    }
  }
  capsuleFile.close();
  uint16_t iterator = 0;
  uint8_t identifierSize = this->memory[iterator];
  iterator++;
  uint8_t dataBlockSize = this->memory[iterator];
  iterator++;
  uint8_t configBlockSize = this->memory[iterator];
  iterator++;
  std::vector<uint8_t> id;
  uint16_t identifierEnd = iterator + identifierSize;
  for (; iterator < identifierEnd; iterator++) {
    id.push_back(this->memory[iterator]);
  }
  this->identifier = mac(id[0], id[1], id[2], id[3], id[4], id[5]);
  for (uint8_t i = 0; i < dataBlockSize; i++) {
    dataEntry entry(this->memory[iterator]);
    iterator++;
    uint8_t entryDataSize = this->memory[iterator];
    uint8_t entryDataEnd = entryDataSize + iterator;
    iterator++;
    std::vector<uint8_t> entryData;
    for (; iterator < entryDataEnd; iterator++) {
      entryData.push_back(this->memory[iterator]);
    }
    entryData.push_back(this->memory[iterator]);
    entry.setData(entryData);
    this->dataBlock.push_back(entry);
    iterator++;
  }
  for (uint8_t i = 0; i < configBlockSize; i++) {
    dataEntry entry(this->memory[iterator]);
    iterator++;
    uint8_t entryDataSize = this->memory[iterator];
    uint8_t entryDataEnd = entryDataSize + iterator;
    iterator++;
    std::vector<uint8_t> entryData;
    for (; iterator < entryDataEnd; iterator++) {
      entryData.push_back(this->memory[iterator]);
    }
    entryData.push_back(this->memory[iterator]);
    entry.setData(entryData);
    this->configBlock.push_back(entry);
    iterator++;
  }
}

void capsule::setSafeMode() {
  this->updateBlock(blockType::CONFIGBLOCK,
                    createAnalogUInt8Entry(configId::TYPE, configType::PLANET));
  this->updateBlock(blockType::CONFIGBLOCK,
                    createDigitalEntry(configId::PROGRAM, configProgram::TRUE));
  this->updateBlock(blockType::CONFIGBLOCK,
                    createAnalogUInt8Entry(configId::CHANNEL, configChannel::CHANNEL_3));
  this->updateBlock(
      blockType::CONFIGBLOCK,
      createMacEntry(configId::PLANET_MAC_ADDRESS, mac(0x32, 0x42, 0xB4, 0x87, 0x99, 0x23)));
  this->updateBlock(blockType::CONFIGBLOCK,
                    createStringEntry(configId::WIFI_SSID, "safe wifi ssid"));
  this->updateBlock(blockType::CONFIGBLOCK,
                    createStringEntry(configId::WIFI_PASSWORD, "safe wifi password"));
  this->updateBlock(blockType::CONFIGBLOCK,
                    createIpEntry(configId::MQTT_HOST, ip(192, 168, 2, 153)));
  this->updateBlock(blockType::CONFIGBLOCK, createAnalogUInt16Entry(configId::MQTT_PORT, 1883));
  this->updateBlock(blockType::CONFIGBLOCK,
                    createStringEntry(configId::MQTT_USERNAME, "safe mqtt username"));
  this->updateBlock(blockType::CONFIGBLOCK,
                    createStringEntry(configId::MQTT_PASSWORD, "safe mqtt password"));
}

void capsule::mountFileSystem() {
  if (!LittleFS.begin()) {
    Serial.printf("Failed to mount the file system.\n");
  } else {
    Serial.printf("File system mounted successfully.\n");
  }
}

void capsule::blockPush(std::vector<dataEntry>& destinationBlock, dataEntry entryIn) {
  bool updateComplete = false;
  if (destinationBlock.size() > 0) {
    for (uint8_t i = 0; i < destinationBlock.size(); i++) {
      if (destinationBlock[i].getIdTgt() == entryIn.getIdTgt()) {
        destinationBlock[i].setData(entryIn.getData());
        updateComplete = true;
        break;
      }
    }
  }
  if (updateComplete == false) {
    destinationBlock.push_back(entryIn);
    updateComplete = true;
  }
}

std::pair<operationStatus, dataEntry> capsule::blockPull(std::vector<dataEntry>& destinationBlock,
                                                         uint8_t id) {
  std::pair<operationStatus, dataEntry> blockPullResult;
  blockPullResult.first = operationStatus::FAIL;
  if (destinationBlock.size() > 0) {
    for (uint8_t i = 0; i < destinationBlock.size(); i++) {
      if (destinationBlock[i].getIdTgt() == id) {
        blockPullResult.first = operationStatus::SUCCESS;
        blockPullResult.second = destinationBlock[i];
      }
    }
  }
  return blockPullResult;
}