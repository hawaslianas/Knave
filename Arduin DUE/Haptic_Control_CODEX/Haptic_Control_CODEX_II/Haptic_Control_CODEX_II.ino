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


bool Activate = false, Arm1_caled = false , Arm2_caled = false, DataIN=false;
const int quad_A = 2;
const int quad_B = 13;
const int IR1    = 7;
const int IR2    = 8;
const unsigned int mask_quad_A = digitalPinToBitMask(quad_A);
const unsigned int mask_quad_B = digitalPinToBitMask(quad_B);
long Position1 = 0, Position2 = 0;
double Kp = 150;
double Kd = 50;
double Acc1, w1, wold1 = 110, qold1 = 0, qd1 = 0, qe1 = 0, C1 = 0, Cal1 = 1200;
double Acc2, w2, wold2 = 110, qold2 = 0, qd2 = 0, qe2 = 0, C2 = 0, Cal2 = 1200;
double q1 = 0, q2 = 0;
int Zcommand  = 1000, PC = 0;
double wcalibration = 0.01; // The speed during calibration rad/s
int timescale = 100;
double Tint1, Tint2;
String incomingByte;

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
  //Update the old Position
  qold1 = q1;
  qold2 = q2;

  //Update the old Velocity
  wold1 = w1;
  wold2 = w2;

  //Calculate the new position
  Position1 =  (REG_TC0_CV0 );
  Position2 =   0;

  //Calculate q1 and q2
  q1 = Position1 * 0.00153398; // 3.141592653589793238 / 2048;
  q2 = Position2 * 3.141592653589793238 / 1024;

  //Calculate the Position error
  qe1 = qd1 - q1;
  qe2 = qd2 - q2;

  //Calculate the Velocity
  w1 = (q1 - qold1) * timescale;
  w2 = (q2 - qold2) * timescale;

  //Calculate the Acceleration
  Acc1 = (w1 - wold1) * timescale;
  Acc2 = (w2 - wold2) * timescale;


  //Calculate Sin
  S12 = sin(q1 - q2);
  C12 = cos(q1 - q2);

  // Calculate Torques Intrinsic
  Tint1 = A * Acc1 + B * C12 * Acc2 + Z * S12 * w1 + S12 * (Z - B * (w1 - w2)) * w2;
  Tint2 = B * C12 * Acc1 + G * Acc2 - S12 * (Z + B * (w1 - w2)) * w1 - Z * S12 * w2;
  if (Activate)
  {
    switch (PC)
    {
      case 0:
        break;

      case 1:
        //Update Commands
        C1 = Zcommand + Kp * qe1 - Kd * we1;
        C2 = Zcommand + Kp * qe2 - Kd * we2;
        break;

      case 2:
        //Update Commands
        C1 = Zcommand + Kp * qe1 - Kd * we1;
        C2 = Zcommand + Kp * qe2 - Kd * we2;
        break;

      default:
        //Update Commands
        C1 = Zcommand;
        C2 = ZCommand;
        break;
    }
    /*
      Commands Guide
      0  => 3.5 V
      1100 =>   2 V
      2190 => 0.5 V
    */
    //Saturation
    if (C1 > 2190) C1 = 2190;
    if (C1 < 0)  C1 = 0;
    PWM_DUTY_PIN_35 = C1;
    if (C1 > 2190) C1 = 2190;
    if (C1 < 0)  C1 = 0;
    PWM_DUTY_PIN_35 = C1;
    if (Safety)
    {
      // Please be sure to add a safety condition for the angles before applying the wire

      //Send Commands
      // changing duty in pwm output pin 35
      change_duty(pwm_pin35, PWM_DUTY_PIN_35, PWM_PERIOD_PIN_35);
      // changing duty in pwm output pin 42
      change_duty(pwm_pin42, PWM_DUTY_PIN_42, PWM_PERIOD_PIN_42);
      //Serial.println(w1);
    }
    else
    {
      //Send Commands
      // changing duty in pwm output pin 35
      change_duty(pwm_pin35, Zcommand, PWM_PERIOD_PIN_35);
      // changing duty in pwm output pin 42
      change_duty(pwm_pin42, Zcommand, PWM_PERIOD_PIN_42);
      //Serial.println(w1);
    }
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

bool Safety()
{
  if (q1 > q1max || q1 < q1min || q2 > q2max || q2 < q2min) return false;
  else if ( q1 + q2 == 0) return false;
  else return true;
}

int ChooseProject()
{
  while (1)
  {
    if (Serial.available() > 0)
    {
      // read the incoming byte:
      incomingByte = Serial.readString();
      Serial.println("Data Incoming: ");
      switch (incomingByte)
      {

        case "ST1G":
          Serial.println("Charges Project Requested");
          delay(1000);
          return 1;
          break;

        case "ST2G":
          Serial.println("Rehabitation Project Requested");
          delay(1000);
          return = 1;
          break;

        case "ST0G":
          Serial.println("Termination Requested");
          delay(1000);
          return 0;
          break;
        default:
          Serial.println("Invalid Command Requested!!");
          break;
      }
      Serial.println("Reading Finished Zero was returned");
      delay(1000);
    }
    return 0;
  }
}

void Calibrate()
{
  Activate = false;
  while (1)
  {
    Cal1 = Zcommand - kd * (w1 - wcalibration);
    Cal2 = Zcommand - kd * (w2 - wcalibration);
    if (digitalRead(IR1) == 0 | Arm1_caled) {
      Arm1_caled = true;
    }
    else {
      Serial.println("First Arm isn't Calibrated!");
    }

    if (!digitalRead(IR2) == 0 | Arm2_caled) {
      Arm2_caled = true;
    }
    else {
      Serial.print("Second Arm isn't Calibrated!");
    }
    Commands(Cal1, Cal2);
    if (Arm1_caled & Arm2_caled) {
      break;
    }
  }
  Activate = true;
  Serial.println("Calibration Finished");
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

  Calibrate();
  PC = ChooseProject();

}

void loop()
{
  Serial.println("Log: ");
  Serial.print("Error1 = ");
  Serial.println(qe1, DEC);
  Serial.print("Position1 = ");
  Serial.println(q1, DEC);
  Serial.print("Command1 = ");
  Serial.println(C1, DEC);
  Serial.print("Activation status: ");
  Serial.println(Activate);
  Serial.println();
  //Serial.println("Command = ");
  //Serial.print(Cal2);
  delay(250);
}
