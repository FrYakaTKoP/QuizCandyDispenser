/* https://github.com/FrYakaTKoP/QuizCandyDispenser

	QuizCandy-Hwtest
	
	Tests the hardware of the QuizCandyDispenser
	
	look at the Readme.md in the repo for connection diagramm

*/
#include <Servo.h>
#include "U8glib.h"


#define EJECT_POS 0 // Eject postion (where the candy drops to the output compartment)
#define LOAD_POS  180 // Loading postion (where the new candy gets taken from magazin)
#define SERVO_MS_MIN 544 // the pulse width, in microseconds, corresponding to the minimum (0-degree) angle on the servo (defaults to 544) 
#define SERVO_MS_MAX 2400 // the pulse width, in microseconds, corresponding to the maximum (180-degree) angle on the servo (defaults to 2400) 

#define PIN_SERVO 11 // on RAMPS 1.4 -> SER1=11, SER2=6, SER3=5, SER4=4

#define PIN_BTN_A 14
#define PIN_BTN_B 15
#define PIN_BTN_C 18
#define PIN_BTN_D 19

#define PIN_LCD_MOSI	23
#define PIN_LCD_CLK		17
#define PIN_LCD_CS 		16
#define PIN_BEEPER 	37
#define PIN_ENCBTN 	35
#define PIN_ENC1 	33
#define PIN_ENC2 	31
#define PIN_RSTBTN 	41

#define PIN_SD_DET 	49




U8GLIB_ST7920_128X64_1X u8g(LCD_PIN_MOSI, LCD_PIN_CLK, LCD_PIN_CS);  // SPI Com: SCK = en, MOSI = rw, CS = di
Servo servo;  // create servo object to control a servo
int curPos = 0;   // variable to store the servo position




void setup() {
  servo.attach(PIN_SERVO, SERVO_MS_MIN, SERVO_MS_MAX);  // attaches the servo on pin 9 to the servo object
  
  pinMode(PIN_BEEPER, OUTPUT); // Set buzzer - pin 9 as an output
}

void loop() {
  for (curPos = 0; curPos <= 180; curPos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(curPos);              // tell servo to go to position in variable 'curPos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (curPos = 180; curPos >= 0; curPos -= 1) { // goes from 180 degrees to 0 degrees
    servo.write(curPos);              // tell servo to go to position in variable 'curPos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
