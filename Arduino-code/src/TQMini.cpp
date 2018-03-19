#include "TQMini.h"

/*
  Servo location and corresponding pins on Arduino:
   ---------------------
  | 4    2       3    5 |
   -----     .     -----
        |   / \   |
        |    |    |
        |    |    |
   -----           -----
  | 8    6       7    9 |
   ---------------------
*/

void TQMini::initializeServos() {
  
  // set servo pins
  arduinoPins[FRONT_LEFT_HIP] = 2;
  arduinoPins[FRONT_RIGHT_HIP] = 3;
  arduinoPins[FRONT_LEFT_LEG] = 4;
  arduinoPins[FRONT_RIGHT_LEG] = 5;
  arduinoPins[BACK_LEFT_HIP] = 6;
  arduinoPins[BACK_RIGHT_HIP] = 7;
  arduinoPins[BACK_LEFT_LEG] = 8;
  arduinoPins[BACK_RIGHT_LEG] = 9;

  // set trim values, used for servo calibration
  trimValues[FRONT_LEFT_HIP] = 15;
  trimValues[FRONT_RIGHT_HIP] = -12;
  trimValues[FRONT_LEFT_LEG] = 10;
  trimValues[FRONT_RIGHT_LEG] = -20;
  trimValues[BACK_LEFT_HIP] = -8;
  trimValues[BACK_RIGHT_HIP] = 0;
  trimValues[BACK_LEFT_LEG] = -10;
  trimValues[BACK_RIGHT_LEG] = 7;


  // attach servos to pins
  attachAllServos();

  // resting position
  standby();
}

void TQMini::standby(int duration) {
  //           FLH, FRH, FLL, FRL, BLH, BRH, BLL, BRL, ms 
  setLegServos( 60, 120,  90,  90, 120,  60,  90,  90, duration);
}

void TQMini::forward(int duration) {
  //           FLH, FRH, FLL, FRL, BLH, BRH, BLL, BRL, ms
  setLegServos( 75, 135,  90, 120, 105,  45, 120,  90, duration);   // FRL+BLL up & FRH+BLH forward & FLH+BRH backward
  setLegServos( 75, 135,  90,  90, 105,  45,  90,  90, duration/2); // FRL+BLL down
  setLegServos( 45, 105,  60,  90, 135,  75,  90,  60, duration);   // FLL+BRL up & FRH+BLH backward & FLH+BRH forward
  setLegServos( 45, 105,  90,  90, 135,  75,  90,  90, duration/2); // FLL+BRL down
}

void TQMini::backward(int duration) {
  //           FLH, FRH, FLL, FRL, BLH, BRH, BLL, BRL, ms
  setLegServos( 45, 105,  90, 120, 135,  75, 120,  90, duration);   // FRL+BLL up & FRH+BLH backward & FLH+BRH forward
  setLegServos( 45, 105,  90,  90, 135,  75,  90,  90, duration/2); // FRL+BLL down
  setLegServos( 75, 135,  60,  90, 105,  45,  90,  60, duration);   // FLL+BRL up & FRH+BLH forward & FLH+BRH backward
  setLegServos( 75, 135,  90,  90, 105,  45,  90,  90, duration/2); // FLL+BRL down
}

void TQMini::turnRight(int duration) {
  //           FLH, FRH, FLL, FRL, BLH, BRH, BLL, BRL, ms
  setLegServos( 90,  90,  90, 120,  90,  90, 120,  90, duration);   // FRL+BLL up & FRH+BLH clockwise & FLH+BRH counterclockwise 
  setLegServos( 90,  90,  90,  90,  90,  90,  90,  90, duration/2); // FRL+BLL down
  setLegServos( 60, 120,  60,  90, 120,  60,  90,  60, duration);   // FLL+BRL up & FRH+BLH counterclockwise & FLH+BRH clockwise
  setLegServos( 60, 120,  90,  90, 120,  60,  90,  90, duration/2);   // FLL+BRL down
}

