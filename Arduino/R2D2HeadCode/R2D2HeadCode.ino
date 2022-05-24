/*  L I B R A R I E S  */
#include <SoftwareSerial.h>
#include <SPI.h>

/*  U S E F U L  L I N K S  */
// MAX7219 Reference: https://www.best-microcontroller-projects.com/max7219.html#Arduino_Sketch_Example_2
// ASCII Table:       https://www.asciitable.com/ 

/*  V A R I A B L E S  */
int incomingByte = 0;     // Stores values sent from python script
int blinkTimer = 300;     // Change how long LEDs blink for
int brightness = 255;     // Dot Matrix Brightness; 255 is maximum
int iterationCounter = 0; // Used in for loops

/*  P I N O U T  */
#define LEDArray  23         // Connects 6 LED array & Single LED in the 'eye'
#define SS_PIN    53         // SPI SS pin of the Dot Matrices
SoftwareSerial hc06(50, 22); // Pins used for the HC06, RX pin is limited to 10, 11, 12, 13, 14, 15, 50, 51, 52, 53.

// MAX7219 SPI Address Codes
#define MAX7219_TEST 0x0f
#define MAX7219_BRIGHTNESS 0x0a
#define MAX7219_SCAN_LIMIT 0x0b
#define MAX7219_DECODE_MODE 0x09
#define MAX7219_SHUTDOWN 0x0C

void maxTransferCMD(uint8_t address, uint8_t value) {
  uint8_t i;
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(SS_PIN, HIGH);
}

void maxTransferDATA(uint8_t address, uint8_t value, uint8_t value2) {
  uint8_t i;
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  SPI.transfer(address);
  SPI.transfer(value2);
  digitalWrite(SS_PIN, HIGH);
}

void blinkMatrix() {
  //Randomly generates LED patterns
  uint8_t row = 0;

  maxTransferCMD(MAX7219_SHUTDOWN, 0x01);    // Turn on chip.

  for (iterationCounter = 0; iterationCounter < blinkTimer; iterationCounter++) {

    if ( row++ > 8 ) {
      row = 1;
    }

    maxTransferDATA(row, random(0, 255), random(0, 255));
    maxTransferCMD(MAX7219_BRIGHTNESS, brightness >> 4);
    delay(10);
  }
  maxTransferCMD(MAX7219_SHUTDOWN, 0x00);    // Turn off chip, prevents lingering LEDs.
}

void blinkLEDArray() {
  for (iterationCounter = 0; iterationCounter < blinkTimer / 15; iterationCounter++) {
    digitalWrite(LEDArray, HIGH);
    delay(50);
    digitalWrite(LEDArray, LOW);
    delay(50);
  }
}

void setup() {
  hc06.begin(9600);

  pinMode(SS_PIN, OUTPUT);
  pinMode(LEDArray, OUTPUT);

  SPI.setBitOrder(MSBFIRST);
  SPI.begin();

  // Bootup Test, flashes all lights
  maxTransferCMD(MAX7219_TEST, 0x01);        delay(500);
  maxTransferCMD(MAX7219_TEST, 0x00);        // Finish test mode.
  maxTransferCMD(MAX7219_DECODE_MODE, 0x00); // Disable BCD mode.
  maxTransferCMD(MAX7219_BRIGHTNESS, 0x00);  // Use lowest intensity.
  maxTransferCMD(MAX7219_SCAN_LIMIT, 0x0f);  // Scan all digits.
  digitalWrite(LEDArray, HIGH);              delay(300);
  digitalWrite(LEDArray, LOW);
}

void loop() {
  incomingByte = 0;
  
  //Writes byte sent to the hc06 to a variable
  if (hc06.available()) {
    incomingByte = hc06.read();
  }

  //Do all the cool flashy stuff here
  switch (incomingByte) {
    case 35: // #
      blinkMatrix();
      break;

    case 36: // $
      blinkLEDArray();
      break;

    case 37: // %
      //Do something cool here! :)
      break;

    default:
      break;
  } 
}
