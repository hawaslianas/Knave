#include <PWM.h>


//use pin 11 on the Mega instead, otherwise there is a frequency cap at 31 Hz
int PWM1 = 11;                // the pin that the PWM is attached to
double Duty_Cycle1 = 0;        // Change duty cycle
int32_t frequency1 = 40000;    //frequency (in Hz)
double ref1 = 170;
double DC1 = 0;
void setup()
{
  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe();

  //sets the frequency for the specified pin
  SetPinFrequencySafe(PWM1, frequency1);
  DC1 = ref1 * Duty_Cycle1 / 100;
}

void loop()
{
  
    Duty_Cycle1 = 1+Duty_Cycle1;
    DC1 = ref1 * Duty_Cycle1 / 100  + 25.5;
    pwmWrite(PWM1, DC1);
    delay(1000);
  
}
