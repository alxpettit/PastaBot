#include "Arduino.h"

// motor A pins
#define enA 7
#define in1 6
#define in2 5
// motor B pins
#define in3 4
#define in4 3
#define enB 2


// last millisecond count since boot
// recorded at start of function
unsigned long next_millis = 0;

// initialize pins and stuff
void pastabotSetup () {                
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

// takes in speed as integer
// starts motor moving forward if integer is positive, else backward
// absolute value of speed int determines motor speed (duh)
void mov (int speedA, int speedB) {
  // abs() makes negative/postive not matter
  analogWrite(enA, abs(speedA));
  analogWrite(enB, abs(speedB));
  // if speed is positive, move forward
  // else, move backward
  if (speedA > 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else if (speedA < 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  // do same for motor B
  if (speedB > 0) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else if (speedB < 0) {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}


void pastabot_stop() {
  mov(0, 0);
}

// abstraction layer for human-readability for simple rover robot program
void turnLeft (int _speed, int duration) {
  // negative speed on motor B makes it rotate backward
  mov(_speed, -_speed);
  delay(duration);
  pastabot_stop();
}

void turnRight (int _speed, int duration) {
  // negative speed on motor A makes it rotate backward
  mov(-_speed, _speed);
  delay(duration);
  pastabot_stop();
}

// no need for goForward or goBack
// speed neg/pos determines direction of movement.
void go (int _speed, int duration) {
  mov(_speed, _speed);
  delay(duration);
  pastabot_stop();
}


