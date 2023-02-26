#pragma once

#include <array>
#include <string>
#include <vector>

#include "def.h"

#define MESSAGE_QUEUE_MAX_SIZE 50

class message {
 public:
  message();

  idType getIdTyp();
  mac getIdAdd();
  std::vector<dataEntry> getPayload();
  void setIdTyp(idType newIdTyp);
  void setIdAdd(mac newIdAdd);
  void setPayload(std::vector<dataEntry> newPayload);
  void fromString(const std::string& stringIn);
  std::string toString();

 private:
  idType idTyp;
  mac idAdd;
  std::vector<dataEntry> payload;

  void readIdTyp(const std::string& messageString);
  void readIdAdd(const std::string& messageString);
  void readPayload(const std::string& messageString, std::vector<uint8_t> dataIndicies);
};

class messageQueue {
 public:
  messageQueue();

  void purge();
  std::pair<operationStatus, message> read();
  void pop();
  void push(idType idTyp, mac idArr, std::vector<dataEntry> payload);
  void push(message messageIn);

 private:
  std::vector<message> queue;
};

std::vector<uint8_t> findDataIndicies(const std::string& stringIn);
std::string uint8tToString(uint8_t valueIn);