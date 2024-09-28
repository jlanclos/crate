#pragma once

#include <types.h>

class boolean : public type {
 public:
  boolean(bool value);
  boolean(byteString_t bytes);

  bool getValue();
  byteString_t encode() override;

 private:
  bool value = false;
};

static bool isValidBoolean(byteString_t bytes);