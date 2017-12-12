

/* https://github.com/FrYakaTKoP/QuizCandyDispenser

	QuizCandy-Hwtest

	Tests the hardware of the QuizCandyDispenser

	look at the Readme.md in the repo for connection diagramm


*/

#include <Servo.h>
#include "U8glib.h"

#define EJECT_POS 0 // Eject postion (where the candy drops to the output compartment)
#define EJECT_DELAY 400 // time in ms where the servo waits in Eject postion 
#define LOAD_POS  180 // Loading postion (where the new candy gets taken from magazin)
#define LOAD_DELAY 600 // time in ms where the servo waits in Eject postion 
#define SERVO_SPEED 10 // delay in servo sweep ms
#define SERVO_MS_MIN 544 // the pulse width, in microseconds, corresponding to the minimum (0-degree) angle on the servo (defaults to 544) 
#define SERVO_MS_MAX 2400 // the pulse width, in microseconds, corresponding to the maximum (180-degree) angle on the servo (defaults to 2400) 
#define REST_POS 90 // rest postion, don't edit

#define SILENT_SERVO


#define PIN_SERVO 11 // on RAMPS 1.4 -> SER1=11, SER2=6, SER3=5, SER4=4

// Button Pins connected to RAMPS 1.4 endstops (X-min=3,X-max=2,Y-min=14 (non interrupt), Y-max=15 (non interrupt), Z-min= 18, Z-max=19)
#define PIN_BTN_A     3 // Z-min endstop
#define PIN_BTN_B     2 // Z-max endstop
#define PIN_BTN_C     14 // Y-min endstop
#define PIN_BTN_D     15 // Y-max endstop

#define PIN_LCD_MOSI  23 // MOSI, SID, LCD_PINS_ENABLE
#define PIN_LCD_CLK   17 // CLK, PINS_D4 
#define PIN_LCD_CS    16 // CS, LCD_PINS_RS
#define PIN_BEEPER    37
#define PIN_ENCBTN    35
#define PIN_ENC1      33
#define PIN_ENC2      31
#define PIN_RSTBTN    41

#define PIN_SD_DET    49
#define PIN_SD_CS     53


//VarSpeedServo servo;  // create servo object to control a servo
Servo servo;  // use factory servo lib
int curPos = REST_POS;   // variable to store the servo position

U8GLIB_ST7920_128X64_1X u8g(PIN_LCD_MOSI, PIN_LCD_CLK, PIN_LCD_CS);  // SPI Com: SCK = en, MOSI = rw, CS = di

void draw(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
  u8g.drawStr( 2, 0, "drawRFrame/Box");
  u8g.drawRFrame(5, 10, 40, 30, 2);
  u8g.drawRBox(50, 10, 25, 40, 2);
}

void setup() {
  servo.attach(PIN_SERVO, SERVO_MS_MIN, SERVO_MS_MAX);
  servo.write(REST_POS);

  pinMode(PIN_BEEPER, OUTPUT);

  pinMode(PIN_ENCBTN, INPUT_PULLUP);
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);
  pinMode(PIN_BTN_C, INPUT_PULLUP);
  pinMode(PIN_BTN_D, INPUT_PULLUP);

  delay(200);
#if defined(SILENT_SERVO)
  servo.detach();
#endif
}

void servoSweep(int newPos)
{
  while (curPos != newPos)
  {
    if (curPos > newPos)
    {
      curPos--;
    }
    else
    {
      curPos++;
    }
    servo.write(curPos);
    delay(SERVO_SPEED);
  }
}

void moveServo()
{
#if defined(SILENT_SERVO)
  servo.attach(PIN_SERVO, SERVO_MS_MIN, SERVO_MS_MAX);
#endif
  servoSweep(LOAD_POS);
  delay(LOAD_DELAY);
  servoSweep(EJECT_POS);
  delay(EJECT_DELAY);
  servoSweep(REST_POS);
#if defined(SILENT_SERVO)
  servo.detach();
#endif
}

void beep()
{
  tone(PIN_BEEPER, 800);
  delay(100);
  noTone(PIN_BEEPER);
  delay(100);
  tone(PIN_BEEPER, 800);
  delay(100);
  noTone(PIN_BEEPER);
  delay(200);
  tone(PIN_BEEPER, 1200);
  delay(150);
  noTone(PIN_BEEPER);
}

void loop() {
  bool feed = false;
  if (digitalRead(PIN_ENCBTN) == LOW)
  {
    feed = true;
  }
  if (digitalRead(PIN_BTN_A) == LOW)
  {
    feed = true;
  }
  if (digitalRead(PIN_BTN_B) == LOW)
  {
    feed = true;
  }
  if (digitalRead(PIN_BTN_C) == LOW)
  {
    feed = true;
  }
  if (digitalRead(PIN_BTN_D) == LOW)
  {
    feed = true;
  }
  if (feed)
  {
    moveServo();
    beep();
  }

  // picture loop
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
}
