
#include <Servo.h>

Servo myservo; 

void setup() {
  myservo.attach(11);  // attaches the servo on pin 11 to the servo object
}

void loop() {
 myservo.write(90);
 delay(100000);   //就只转个90度
}
