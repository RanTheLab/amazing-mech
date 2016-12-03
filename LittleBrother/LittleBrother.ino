/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int SWITCH = 11;
int LIGHT = 12;
int WARNING = 13;

int pos = 0;    // variable to store the servo position
int switchPos = 0;
int MAX = 180;

void setup() {
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(pos);
  pinMode(SWITCH, INPUT);
  pinMode(LIGHT, OUTPUT);
  pinMode(WARNING, OUTPUT);

  Serial.begin(9600);

  Serial.println("Setup exiting...");
}

void loop() {

  switchPos = digitalRead(SWITCH);

  //Serial.println(switchPos);

  if (switchPos == 1) {
    digitalWrite(LIGHT, HIGH);
    pos = 0;

    delay(1500);

    Serial.println("Who turned on the light?");
    for (int i = 0; i < 3; i++) {
      Serial.println("Warning");
      digitalWrite(WARNING, HIGH);
      delay(333);
      digitalWrite(WARNING, LOW);
      delay(333);
    }

    Serial.println("Turning light off...");
    digitalWrite(WARNING, HIGH);
    while (switchPos == 1) {
//    for (pos = 0; pos <= MAX; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(8);                       // waits 15ms for the servo to reach the position
      pos += 3;

      // Emergency reset for junky servo?
      if (pos > MAX) {
        pos = 0;
      }
      switchPos = digitalRead(SWITCH);
    }
    Serial.print("Switch is off, servo position is:");
    Serial.println(pos);
    digitalWrite(LIGHT, LOW);

    digitalWrite(WARNING, LOW);

  Serial.println("Going home");
    for (int reversePos = pos; reversePos >= 0; reversePos -= 5) { // goes from 180 degrees to 0 degrees
      myservo.write(reversePos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
  Serial.println("I am home ============");  
  }

  //delay(3500);
  //Serial.println("Waiting at bottom of looop");
}

