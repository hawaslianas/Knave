#include <DueTimer.h>
#include "pwm_lib.h"
#include "tc_lib.h"

using namespace arduino_due::pwm_lib;


#define change_duty_definition \
  template<typename pwm_type> void change_duty( \
      pwm_type& pwm_obj, \
      uint32_t pwm_duty, \
      uint32_t pwm_period \
                                              ) \
  { \
    uint32_t duty=pwm_duty; \
    if(duty>pwm_period) duty=pwm_duty; \
    pwm_obj.set_duty(duty); \
  }
change_duty_definition;


#define PWM_PERIOD_PIN_35 2500 // hundredth of usecs (1e-8 secs)
int PWM_DUTY_PIN_35 = 1250; // 100 msecs in hundredth of usecs (1e-8 secs)

#define PWM_PERIOD_PIN_42 2500 // 100 usecs in hundredth of usecs (1e-8 secs)
int PWM_DUTY_PIN_42 = 500 ;// 10 usec in hundredth of usecs (1e-8 secs)

#define CAPTURE_TIME_WINDOW 15000000 // usecs
#define DUTY_KEEPING_TIME 30000 // msecs 

// defining pwm object using pin 35, pin PC3 mapped to pin 35 on the DUE
// this object uses PWM channel 0
pwm<pwm_pin::PWMH0_PC3> pwm_pin35;

// defining pwm objetc using pin 42, pin PA19 mapped to pin 42 on the DUE
// this object used PWM channel 1
pwm<pwm_pin::PWMH1_PA19> pwm_pin42;


const int quad_A = 2;
const int quad_B = 13;
const unsigned int mask_quad_A = digitalPinToBitMask(quad_A);
const unsigned int mask_quad_B = digitalPinToBitMask(quad_B);
long Position;
double Kp = 1.2, I = 0;
double  posd = 0, e = 0, C = 0;

void Handler()
{
  //Save the old position
  //posd =Position;
  //Calculate the new position
  Position =  (REG_TC0_CV0 % 10240) - 5120;
  //Calculate the error
  e = posd - Position;
  e = e / 5;

  // 125  => 3.5 V
  // 1100 =>   2 V
  // 2190 => 0.5 V
  C = 1100 + Kp * e ;
  if (C > 2190) C = 2190;
  if (C < 125)  C = 125;
  //PWM_DUTY_PIN_35 = C;

  // changing duty in pwm output pin 35
  //change_duty(pwm_pin35, PWM_DUTY_PIN_35, PWM_PERIOD_PIN_35);

  // changing duty in pwm output pin 42
  //change_duty(pwm_pin42, PWM_DUTY_PIN_42, PWM_PERIOD_PIN_42);
}

void setup()
{
  Timer3.attachInterrupt(Handler);
  Timer3.start(1000); // Calls every 10ms


  Serial.begin(115200);
  delay(100);


  // starting PWM signals
  pwm_pin35.start(PWM_PERIOD_PIN_35, PWM_DUTY_PIN_35);
  pwm_pin42.start(PWM_PERIOD_PIN_42, PWM_DUTY_PIN_42);

  // activate peripheral functions for quad pins
  REG_PIOB_PDR = mask_quad_A;     // activate peripheral function (disables all PIO functionality)
  REG_PIOB_ABSR |= mask_quad_A;   // choose peripheral option B
  REG_PIOB_PDR = mask_quad_B;     // activate peripheral function (disables all PIO functionality)
  REG_PIOB_ABSR |= mask_quad_B;   // choose peripheral option B

  // activate clock for TC0
  REG_PMC_PCER0 = (1 << 27);
  // select XC0 as clock source and set capture mode
  REG_TC0_CMR0 = 5;
  // activate quadrature encoder and position measure mode, no filters
  REG_TC0_BMR = (1 << 9) | (1 << 8) | (1 << 12);
  // enable the clock (CLKEN=1) and reset the counter (SWTRG=1)
  // SWTRG = 1 necessary to start the clock!!
  REG_TC0_CCR0 = 5;
}
void loop()
{

  // changing duty in pwm output pin 35
  I = 0.5;
  PWM_DUTY_PIN_35 = 1500;
  //PWM_DUTY_PIN_35 = (2.77226-1.7721*I)/0.0014;
  change_duty(pwm_pin35, PWM_DUTY_PIN_35, PWM_PERIOD_PIN_35);
  Serial.print("Error = ");
  Serial.println(e, DEC);
  Serial.print("Position = ");
  Serial.println(Position,DEC);
  Serial.print("Command = ");
  Serial.println(C,DEC);  
  Serial.println();
  delay(100);
}
