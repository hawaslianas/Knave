/*
  Haptic_Control_CODEX.ino
  -----------------------
  Firmware for KNAVE 2-DOF Five Bar Haptic Device (Arduino Due, SAM3X8E)

  Responsibilities:
    - Read rotary encoders for joint positions
    - Compute kinematics and dynamics
    - Implement real-time control (impedance, torque, PID)
    - Generate PWM for motor drivers
    - Communicate with the PC GUI via serial

  Author: [Your Name]
  Last Cleaned: July 2025
*/

#include <DueTimer.h>
#include "pwm_lib.h"
#include "tc_lib.h"

using namespace arduino_due::pwm_lib;

// -------------------- PWM Setup --------------------
#define PWM_PERIOD_PIN_35 2500 // hundredth of usecs (1e-8 secs)
int PWM_DUTY_PIN_35 = 1250; // 100 msecs in hundredth of usecs (1e-8 secs)

#define PWM_PERIOD_PIN_42 2500 // 100 usecs in hundredth of usecs (1e-8 secs)
int PWM_DUTY_PIN_42 = 500 ;// 10 usec in hundredth of usecs (1e-8 secs)

pwm<pwm_pin::PWMH0_PC3> pwm_pin35; // PWM channel 0, pin 35
pwm<pwm_pin::PWMH1_PA19> pwm_pin42; // PWM channel 1, pin 42

// -------------------- System Parameters --------------------
double  Lc1 = 0.02126, Lc2 = 0.02921, Lc3 = 0.11, Lc4 = 0.11, L = 0.22;
double  m1 = 0.256, m2 = 0.294, m3 = 0.066, m4 = 0.086;
double  I1 = 0.001017212, I2 = 0.001987462, I3 = 0.00212, I4 = 0.005772;
double  A = I1 + I3 + m1 * pow(Lc1,2) + m3 * pow(Lc3,2) + m4 * pow(L,2);
double  B = L * (0.5 * m3 * Lc3 + m4*Lc4);
double  G = I2 + I4 + m2 * pow(Lc2,2) + 0.25 * m3 * pow(L,2) + m4 * pow(Lc4,2);
double  Z = 0.25 * L * (m3 * Lc3 + 2 * m4*Lc4);

// -------------------- Encoder & Control Variables --------------------
bool Activate = false;
const int quad_A = 2;
const int quad_B = 13;
const unsigned int mask_quad_A = digitalPinToBitMask(quad_A);
const unsigned int mask_quad_B = digitalPinToBitMask(quad_B);
long Position1 = 0, Position2 = 0;
double Kp = 10;
double Acc1, w1, wold1 = 0, qold1 = 0, qd1 = 0, qp1 = 0, C1 = 0;
double Acc2, w2, wold2 = 0, qold2 = 0, qd2 = 0, qp2 = 0, C2 = 0;
double q1 = 0, q2 = 0;
double S12 = 0, C12 = 0;
int Zcommand  = 1100;
int timescale = 100;
double Tint1 = 0, Tint2 = 0;

// For serial output in loop
long e = 0; // Placeholder for error (define as needed)
long Position = 0; // Placeholder for position (define as needed)
long C = 0; // Placeholder for command (define as needed)

// -------------------- PWM Duty Helper --------------------
template<typename pwm_type> void change_duty(
    pwm_type& pwm_obj,
    uint32_t pwm_duty,
    uint32_t pwm_period
) {
  uint32_t duty = pwm_duty;
  if (duty > pwm_period) duty = pwm_period;
  pwm_obj.set_duty(duty);
}

// -------------------- Main Control Calculation --------------------
/**
 * Calculate() - Main control loop, called by timer interrupt.
 * Reads encoder, computes kinematics/dynamics, updates PWM.
 */
