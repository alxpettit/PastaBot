// Copyleft (c) Alex Pettit, GNU GPL v3
// PastaBot IR Example Code

// Makes PastaBot respond to commands given via infared
// instead of functioning autonomously
// Requires IRRemote Arduino Library (https://github.com/z3t0/Arduino-IRremote)

/*

   ***
  *******
 \-------/

*/

// roverbot API; defines code for controlling PastaBot chassis
#include <pastabot.h>

// Defines Xinda remote control's hex codes for button presses
#include <xinda.h>

// IR Remote API -- reads raw remote serial input and outputs hex data
#include <IRremote.h>

// Speed at which to move motors
// Supposed to be set between 0 and 255
#define SPEED 255

// Initialize IR RECeiVing class with digital I/O pin 11
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);

// Class instance for decoding IR input
decode_results results;

// Function runs once at arduino boot
void setup()
{
  // Initialize pins associated with
  // PastaBot motor control
  pastabotSetup();
  // Initialize IR input stuff
  irrecv.enableIRIn();
}

unsigned long millis_until_stop = 0;

void onSignal()
{
  // Take action based on results.value
  // (result of decoding IR signal)
  switch (results.value) {
    case XINDA_UP:
      // moving forward
      mov(SPEED, SPEED);
      break;
    case XINDA_LEFT:
      // moving left
      mov(SPEED, -SPEED);
      break;
    case XINDA_RIGHT:;
      // moving right
      mov(-SPEED, SPEED);
      break;
    case XINDA_DOWN:
      // moving backward
      mov(-SPEED, -SPEED);
      break;
  }
  // stops at 150 ms unless another signal is received (if the signal is the same, it keeps moving).
  millis_until_stop = millis() + 150;
    
}

// Function loops over and over while arduino is active
void loop() {
  
  // Function returns true if we are receiving a signal
  if (irrecv.decode(&results)) {
    // Ignore all non NEC signals
    if (results.decode_type == NEC) {
      // Run signal handler function
      onSignal();
    }
    // accept further signals
    irrecv.resume();
  }
  
  // if millis_until_stop is less than millis (millisecond clock value)
  // then shut down all movement and wait for further instructiojn
  if (millis_until_stop < millis()) {
    mov(0, 0);
  }
  
  // small delay for stability
  delay(10);
}
