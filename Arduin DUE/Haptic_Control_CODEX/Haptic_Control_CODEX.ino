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
int PWM_DUTY_PIN_35 = 1100; // 100 msecs in hundredth of usecs (1e-8 secs)

#define PWM_PERIOD_PIN_42 2500 // 100 usecs in hundredth of usecs (1e-8 secs)
int PWM_DUTY_PIN_42 = 1100 ;// 10 usec in hundredth of usecs (1e-8 secs)

// defining pwm object using pin 35, pin PC3 mapped to pin 35 on the DUE
// this object uses PWM channel 0
pwm<pwm_pin::PWMH0_PC3> pwm_pin35;

// defining pwm objetc using pin 42, pin PA19 mapped to pin 42 on the DUE
// this object used PWM channel 1
pwm<pwm_pin::PWMH1_PA19> pwm_pin42;

//Define System Criteria
double  Lc1 = 0.02126, Lc2 = 0.02921, Lc3 = 0.11, Lc4 = 0.11, L = 0.22;
double   m1 = 0.256,    m2 = 0.294,    m3 = 0.066, m4 = 0.086;
double   I1 = 0.001017212, I2 = 0.001987462, I3 = 0.00212, I4 = 0.005772;
//Define The Constants for the Torque equations
double A = I1 + I3 + m1 * Lc1 * Lc1 + m3 * Lc3 * Lc3 + m4 * L * L,
       B = L * (0.5 * m3 * Lc3 + m4*Lc4),
       G = I2 + I4 + m2 * Lc2 * Lc2 + 0.25 * m3 * L * L + m4 * Lc4 * Lc4,
       Z = 0.25 * L * (m3 * Lc3 + 2 * m4*Lc4);
double S12 = 0, C12 = 0;
double X=0,Y=0;


bool Activate = false;
const int quad_A = 2;
const int quad_B = 13;
const int IR1    = 7;
const int IR2    = 8;
const unsigned int mask_quad_A = digitalPinToBitMask(quad_A);
const unsigned int mask_quad_B = digitalPinToBitMask(quad_B);
long Position1 = 0, Position2 = 0;
double Kp = 500;
double Kd = 200;
double Acc1, w1, wold1 = 110, qold1 = 0, qd1 = 0, qe1 = 0, C1 = 0, Cal1 = 1200;
double Acc2, w2, wold2 = 110, qold2 = 0, qd2 = 0, qe2 = 0, C2 = 0, Cal2 = 1200;
double q1 = 0, q2 = 0;
int Zcommand  = 1100;
int timescale = 100;
double Tint1, Tint2;

void ai1()
{
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if (digitalRead(5) == LOW) {
    Position2++;
  }
  else {
    Position2--;
  }
}

