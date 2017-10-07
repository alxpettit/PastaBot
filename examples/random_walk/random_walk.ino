// copyleft (c) alex pettit, GNU GPL v3
#include "pastabot.h"

void setup () {
 roverbotSetup(); 
 // if analog input pin 0 is unconnected, random analog
 // noise will cause the call to randomSeed() to generate
 // different seed numbers each time the sketch runs.
 // randomSeed() will then shuffle the random function.
 randomSeed(analogRead(6));
}


void loop() {
  int _speed = 255;
  go(_speed, random(0, 1000));
  turnLeft(_speed, random(0, 1000));
  go(_speed, random(0, 1000));
  turnRight(_speed, random(0,1000));
  go(200, 2000);
}
