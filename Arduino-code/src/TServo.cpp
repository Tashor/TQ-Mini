#include "TServo.h"

TServo::TServo() {
  minAngle = 0;
  maxAngle = 180;
  minMicros = NEW_MIN_PULSE_WIDTH;
  maxMicros = NEW_MAX_PULSE_WIDTH;
}

void TServo::setMinAngle(uint8_t value) {
  if (value > 0 && value < maxAngle) {
    minAngle = value;
    minMicros = map(value, 0, 180, NEW_MIN_PULSE_WIDTH, NEW_MAX_PULSE_WIDTH);
  }
}

void TServo::setMaxAngle(uint8_t value) {
  if (value < 180 && value > minAngle) {
    maxAngle = value;
    maxMicros = map(value, 0, 180, NEW_MIN_PULSE_WIDTH, NEW_MAX_PULSE_WIDTH);
  }
}

void TServo::setAngle(int value) {
  value = constrain(value, minAngle, maxAngle);
  this->write(value);
}

void TServo::setMicroseconds(int value) {
  value = constrain(value, minMicros, maxMicros);
  this->writeMicroseconds(value);
}