void TQMini::turnLeft(int duration) {
  //           FLH, FRH, FLL, FRL, BLH, BRH, BLL, BRL, ms
  setLegServos( 90,  90,  60,  90,  90,  90,  90,  60, duration);   // FLL+BRL up & FRH+BLH clockwise & FLH+BRH counterclockwise 
  setLegServos( 90,  90,  90,  90,  90,  90,  90,  90, duration/2); // FLL+BRL down
  setLegServos( 60, 120,  90, 120, 120,  60, 120,  90, duration);   // FRL+BLL up & FRH+BLH counterclockwise & FLH+BRH clockwise
  setLegServos( 60, 120,  90,  90, 120,  60,  90,  90, duration/2);   // FRL+BLL down
}


void TQMini::hi() {
  //           FLH, FRH, FLL, FRL, BLH, BRH, BLL, BRL, ms 
  setLegServos( 40, 150, 130, 180, 130,  50, 160,  20, 400);
  setLegServos( 40, 150, 130, 130, 130,  50, 160,  20, 400);  // FRL down
  setLegServos( 40, 150, 130, 180, 130,  50, 160,  20, 400);  // FRL up
  setLegServos( 40, 150, 130, 130, 130,  50, 160,  20, 400);  // FRL down
  setLegServos( 40, 150, 130, 180, 130,  50, 160,  20, 400);  // FRL up
  setLegServos( 40, 170, 130, 180, 130,  50, 160,  20, 400);  // FRH left
  setLegServos( 40, 100, 130, 180, 130,  50, 160,  20, 400);  // FRH right
  setLegServos( 40, 170, 130, 180, 130,  50, 160,  20, 400);  // FRH left
  setLegServos( 40, 100, 130, 180, 130,  50, 160,  20, 400);  // FRH right
  standby(1000);
}

void TQMini::pushUp() {
  //           FLH, FRH, FLL, FRL, BLH, BRH, BLL, BRL, ms 
  setLegServos(100,  80, 120,  60, 180,   0, 155,  25, 500);   // start position
  delay(1500);
  setLegServos(100,  80,  25, 155, 180,   0, 155,  25, 500);  // down
  setLegServos(100,  80, 120,  60, 180,   0, 155,  25, 500);  // up
  setLegServos(100,  80,  25, 155, 180,   0, 155,  25, 600);  // down
  setLegServos(100,  80, 120,  60, 180,   0, 155,  25, 600);  // up
  setLegServos(100,  80,  25, 155, 180,   0, 155,  25, 800);  // down
  setLegServos(100,  80, 120,  60, 180,   0, 155,  25, 800);  // up
  setLegServos(100,  80,  25, 155, 180,   0, 155,  25, 1000); // down
  setLegServos(100,  80,  90,  90, 180,   0, 155,  25, 1800); // slow half way up
  setLegServos(100,  80,  25, 155, 180,   0, 155,  25, 250);  // fast down
  delay(2000);
  standby(1500);
}

void TQMini::shake() {
  //           FLH, FRH, FLL, FRL, BLH, BRH, BLL, BRL, ms 
  setLegServos( 90, 150,  90,  90, 150,  90,  90,  90, 500);  // turn body counterclockwise
  setLegServos( 30,  90,  90,  90,  90,  30,  90,  90, 500);  // turn body clockwise
  setLegServos( 90, 150,  90,  90, 150,  90,  90,  90, 600); // turn body counterclockwise slow
  setLegServos( 30,  90,  90,  90,  90,  30,  90,  90, 600); // turn body clockwise slow
  setLegServos( 30,  90,  30, 150,  90,  30,  90,  90, 500); // front legs down
  setLegServos( 90, 150,  30, 150, 150,  90,  90,  90, 500); // turn body counterclockwise
  setLegServos( 30,  90,  30, 150,  90,  30,  90,  90, 500); // turn body clockwise
  setLegServos( 90, 150,  30, 150, 150,  90,  90,  90, 600);  // turn body counterclockwise slow
  setLegServos( 30,  90,  30, 150,  90,  30,  90,  90, 600);  // turn body clockwise slow
  setLegServos( 90, 150,  30, 150, 150,  90,  90,  90, 700);  // turn body counterclockwise slower
  setLegServos( 30,  90,  30, 150,  90,  30,  90,  90, 700);  // turn body clockwise slower
  standby(1000);
}

// set servo number "servoID" to angle "servoAngle"
void TQMini::setServo(uint8_t servoID, uint8_t servoAngle) {
  servos[servoID].setAngle(servoAngle + trimValues[servoID]);
}

