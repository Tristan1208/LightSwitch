#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo;  // create servo object to control a servo
int servoPin = 13; // GPIO pin for servo control
int pos =0;    // variable to store the servo position

void setup() {
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	servo.setPeriodHertz(50);    // standard 50 hz servo
	servo.attach(servoPin, 500, 2400);
}

void loop() {
		servo.write(180);    
		delay(2000);
		servo.write(0);
		delay(2000);             
}