void Calculate()
{
  Activate = 1;
  if (Activate)
  {
    //Update the old Position
    qold1 = q1;
    qold2 = q2;

    //Update the old Velocity
    wold1 = w1;
    wold2 = w2;

    //Calculate the new position
    Position1 =  (REG_TC0_CV0);


    //Calculate q1 and q2
    q1 = Position1 / 21408.9; // 3.141592653589793238 / 2048;
    q2 = Position2 / 4052.65; // pi/3 * 3870;

    //Calculate the Position error
    qe1 = qd1 - q1;
    qe2 = qd2 - q2;

    //Calculate the Velocity
    w1 = (q1 - qold1) * timescale;
    w2 = (q2 - qold2) * timescale;

    //Apply digital filter to the velocity
    w1 = (wold1 + w1) / 2;
    w2 = (wold2 + w2) / 2;

    //Calculate the Acceleration
    Acc1 = (w1 - wold1) * timescale;
    Acc2 = (w2 - wold2) * timescale;


    //Calculate Sin
    S12 = sin(q1 - q2);
    C12 = cos(q1 - q2);
    /*
      Commands Guide
      0  => 3.5 V
      1100 =>   2 V
      2190 => 0.5 V
    */

    // Calculate Torques Intrinsic
    Tint1 = A * Acc1 + B * C12 * Acc2 + Z * S12 * w1 + S12 * (Z - B * (w1 - w2)) * w2;
    Tint2 = B * C12 * Acc1 + G * Acc2 - S12 * (Z + B * (w1 - w2)) * w1 - Z * S12 * w2;


    //Calculate Position (X,Y);
    X = L * cos(q1) + L * sin(q2);
    Y = L * sin(q1) + L * sin(q2);

    //Update Commands
    /*if(q1>0.2)
      {
      C1 = Zcommand  -Kd* w1 +Kp * qe1 ;
      }
      else
      {
      C1 = Zcommand  -Kd* w1 ;
      }*/
    //C1 = Zcommand  -Kd* w1 +Kp * qe1 ;
    if (q1 < -2)
    {
      C1 = Zcommand + Kp * qe1 - Kd * w1;
      C2 = Zcommand + Kp * qe2;
    }
    else
    {
      C1 = Zcommand - Kd * w1;
      C2 = Zcommand + Kp * qe2;
    }

    //Saturation
    if (C1 > 2190) C1 = 2190;
    if (C1 < 0)  C1 = 0;
    PWM_DUTY_PIN_35 = C1;
    if (C1 > 2190) C1 = 2190;
    if (C1 < 0)  C1 = 0;
    PWM_DUTY_PIN_35 = C1;
    // Please be sure to add a safety condition for the angles before applying the wire
    //Send Commands
    // changing duty in pwm output pin 35
    change_duty(pwm_pin35, PWM_DUTY_PIN_35, PWM_PERIOD_PIN_35);
    // changing duty in pwm output pin 42
    change_duty(pwm_pin42, PWM_DUTY_PIN_42, PWM_PERIOD_PIN_42);
    //Serial.println(w1);
  }
  else Serial.println("Waiting...");
}
void Commands(int Ca1, int Ca2)
{
  //Send Commands
  // changing duty in pwm output pin 35
  change_duty(pwm_pin35, Ca1, PWM_PERIOD_PIN_35);
  // changing duty in pwm output pin 42
  change_duty(pwm_pin42, Ca2, PWM_PERIOD_PIN_42);
}
void Calibration()
{
  Activate = false;
  while (1)
  {
    Serial.println("First Arm isn't Calibrated");
    if (digitalRead(IR1) == 0) {
      Cal1 = 1050;
    }
    else {
      Serial.println("First Arm isn't Calibrated");
    }

    if (!digitalRead(IR2) == 0) {
      Cal2 = 1050;
    }
    else {
      Serial.print("Second Arm isn't Calibrated");
    }
    Commands(Cal1, Cal2);
    if (Cal1 == 1050 and Cal2 == 1050) {
      break;
    }
  }
  // 120 degrees equal 3413.33
  Activate = true;
  //Cal1 = 1500;
  //Cal2 = 1500;
  Serial.println("All is good");
}

void setup()
{
  Serial.begin(115200);
  //Define Sensor pins
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  //Attach 2nd encoder decoder
  attachInterrupt(digitalPinToInterrupt(6), ai1, RISING);

  // starting PWM signals
  pwm_pin35.start(PWM_PERIOD_PIN_35, PWM_DUTY_PIN_35);
  pwm_pin42.start(PWM_PERIOD_PIN_42, PWM_DUTY_PIN_42);

  //Calibration();
  //Start Calculation Interrupt
  Timer3.attachInterrupt(Calculate);
  Timer3.start(100000 / timescale ); // Calls every 10ms
  delay(100);

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



  Serial.println("Log: ");
  Serial.print((String) "   Error 1 = " + qe1 + "   Position 1 = " + Position1);
  Serial.print((String)"   Error 2 = " + qe2 + "   Position 2 = " + q2);
  Serial.print((String)"   Command 1 = " + C1 + "   Command 2 = " + C2);
  Serial.print("   Activation status: ");
  Serial.println(Activate);
  Serial.println();

  Serial.println((String)"  X = " +X);
  Serial.println((String)"  Y = " +Y);
  //Serial.println("Command = ");
  //Serial.print(Cal2);

  delay(250);
}