// set angle of all leg servos in a certain duration (in milliseconds) with sine wave movement
// to simulate a more natural like movement
void TQMini::setLegServos(uint8_t frontLeftHip, uint8_t frontRightHip, uint8_t frontLeftLeg, uint8_t frontRightLeg, 
                        uint8_t backLeftHip, uint8_t backRightHip, uint8_t backLeftLeg, uint8_t backRightLeg, int duration) {
  
  uint8_t positions[NUMBER_OF_LEG_SERVOS] = {frontLeftHip, frontRightHip, frontLeftLeg, frontRightLeg, 
                          backLeftHip, backRightHip, backLeftLeg, backRightLeg};
                          
  if(duration > 0) {    // calculate needed steps for each servo, then set all servos in motion with individual steps
    
    // calculate needed number of steps by dividing the duration (ms) 
    // by the refresh interval of the servos in milliseconds (standard: 20ms)
    int numberOfSteps = duration / REFRESH_INTERVAL_MILLIS;
    if (numberOfSteps < 1)  // make sure that there is at least 1 step
      numberOfSteps = 1;

    int servoTargetMicrosArray[NUMBER_OF_LEG_SERVOS];
    int servoStartMicrosArray[NUMBER_OF_LEG_SERVOS];
    int servoDeltaMicrosArray[NUMBER_OF_LEG_SERVOS];
    
    // calculate all servo-travel-distances in microseconds
    for (int i = 0; i < NUMBER_OF_LEG_SERVOS; i++) {  
      int currentServoTargetAngle = positions[i] + trimValues[i];
      currentServoTargetAngle = constrain(currentServoTargetAngle, 0, 180);
      servoTargetMicrosArray[i] = map(currentServoTargetAngle, 0, 180, NEW_MIN_PULSE_WIDTH, NEW_MAX_PULSE_WIDTH);
      servoStartMicrosArray[i] = servos[i].readMicroseconds();
      servoDeltaMicrosArray[i] = abs(servoTargetMicrosArray[i] - servoStartMicrosArray[i]);
    }
    
    // calculate the new servo position for each servo and set them to their new position
    for (int i = 1; i <= numberOfSteps; i++) {  
      // calculate the step size in percent for the current step
      float stepSizeInPercent = (1 - sin(i / float(numberOfSteps) * PI + PI/2)) / 2 * sineEffectInPercent 
                                  + i / float(numberOfSteps) * (1 - sineEffectInPercent);
                                  
      for (int j = 0; j < NUMBER_OF_LEG_SERVOS; j++) {  // for each servo:
        int currentStepMicros;
        // multiply the current step size by the whole servo-travel-distance
        // and add this value to the value of the start position of the servo if the target position is greater than the start position
        // or subtract it, if the target position is smaller than the start position
        // start- and target positions are the puls-widths in microseconds
        if (servoTargetMicrosArray[j] > servoStartMicrosArray[j]) {
          currentStepMicros = servoStartMicrosArray[j] + servoDeltaMicrosArray[j] * stepSizeInPercent;
        }
        else {
          currentStepMicros = servoStartMicrosArray[j] - servoDeltaMicrosArray[j] * stepSizeInPercent;
        }
        servos[j].setMicroseconds(currentStepMicros);   // set current servo to its new position
      }
      // ToDo: change delay to interupt + timer
      delay(REFRESH_INTERVAL_MILLIS);
    }
  } 
  else {    // if duration == 0, move all servos with max speed to the target position
    for(int i = 0; i < NUMBER_OF_LEG_SERVOS; i++) {
      servos[i].setAngle(positions[i] + trimValues[i]);
    }
  }
}

void TQMini::attachAllServos() {
  for(int i = 0; i < NUMBER_OF_LEG_SERVOS; i++) {
    servos[i].attach(arduinoPins[i], NEW_MIN_PULSE_WIDTH, NEW_MAX_PULSE_WIDTH);
  }
  servos[BACK_RIGHT_HIP].setMinAngle(8);
}

void TQMini::detachAllServos() {
  for (int i = 0; i < NUMBER_OF_LEG_SERVOS; i++) {
    servos[i].detach();
  }
}



