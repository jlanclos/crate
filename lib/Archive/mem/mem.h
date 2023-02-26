#pragma once

#define CAPSULE_FILE_PATH "capsule"

#include <array>
#include <string>
#include <vector>

#include "def.h"

enum class blockType : uint8_t { DATABLOCK = 0x00, CONFIGBLOCK = 0x01 };

class capsule {
 public:
  capsule();

  void purge();
  mac getIdentifier();
  void setIdentifier(mac identifier);
  void updateBlock(blockType block, dataEntry entryIn);
  std::pair<operationStatus, dataEntry> reportBlock(blockType block, uint8_t id);
  void save();
  void load();

 private:
  mac identifier;
  std::vector<dataEntry> dataBlock;
  std::vector<dataEntry> configBlock;
  std::vector<uint8_t> memory;

  void setSafeMode();
  void mountFileSystem();
  void blockPush(std::vector<dataEntry>& destinationBlock, dataEntry entryIn);
  std::pair<operationStatus, dataEntry> blockPull(std::vector<dataEntry>& destinationBlock,
                                                  uint8_t id);
};