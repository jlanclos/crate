#pragma once

#include <types.h>

class boolean : public type {
 public:
  boolean(bool value);
  boolean(encoding_t bytes);

  bool getValue();
  encoding_t encode() override;

 private:
  bool value = false;
};

static bool isValidBoolean(encoding_t bytes);