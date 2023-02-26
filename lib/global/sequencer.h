#pragma once

#include <cstdint>

class sequencer {
 public:
  sequencer();
  sequencer(uint32_t start, uint32_t end);
  sequencer(uint32_t start, uint32_t end, uint32_t step);

  uint32_t getStart();
  uint32_t getEnd();
  uint32_t getStep();
  uint32_t getCurrent();
  uint32_t next();

 private:
  uint32_t start;
  uint32_t end;
  uint32_t step;
  uint32_t value;
};