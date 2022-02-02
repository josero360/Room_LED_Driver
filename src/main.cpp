#include <Arduino.h>

// Board: Arduino Uno R3 (ATmega328p)
#define PIN_PWM_WW 6
#define PIN_PWM_CW 5
#define PIN_POTI_WW A0 
#define PIN_POTI_CW A1  
#define GAMMA_WW_VALUE 1.5
#define GAMMA_CW_VAlUE 1.5
#define GAMMA_WW_OFFSET 35.0
#define GAMMA_CW_OFFSET 35.0

int A_ww = 0;
int A_cw = 0;
int old_A_ww = 0;
int old_A_cw = 0;

/*! @brief
 *  @param newAnalog new/current 8-bit int value
 *  @param oldAnalog old 8-bit int value
 *  @param outputPIN PWM output pin to drive LED
 *  @param valueGAMMA Value for gamma correction (typical for LED applications 1.5-3)
 *  @param offsetLEDthreshold Offset value on with the LED will turn on
*/
void setLEDoutput(int newAnalog, int oldAnalog, uint8_t outputPIN, float valueGAMMA, float offsetLEDthreshold)
{
  if ((newAnalog - oldAnalog) > 4 || (newAnalog - oldAnalog) < -4)
  {
    if (newAnalog < 4){
      analogWrite(outputPIN, 0);
    }
    else{
      analogWrite(outputPIN, (int)( (pow((float)newAnalog/255.0, valueGAMMA)*(255.0 - offsetLEDthreshold)) +offsetLEDthreshold)); 
    }
    oldAnalog = newAnalog;
  }
}

void setup() 
{
  /* Change Prescaler of Timer0 Clock to x256
   * PIN D5 and D6 now on 244Hz
  */  
  TCCR0B = (TCCR0B & B11111000) | B00000100;       //TCCR0B & B11111000| B00000011;
  pinMode(PIN_PWM_WW, OUTPUT);
  pinMode(PIN_PWM_CW, OUTPUT);
}

void loop() {
  A_ww = (analogRead(PIN_POTI_WW)/4);
  A_cw = (analogRead(PIN_POTI_CW)/4);
  setLEDoutput(A_ww, old_A_ww, PIN_PWM_WW, GAMMA_WW_VALUE, GAMMA_WW_OFFSET);
  setLEDoutput(A_cw, old_A_cw, PIN_PWM_CW, GAMMA_CW_VAlUE, GAMMA_CW_OFFSET);
  delay(25);   // by x4
}