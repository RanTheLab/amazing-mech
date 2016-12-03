/* Based on Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep

 further modified 2 Dec 2016
 by RanTheLab
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

// Pins being used.
int SWITCH = 11;
int LIGHT = 12;
int WARNING = 13;

int pos = 0;    // variable to store the servo position
int switchPos = 0; // variable to store the switch position
int MAX = 180;  // maximum amount I want the servo to go to

void setup() {
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(pos);  // set the servo to zero position
  // set up pins
  pinMode(SWITCH, INPUT);
  pinMode(LIGHT, OUTPUT);
  pinMode(WARNING, OUTPUT);

  // initialize serial port
  Serial.begin(9600);

  Serial.println("Setup exiting...");
}

void loop() {

  // Read the switch position
  switchPos = digitalRead(SWITCH);

  //Serial.println(switchPos);

  // if it is on, we got work to do!
  if (switchPos == 1) {
    // turn on the light.
    digitalWrite(LIGHT, HIGH);
    // initialize the servo position value
    pos = 0;

    Serial.println("Who turned on the light?");
    // flash the warning light.
    for (int i = 0; i < 3; i++) {
      Serial.println("Warning");
      digitalWrite(WARNING, HIGH);
      delay(333);
      digitalWrite(WARNING, LOW);
      delay(333);
    }

    Serial.println("Turning warning light off...");
    digitalWrite(WARNING, HIGH);

    // Move servo until the switch goes off.
    while (switchPos == 1) {
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(8);                       // waits 8ms for the servo to reach the position
      pos += 3;                       // bump up the servo position a tiny bit

      // Emergency reset for junky servo?
      if (pos > MAX) {
        pos = 0;
      }
      // Check is we turned the light off yet...
      switchPos = digitalRead(SWITCH);
    }
    
    Serial.print("Switch is off, servo position is:");
    Serial.println(pos);

    // turn off the warning and the light.
    digitalWrite(WARNING, LOW);
    digitalWrite(LIGHT, LOW);

    // send the servo back to the home position.
    Serial.println("Going home");
    for (int reversePos = pos; reversePos >= 0; reversePos -= 5) { // goes from 180 degrees to 0 degrees
      myservo.write(reversePos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
    // Do it all over again...
    Serial.println("I am home ============");  
  }

  // useful for debugging...
  //delay(3500);
  //Serial.println("Waiting at bottom of looop");
}

