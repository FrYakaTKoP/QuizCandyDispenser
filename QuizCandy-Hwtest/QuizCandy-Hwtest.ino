

/* https://github.com/FrYakaTKoP/QuizCandyDispenser

	QuizCandy-Hwtest

	Tests the hardware of the QuizCandyDispenser

	look at the Readme.md in the repo for connection diagramm


*/

#include <Servo.h>
#include "U8glib.h"
#include "pitches.h"


#define EJECT_POS 0 // Eject postion (where the candy drops to the output compartment)
#define EJECT_DELAY 400 // time in ms where the servo waits in Eject postion 
#define LOAD_POS  180 // Loading postion (where the new candy gets taken from magazin)
#define LOAD_DELAY 600 // time in ms where the servo waits in Eject postion 
#define SERVO_SPEED 10 // delay in servo sweep ms
#define SERVO_MS_MIN 544 // the pulse width, in microseconds, corresponding to the minimum (0-degree) angle on the servo (defaults to 544) 
#define SERVO_MS_MAX 2400 // the pulse width, in microseconds, corresponding to the maximum (180-degree) angle on the servo (defaults to 2400) 
#define REST_POS 90 // rest postion, don't edit

#define SILENT_SERVO

// Answer was correct melody:
int melodyCorrect[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,  0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int melodyCorrectDurations[] = {
  12, 12, 12, 12,
  12, 12, 128,  128
};

// Answer was wrong melody:
int melodyWrong[] = {
  NOTE_G3, 0, NOTE_G3, 0,
  0, 0, 0,  0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int melodyWrongDurations[] = {
  2, 16, 4, 128,
  128, 128, 128, 128
};

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
  u8g.drawStr( 2, 0, "Quiz Candy Dispenser");
  u8g.drawStr( 2, 10, "Hw Test Sketch");

  u8g.drawRFrame(1, 41, 9, 11, 2);
  u8g.drawStr( 3, 42, "A");
  u8g.drawRFrame(65, 41, 9, 11, 2);
  u8g.drawStr( 67, 42, "B");
  u8g.drawRFrame(1, 53, 9, 11, 2);
  u8g.drawStr( 3, 54, "C");
  u8g.drawRFrame(65, 53, 9, 11, 2);
  u8g.drawStr( 67, 54, "D");

  
  u8g.setFont(u8g_font_5x8);
  u8g.setFontPosTop();
  u8g.drawStr( 11, 43, "Antwort A");
  u8g.drawStr( 75, 43, "Antwort B");
  u8g.drawStr( 11, 55, "Antwort C");
  u8g.drawStr( 75, 55, "Antwort D");
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
  pinMode(PIN_RSTBTN, INPUT_PULLUP);

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

void beep(int melody[], int durations[])
{
  int melodyLength = sizeof(melody) / sizeof(int);
  // TODO: Variable melody length not working using fixed for now
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / durations[thisNote];
    tone(PIN_BEEPER, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(PIN_BEEPER);
  }
}

void loop() {
  bool newInput = false;
  bool win = true;
  if (digitalRead(PIN_ENCBTN) == LOW)
  {
    newInput = true;
  }
  if (digitalRead(PIN_BTN_A) == LOW)
  {
    newInput = true;
  }
  if (digitalRead(PIN_BTN_B) == LOW)
  {
    newInput = true;
  }
  if (digitalRead(PIN_BTN_C) == LOW)
  {
    newInput = true;
  }
  if (digitalRead(PIN_BTN_D) == LOW)
  {
    newInput = true;
  }
  if (digitalRead(PIN_RSTBTN) == LOW)
  {
    newInput = true;
    win = false;
  }
  if(newInput)
  {
    if(win)
    {    
      beep(melodyCorrect, melodyCorrectDurations);
      moveServo(); 
    }
    else
    {
      beep(melodyWrong, melodyWrongDurations);
    }
  }

  // picture loop
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
}