void Calculate() {
  if (Activate) {
    // Update previous state
    qold1 = q1;
    qold2 = q2;
    wold1 = w1;
    wold2 = w2;

    // Read encoder (example, update as needed)
    Position1 =  (REG_TC0_CV0 % 10240) - 5120;
    Position2 =   0; // TODO: Add second encoder read if available

    // Calculate joint angles
    q1 = Position1 * 3.141592653589793238 / 5120;
    q2 = Position2 * 3.141592653589793238 / 5120;

    // Calculate position error
    qp1 = qd1 - q1;
    qp2 = qd2 - q2;

    // Calculate velocity
    w1 = qp1 * timescale;
    w2 = qp2 * timescale;

    // Calculate acceleration
    Acc1 = (w1 - wold1) * timescale;
    Acc2 = (w2 - wold2) * timescale;

    // Trig for dynamics
    S12 = sin(q1 - q2);
    C12 = cos(q1 - q2);
    /*
      Commands Guide
      0  => 3.5 V
      1100 =>   2 V
      2190 => 0.5 V
    */

    // Calculate torques (Intrinsic)
    Tint1 = A * Acc1 + B * C12 * Acc2 + Z * S12 * w1 + S12 * (Z - B * (w1 - w2)) * w2;
    Tint2 = B * C12 * Acc1 + G * Acc2 - S12 * (Z + B * (w1 - w2)) * w1 - Z * S12 * w2;

    // Update commands
    C1 = Zcommand + Kp * qp1;
    C2 = Zcommand + Kp * qp2;

    // Saturation
    if (C1 > 2190) C1 = 2190;
    if (C1 < 0)    C1 = 0;
    PWM_DUTY_PIN_35 = C1;
    if (C2 > 2190) C2 = 2190;
    if (C2 < 0)    C2 = 0;
    PWM_DUTY_PIN_42 = C2;

    // Output PWM
    change_duty(pwm_pin35, PWM_DUTY_PIN_35, PWM_PERIOD_PIN_35);
    change_duty(pwm_pin42, PWM_DUTY_PIN_42, PWM_PERIOD_PIN_42);
  } else {
    Serial.println("Waiting...");
  }
}

// -------------------- Calibration Routine --------------------
/**
 * Calibration() - Calibrates encoders and system before activation.
 */
void Calibration() {
  Activate = false;
  // TODO: Add actual calibration logic if needed
  // while (sensor) { /* Wait for sensor or user input */ }
  Activate = true;
}

// -------------------- Arduino Setup --------------------
/**
 * setup() - Arduino setup function. Initializes serial, hardware, and starts control loop.
 */
void setup() {
  Serial.begin(115200);
  Calibration();

  // Start Calculation Interrupt
  Timer3.attachInterrupt(Calculate);
  Timer3.start(100000 / timescale ); // Calls every 10ms

  delay(100);

  // Start PWM signals
  pwm_pin35.start(PWM_PERIOD_PIN_35, PWM_DUTY_PIN_35);
  pwm_pin42.start(PWM_PERIOD_PIN_42, PWM_DUTY_PIN_42);

  // activate peripheral functions for quad pins
  REG_PIOB_PDR = mask_quad_A;     // activate peripheral function (disables all PIO functionality)
  REG_PIOB_ABSR |= mask_quad_A;   // choose peripheral option B
  REG_PIOB_PDR = mask_quad_B;     // activate peripheral function (disables all PIO functionality)
  REG_PIOB_ABSR |= mask_quad_B;   // choose peripheral option B

  // Activate clock for TC0
  REG_PMC_PCER0 = (1 << 27);
  // Select XC0 as clock source and set capture mode
  REG_TC0_CMR0 = 5;
  // Activate quadrature encoder and position measure mode, no filters
  REG_TC0_BMR = (1 << 9) | (1 << 8) | (1 << 12);
  // enable the clock (CLKEN=1) and reset the counter (SWTRG=1)
  // SWTRG = 1 necessary to start the clock!!
  REG_TC0_CCR0 = 5;

}

// -------------------- Arduino Main Loop --------------------
/**
 * loop() - Arduino main loop. Prints debug info over serial.
 */
void loop() {
  Serial.print("Error = ");
  Serial.println(e, DEC);
  Serial.print("Position = ");
  Serial.println(Position, DEC);
  Serial.print("Command = ");
  Serial.println(C, DEC);
  Serial.println();
  delay(100);
}
