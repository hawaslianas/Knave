#include <DueTimer.h>

const int quad_A = 2;
const int quad_B = 13;
const unsigned int mask_quad_A = digitalPinToBitMask(quad_A);
const unsigned int mask_quad_B = digitalPinToBitMask(quad_B);
long Position;
double Kp =1.2;
double  posd = 50, e = 0, C=0;

void Handler()
{
  //Save the old position
  //posd =Position;
  //Calculate the new position
  Position =  (REG_TC0_CV0%10240) - 5120;
  //Calculate the error
  e = posd - Position;
  e = e /40;
  C = 128 + Kp * e ;
}

void setup()
{
  Timer3.attachInterrupt(Handler);
  Timer3.start(1000); // Calls every 10ms


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
  Serial.println(Position, DEC);
  //analogWriteResolution();
  analogWrite(DAC1,C);
  
}
