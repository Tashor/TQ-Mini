// This servo-class extends the standard Arduino Servo.h library.
// It allows you to set a min and max angle for your servo.
// Everytime you try to set an angle outside of the min/max boundaries,
// the angle is set to min/max instead.
// It is usefull to protect your creations (e.g. robots) if physical barriers
// don't allow the full 180 degrees of your servo.

#ifndef tservo_h
#define tservo_h

#include <Servo.h>
#include <Arduino.h>

#define NEW_MIN_PULSE_WIDTH 550
#define NEW_MAX_PULSE_WIDTH 2450

class TServo : public Servo {
  public:
    TServo();
    void setMinAngle(uint8_t value);
    void setMaxAngle(uint8_t value);
    void setAngle(int value);
    void setMicroseconds(int value);

  private:
    uint8_t minAngle;
    uint8_t maxAngle;
    int minMicros;
    int maxMicros;
};

#endif
