/*
  ESC_Stop
    This is to illustrate the "stop" command that can be use. It will send a 500us value which in most cases will stop the motor.
    If another value is needed, it can be changed in the library ESC.h under "ESC_STOP_PULSE" 

    Based on the 27 April 2017 Sketch by Eric Nantel and his RC_ESC library for Robot shop
    rewritten for use in the I2C_Array_ESC library with the Adafruit PCA9685 16-Channel 12-bit PWM/Servo Driver - I2C interface
**/
#include "I2C_Array_ESC.h"
#define LED_PIN (13)            // Pin for the LED
#define SPEED_MIN (1000)        // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)        // Set the Maximum Speed in microseconds
#define ARM_VALUE (500)         // Set the Arm value in microseconds
#define SERVO_FREQ (50)         // Analog servos run at ~50 Hz updates
#define ESC_PIN (0)             // Pin for the ESC on the I2C PWM/Servo extender

I2C_Array_ESC myESC (0x40, SPEED_MIN, SPEED_MAX, ARM_VALUE);       // ESC_Name (I2C_address, ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)

void setup() {
  // start serial port
  Serial.begin(9600);
  Serial.println("I2C Controller Test with ESC");

  /*
   * Set up the I2C based PWM/Servo extenders
   * This is only done once per Adafruit PCA9685 PWM/Servo driver
   */
  myESC.begin();

  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't that precise. 
   * You can 'calibrate' by tweaking this number till you get the frequency you're expecting!
   * The int.osc. is closer to 27MHz and is used for calculating things like writeMicroseconds
   * This is only done once per Adafruit PCA9685 PWM/Servo driver
   */
  myESC.setOscillatorFrequency(26075000);

 /*
  * Set the analog servo PWM frequency
  * alternativly you could set this using the prescale 50Hz is a prescale of about ### (depending on the internal oscillator frequency)
  * This is only done once per Adafruit PCA9685 PWM/Servo driver
  */
  myESC.setPWMFreq(SERVO_FREQ);

  delay(10); // Set a small delay to allow the PCA9685 chips time to set their frequency

  pinMode(LED_PIN, OUTPUT);        // LED Visual Output
  myESC.arm(ESC_PIN);              // Send the Arm value so the ESC will be ready to take commands
  digitalWrite(LED_PIN, HIGH);     // LED High Once Armed
  delay(5000);                     // Wait for a while
  myESC.speed(ESC_PIN, SPEED_MIN); // Set ESC to minimum speed now that the ESC should be Armed
}

void loop() {
  myESC.speed(ESC_PIN, 1200);      // Set the speed to a testing value between SPEED_MIN (1000) and SPEED_MAX (2000)
  delay(500);                      // Wait for a while 
  myESC.stop(ESC_PIN);             // Stop the ESC altogether
  delay(5000);                     // Wait for a while until we restart the loop
}

