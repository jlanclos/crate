#include <sequencer.h>

// sequencer class
sequencer::sequencer() {
  this->start = 0;
  this->end = 4294967295;
  this->step = 1;
  this->value = this->start;
}
sequencer::sequencer(uint32_t start, uint32_t end) {
  this->start = start;
  this->end = end;
  this->step = 1;
  this->value = this->start;
}
sequencer::sequencer(uint32_t start, uint32_t end, uint32_t step) {
  this->start = start;
  this->end = end;
  this->step = step;
  this->value = this->start;
}

uint32_t sequencer::getStart() { return this->start; }

uint32_t sequencer::getEnd() { return this->end; }

uint32_t sequencer::getStep() { return this->step; }

uint32_t sequencer::getCurrent() { return this->value; }

uint32_t sequencer::next() {
  uint32_t startValue = this->start;
  uint32_t endValue = this->end;
  uint32_t stepValue = this->step;
  uint32_t currentValue = this->value;
  if (startValue <= endValue) {
    if ((currentValue) >= endValue) {
      currentValue = startValue;
    } else {
      currentValue += stepValue;
    }
  } else {
    if ((currentValue) <= endValue) {
      currentValue = startValue;
    } else {
      currentValue -= stepValue;
    }
  }
  this->value = currentValue;
  return currentValue;
}