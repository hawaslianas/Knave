#include <DueTimer.h>

const int quad_A = 2;
const int quad_B = 13;
int PWM1 = 3;
const unsigned int mask_quad_A = digitalPinToBitMask(quad_A);
const unsigned int mask_quad_B = digitalPinToBitMask(quad_B);
long Position;
double Kp = 50;
double Velocity, veld = 110, posold = 0, posd = 0, pe = 0, C = 0, ve = 0;
double radian = 0;
bool PWMI = true;

void Handler()
{
  //Save the old position
  posold = radian;
  //Calculate the new position
  Position =  (REG_TC0_CV0 % 10240) - 5120;
  radian = Position * 0.0006135923 ;
  //Calculate the Position error
  pe = posd - Position;
  //Calculate the Speed
  Velocity = (radian - posold) * 1000;
  //Calculate the Speed error
  ve = veld - Velocity;

  C = 0;
  //C = 128 + Kp * ve ;

  //Saturation Block
  if (C > 255) C = 255;
  if (C < 0) C = 0;
  //analogWriteResolution();
  analogWrite(DAC1, C);
}

void PWM_Basic()
{
  PWMI = !PWMI;
  analogWrite(PWM1,PWMI);
}
void PWM_DC()
{
  PWMI = !PWMI;
  analogWrite(PWM1,PWMI);
}
void setup()
{
  Timer3.attachInterrupt(Handler);
  Timer3.start(1000); // Calls every 1ms

  Timer4.attachInterrupt(PWM_Basic);
  Timer4.start(25); // Calls every 25us

  Timer5.attachInterrupt(PWM_DC);
  Timer5.start(12); // Calls every 12us


  Serial.begin(115200);
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
  Serial.print("Speed=");
  Serial.println(Velocity, DEC);
  Serial.print("Error=");
  Serial.println(ve, DEC);
  Serial.print("Command=");
  Serial.println(C);
  Serial.println();
  delay(250);


}
