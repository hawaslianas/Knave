#include <PWM.h>

volatile unsigned int temp, counter  = 0; //This variable will increase or decrease depending on the rotation of encoder
double Position, posd = 50, e = 0;

int PWM = 11;                // the pin that the PWM is attached to
double Duty_Cycle = 50;        // Change duty cycle
int32_t frequency = 40000;    //frequency (in Hz)
double ref = 170;
double DC = 0;

bool LED_STATE1 = true;
bool LED_STATE2 = true;

void setup()
{
  Serial.begin (250000);

  pinMode(2, INPUT_PULLUP); // internal pullup input pin 2

  pinMode(3, INPUT_PULLUP); // internal pullup input pin 3
  //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, ai0, RISING);
  //****************
  InitTimersSafe();
  SetPinFrequencySafe(PWM, frequency);
  DC = ref * Duty_Cycle / 100;
  // ****************
  cli();                      //stop interrupts for till we make the settings
  //Timer2 (interrupt each 1.024ms)
  // interrupt time = 1/(16Mhz/1024) * 16 =  1.024ms.
  TCCR2A = 0;                 // Reset entire TCCR1A to 0
  TCCR2B = 0;                 // Reset entire TCCR1B to 0
  TCCR2B |= B00000111;        //Set CS20, CS21 and CS22 to 1 so we get prescalar 1024
  TIMSK2 |= B00000100;        //Set OCIE1B to 1 so we enable compare match B
  OCR2B = 160;                //Finally we set compare register B to this value
  sei();                      //Enable back the interrupts



}

void loop()
{


}

void ai0()
{
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if (digitalRead(3) == LOW) {
    counter++;
  }
  else {
    counter--;
  }
}

//With the settings above, this IRS will trigger each 1.024ms.
ISR(TIMER2_COMPB_vect)
{
  TCNT2 = 0;
  // Send the value of counter
  Position = (counter % 1024);
  Position = (Position * 360 / 1024) - 180;

  if ( abs(Position - temp) > 0 )
  {
    Serial.println (e);
    temp = e;
  }
  e = posd - Position;

  if ( Serial.available() > 0)
  {
    posd = Serial.read();
  }
  Duty_Cycle = 50 + 0.005 * e * 50;
  DC = ref * Duty_Cycle / 100  + 25.5;
  pwmWrite(PWM, DC);

}
