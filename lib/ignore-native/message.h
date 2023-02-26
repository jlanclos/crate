#pragma once

#include <definitions.h>
#include <entry.h>
#include <stdint.h>

#include <string>
#include <vector>

enum class idType : uint8_t {
  UNDEFINED = 0,
  DEVICE_RESTART = 1,
  DEVICE_PURGE = 2,
  CONFIGBLOCK_REPORT = 20,
  DATABLOCK_REPORT = 21,
  CONFIGBLOCK_UPDATE = 40,
  DATABLOCK_UPDATE = 41,
};

class message {
 public:
  message();
  message(std::vector<uint8_t> messageRaw);

  idType getIdTyp();
  mac getIdAdd();
  std::vector<entry> getPayload();
  void setIdTyp(idType newIdTyp);
  void setIdAdd(mac newIdAdd);
  void setPayload(std::vector<entry> newPayload);
  std::vector<uint8_t> toRaw();

 private:
  idType idTyp;
  mac idAdd;
  std::vector<entry> payload;

  void fromRaw(const std::vector<uint8_t>& messageRaw);
};
struct messageReadSummary {
  bool success;
  message message;
};
class messageQueue {
 public:
  messageQueue();

  void purge();
  messageReadSummary read();
  void pop();
  void push(idType idTyp, mac idArr, std::vector<entry> payload);
  void push(message messageIn);

 private:
  std::vector<message> queue;
};

std::string uint8tToString(uint8_t valueIn);