#include <Arduino.h>

#define PIN_PWM_WW 6
#define PIN_PWM_CW 5
#define PIN_POTI_WW A0 
#define PIN_POTI_CW A1  

int A_ww = 0;
int A_cw = 0;
int old_A_ww = 0;
int old_A_cw = 0;

void setup() 
{
  TCCR0B = TCCR0B & B11111000 | B00000100;       //TCCR0B & B11111000| B00000011;
  pinMode(PIN_PWM_WW, OUTPUT);
  pinMode(PIN_PWM_CW, OUTPUT);
}

void loop() {
  A_ww = (analogRead(PIN_POTI_WW)/4);
  A_cw = (analogRead(PIN_POTI_CW)/4);
  if ((A_ww - old_A_ww) > 4 || (A_ww - old_A_ww) < -4)
  {
    if (A_ww < 4){
      analogWrite(PIN_PWM_WW, 0);
    }
    else{
      analogWrite(PIN_PWM_WW, (int)( (pow((float)A_ww/255.0, 1.5)*230.0) +25.0 )); 
    }
    old_A_ww = A_ww;
  }
  if ((A_cw - old_A_cw) > 4 || (A_cw - old_A_cw) < -4)
  {
    if (A_cw < 4){
      analogWrite(PIN_PWM_CW, 0);
    }
    else{
      analogWrite(PIN_PWM_CW, (int)( (pow((float)A_cw/255.0, 1.5)*230.0) +25.0 ));
    }
    old_A_cw = A_cw;
  }
  delay(25);
}