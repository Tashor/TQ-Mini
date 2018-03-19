#include "Arduino.h"
#include "TServo.h"
#include "TQMini.h"

// define bluetooth related macros
#define PACKET_SIZE 3
#define CONTROL_BYTE 255

#define DIRECTION_BYTE 1
#define DIRECTION_STOP 0
#define DIRECTION_FORWARD 1
#define DIRECTION_BACKWARD 2
#define DIRECTION_LEFT 3
#define DIRECTION_RIGHT 4

#define SPEED_BYTE 2

#define ACTION_BYTE 3
#define ACTION_SAY_HI 1
#define ACTION_SHAKE 2
#define ACTION_PUSH_UP 3

TQMini tqmini;
int movementDuration = 200;

unsigned long previousMillis = 0;
unsigned int timeNoSignalMillis = 300;   // time (ms) until robot goes in standby after recieving last valid bluetooth packet

void setup() {
  Serial.begin(9600);
  tqmini.initializeServos();
}

void loop() {

  byte buffer[PACKET_SIZE];   // buffer stores incoming bytes

  if(Serial.available() >= PACKET_SIZE) {
    buffer[0] = Serial.read();  // read first byte
    if(buffer[0] == CONTROL_BYTE) { // if first byte is control byte
      for(int i = 1; i < PACKET_SIZE; i++){   // read remaining bytes of the packet
        buffer[i] = Serial.read();
      }
    } else {
      return;   // if first byte isn't the control byte -> no valid packet
    }

    // now do something (e.g. move in a certain direction or change movement speed) based on the packet values
    switch(buffer[1]) {
      case DIRECTION_BYTE:
        switch(buffer[2]) {
          case DIRECTION_STOP:
            tqmini.standby(movementDuration);
            break;
          case DIRECTION_FORWARD:
            tqmini.forward(movementDuration);
            // ToDo: find better solution to clear remaining buffer
            while(Serial.available() > 0){ Serial.read(); }
            break;
          case DIRECTION_BACKWARD:
            tqmini.backward(movementDuration);
            // ToDo: find better solution to clear remaining buffer
            while(Serial.available() > 0){ Serial.read(); }
            break;
          case DIRECTION_RIGHT:
            tqmini.turnRight(movementDuration);
            // ToDo: find better solution to clear remaining buffer
            while(Serial.available() > 0){ Serial.read(); }
            break;
          case DIRECTION_LEFT:
            tqmini.turnLeft(movementDuration);
            // ToDo: find better solution to clear remaining buffer
            while(Serial.available() > 0){ Serial.read(); }
            break;
        }
        break;

      case SPEED_BYTE:
        switch(buffer[2]) { // set movement duration based on the 5 speed steps
          case 1:
            movementDuration = 700;
            break;
          case 2:
            movementDuration = 500;
            break;
          case 3:
            movementDuration = 300;
            break;
          case 4:
            movementDuration = 200;
            break;
          case 5:
            movementDuration = 150;
            break;
        }
        break;

      case ACTION_BYTE:
        switch(buffer[2]) {
          case ACTION_SAY_HI:
            tqmini.hi();
            break;
          case ACTION_SHAKE:
            tqmini.shake();
            break;
          case ACTION_PUSH_UP:
            tqmini.pushUp();
            break;
        }
        break;
    }
    previousMillis = millis();  // valid bluetooth packet done -> update time
  }
  else {  // no serial available
    unsigned long currentMillis = millis();   // get current millis
    if(currentMillis - previousMillis >= timeNoSignalMillis) {   // if the last bluetooth signal is longer than timeNoSignalMillis ago
      tqmini.standby(movementDuration);   // set robot in standby mode
    }
  }
}
