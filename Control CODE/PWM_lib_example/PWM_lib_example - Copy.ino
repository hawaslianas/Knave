#include <PWM.h>

//use pin 11 on the Mega instead, otherwise there is a frequency cap at 31 Hz
int PWM = 11;                // the pin that the PWM is attached to
double Duty_Cycle =50;         // Change duty cycle
int32_t frequency = 400000;    //frequency (in Hz)
double ref = 170;
double DC =0;
void setup()
 {
   //initialize all timers except for 0, to save time keeping functions
     InitTimersSafe(); 

   //sets the frequency for the specified pin
     SetPinFrequencySafe(PWM, frequency);
     DC = ref * Duty_Cycle /100;
  }

void loop()
{
  
  DC = ref * Duty_Cycle /100  +25.5;
  pwmWrite(PWM,DC);
//  delay(200);
//  Duty_Cycle = 100;
//  DC = ref * Duty_Cycle /100  +25.5;
//  pwmWrite(PWM,DC);
//  delay(200);

  
 
}
