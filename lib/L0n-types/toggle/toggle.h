#pragma once

#include <types.h>

class toggle : public type {
 public:
  toggle(bool value);
  toggle(byteString_t bytes);

  bool getValue();
  byteString_t encode() override;
  void decode(byteString_t bytes) override;

 private:
  bool value = false;
};

static bool isValidToggle(byteString_t bytes);