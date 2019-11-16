/*
  ESC_Knob
  Controlling an R/C ESC (Electronic Speed Controller) speed using a potentiometer (variable resistor)
  and an Adafruit PCA9685 16-Channel 12-bit PWM/Servo Driver - I2C interface
  This is using a modified version of the "Knob" example in the "Servo" library.

  Based on the 27 April 2017 Sketch by Eric Nantel and his RC_ESC library for Robot shop
  rewritten for use in the I2C_Array_ESC library with the Adafruit PCA9685 16-Channel 12-bit PWM/Servo Driver - I2C interface

  Servo & Knob links
  http://www.arduino.cc/en/Tutorial/Knob
  http://people.interaction-ivrea.it/m.rinott
 */

#include "I2C_Array_ESC.h"
#define LED_PIN (13)            // Pin for the LED
#define SPEED_MIN (1000)        // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)        // Set the Maximum Speed in microseconds
#define ARM_VALUE (500)         // Set the Arm value in microseconds
#define FREQ (60)               // Analog servos run at ~60 Hz updates
#define ESC_PIN (0)             // Pin for the ESC on the I2C PWM/Servo extender
#define POT_PIN (A0)            // Analog pin used to connect the potentiometer

I2C_Array_ESC myESC (0x40, SPEED_MIN, SPEED_MAX, ARM_VALUE);  // ESC_Name (PIN, Minimum Value, Maximum Value, Arm Value)

int potVal;                                // variable to read the value from the analog pin

void setup() {
  // start serial port
  Serial.begin(9600);
  Serial.println("Read potentiometer for ESC Control test over I2C PWM/Servo extender");
  //Set up the PWM extenders
  myESC.begin();
  myESC.setPWMFreq(FREQ);  // This is the analog servo PWM frequency, alternativly you could set this using the prescale 60Hz is a prescale of 105

  delay(10); // Set a small delay to allow the PCA9685 chips time to set their frequency

  pinMode(LED_PIN, OUTPUT);             // LED Visual Output
  myESC.arm(ESC_PIN);                          // Send the Arm value
  digitalWrite(LED_PIN, HIGH);          // LED High Once Armed
  delay(5000);                          // Wait for a while
  myESC.speed(ESC_PIN, SPEED_MIN);               // Set to minimum speed now that the ESC should be Armed
}

void loop() {
  potVal = analogRead(POT_PIN);         // reads the value of the potentiometer (value between 0 and 1023)
  potVal = map(potVal, 0, 1023, SPEED_MIN, SPEED_MAX);  // scale it to use it with the ESC (value between Minimum and Maximum)
  myESC.speed(ESC_PIN, potVal);                  // sets the ESC speed according to the scaled value
  delay(15);                            // Wait for a while before starting the loop over
}
