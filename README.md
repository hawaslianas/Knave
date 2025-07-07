<img src="https://r2cdn.perplexity.ai/pplx-full-logo-primary-dark%402x.png" class="logo" width="120"/>

# KNAVE: 2 DOF Five Bar Haptic Device

## Project Overview

KNAVE is a 2 Degrees of Freedom (DOF) Five Bar parallel manipulator providing haptic (force feedback) interaction for applications such as neuromotor rehabilitation. The device achieves precise position and force control using real-time impedance and torque control algorithms.

## Hardware Components (Code-Relevant)

- **Actuation:** DC motors with gearbox (Capstan Drive mechanism)
- **Sensing:** Rotary encoders (E50S) for position feedback
- **Controller:** SAM3X8E ARM Cortex 32-bit microcontroller
- **Motor Drivers:** H-Bridge modules (BTS7960B, IBT-2)
- **PWM Generation:** TL494 IC
- **Current Sensing:** Analog feedback and conditioning circuits


## Control Algorithms

- **Impedance Control:** Implements dynamic force feedback based on user interaction and virtual environment modeling.
- **Torque Control:** Uses PID controllers, tuned for each motor, to regulate current and achieve desired torque.
- **Dynamic Model:** Real-time computation of robot dynamics for accurate control.
- **Closed-Loop Current Control:** Ensures precise actuation using sensor feedback.


## Software Interface

- **PC GUI:** Developed in C\# for real-time monitoring, parameter tuning, and user interaction.
- **Communication:** Serial connection between PC and microcontroller for command transmission and data feedback.


## Programming Languages \& Tools

- **Embedded C/C++:** Firmware for the SAM3X8E microcontroller.
- **C\#:** Windows application for the graphical user interface.
- **Simulation/Design:** Autodesk Inventor (mechanical), PROTEUS (circuit simulation).


## Build \& Run Instructions

1. **Firmware:**
    - Compile embedded code for the SAM3X8E microcontroller using an ARM-compatible toolchain.
    - Upload the compiled firmware to the microcontroller.
2. **PC Application:**
    - Build and run the C\# GUI application on a Windows PC.
3. **Connection:**
    - Connect the device to the PC via serial port (USB/RS232).
    - Use the GUI to interact with and monitor the system.

## Additional Notes

- PID parameters should be calibrated for optimal performance.
- Hardware setup includes custom 3D-printed parts and PCBs.
- The codebase covers embedded firmware, PC GUI, and communication protocols only. For mechanical assembly and hardware design, refer to the project documentation.

