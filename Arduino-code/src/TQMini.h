#ifndef tqmini_h
#define tqmini_h

#include "TServo.h"

// REFRESH_INTERVAL in "Servo.h" is in microseconds -> calculate milliseconds
#define REFRESH_INTERVAL_MILLIS (REFRESH_INTERVAL / 1000) 

// define servo related macros
#define NUMBER_OF_LEG_SERVOS 8

#define FRONT_LEFT_HIP 0
#define FRONT_RIGHT_HIP 1
#define FRONT_LEFT_LEG 2
#define FRONT_RIGHT_LEG 3
#define BACK_LEFT_HIP 4
#define BACK_RIGHT_HIP 5
#define BACK_LEFT_LEG 6
#define BACK_RIGHT_LEG 7


class TQMini {
  public:
    void setServo(uint8_t servoID, uint8_t servoAngle);
    void setLegServos(uint8_t frontLeftHip, uint8_t frontRightHip, uint8_t frontLeftLeg, uint8_t frontRightLeg,
                    uint8_t backLeftHip, uint8_t backRightHip, uint8_t backLeftLeg, uint8_t backRightLeg,
                    int duration);  
    void initializeServos();

    void standby(int duration = 0);
    void forward(int duration = 200);
    void backward(int duration = 200);
    void turnRight(int duration = 200);
    void turnLeft(int duration = 200);
    void hi();
    void pushUp();
    void shake();

  private:
    void attachAllServos();
    void detachAllServos();
  
    TServo servos[NUMBER_OF_LEG_SERVOS];
    uint8_t arduinoPins[NUMBER_OF_LEG_SERVOS];
    int8_t trimValues[NUMBER_OF_LEG_SERVOS];

    float sineEffectInPercent = 1; // value between 0 and 1, 0 == no sine wave / 1 == full sine wave
};

#endif
