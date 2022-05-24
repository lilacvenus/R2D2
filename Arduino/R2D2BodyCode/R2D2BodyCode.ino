
/*  L I B R A R I E S  */
#include <SoftwareSerial.h>
#include <SabertoothSimplified.h>

/*  U S E F U L  L I N K S  */
// SabertoothSimplified: https://www.dimensionengineering.com/software/SabertoothSimplifiedArduinoLibrary/html/files.html
// Documentation:        http://www.robot-electronics.co.uk/htm/md49tech.htm
// Wiring Example:       https://www.robot-electronics.co.uk/htm/arduino_examples.htm#MD49%2024v%20Motor%20Driver
// ASCII Table:          https://www.asciitable.com/

/*  B Y T E  C O M M A N D S  */
const byte disableTimeout[2]   = {0x00, 0x38}     ; // Prevents auto-timeout after 2 seconds of no commands
const byte setMode2[3]         = {0x00, 0x34, 2}  ; // Move motors together
const byte setMode0[3]         = {0x00, 0x34, 0}  ; // Move motors independantly
const byte setAcceleration[3]  = {0x00, 0x33, 2}  ; // Sets acceleration/deceleration rate
const byte forwardSlow1[3]     = {0x00, 0x31, 80} ; // 1st Motor
const byte forwardFast1[3]     = {0x00, 0x31, 10} ; //
const byte backwardSlow1[3]    = {0x00, 0x31, 183}; //
const byte backwardFast1[3]    = {0x00, 0x31, 245}; //
const byte forwardSlow2[3]     = {0x00, 0x32, 80} ; // 2nd Motor
const byte forwardFast2[3]     = {0x00, 0x32, 10} ; //
const byte backwardSlow2[3]    = {0x00, 0x32, 183}; // 
const byte backwardFast2[3]    = {0x00, 0x32, 245}; //
const byte stopMotor1[3]       = {0x00, 0x31, 128}; // Stop Motors
const byte stopMotor2[3]       = {0x00, 0x32, 128}; //

/*  V A R I A B L E S  */
int incomingByte;                       //Used to read controller input
SoftwareSerial SWSerial(NOT_A_PIN, 11); // RX on no pin (unused), TX on pin 11 (to S1).
SabertoothSimplified ST(SWSerial);      // Use SWSerial as the serial port.

void setup() {
  Serial.begin(9600);    // Send commands to wheel motor controller      Pins: TX(1)   RX(0)
  SWSerial.begin(9600);  // Send commands to head  motor controller       Pins: TX(11)  RX(N/A)

  //Initial MD49 State
  Serial.write(disableTimeout,  2);
  Serial.write(setMode2,        3);
  Serial.write(setAcceleration, 3);

}

void loop() {
  if (Serial.available() > 0) { 
    incomingByte = Serial.read();
  }

    switch(incomingByte) {
      case 119: //w
        Serial.write(forwardSlow1,    3);
        break;

      case 97: //a
        Serial.write(setMode0,        3);
        Serial.write(backwardSlow2,   3);
        Serial.write(forwardSlow1,    3);
        break;

      case 115: //s
        Serial.write(backwardSlow1,   3);
        break;

      case 100: //d
         Serial.write(setMode0,       3); 
         Serial.write(backwardSlow1,  3);
         Serial.write(forwardSlow2,   3);
         break;

      case 54: //Right || 6
         ST.motor(1, 127);
         break;  
        
      case 55: //Left || 7
         ST.motor(1, -127);
         break; 

      case 56: //Stop Head || 8
         ST.motor(1, 0);
         break;

      case 121: //Stop motor on W or S lift || y
         Serial.write(stopMotor1,     3);
         break;

      case 122: //Stop motor on A or D lift || z
         Serial.write(stopMotor1,     3);
         Serial.write(stopMotor2,     3);
         Serial.write(setMode2,       3);
    }
}
