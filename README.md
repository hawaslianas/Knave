# KNAVE Haptic Device: Code Structure Overview

This repository contains the cleaned and organized code for the KNAVE 2-DOF Five Bar Haptic Device. The codebase is split into two main components:

## Structure

```
firmware/
  Haptic_Control_CODEX.ino
pc_gui/
  WindowsFormsApp1/ (C# Windows Forms GUI)
README.md
```

---

## 1. Embedded Firmware (`firmware/`)
- **Platform:** Arduino Due (SAM3X8E ARM Cortex MCU)
- **Main File:** `Haptic_Control_CODEX.ino`
- **Responsibilities:**
  - Read rotary encoders for joint positions
  - Compute kinematics and dynamics
  - Implement real-time control (impedance, torque, PID)
  - Generate PWM for motor drivers
  - Communicate with the PC GUI via serial

### How to Use
1. Open `firmware/Haptic_Control_CODEX.ino` in the Arduino IDE.
2. Select the Arduino Due board and correct port.
3. Upload to the device.

---

## 2. PC GUI (`pc_gui/WindowsFormsApp1/`)
- **Platform:** Windows (C# .NET Framework, Visual Studio)
- **Main Project:** `WindowsFormsApp1`
- **Responsibilities:**
  - Provide a graphical interface for device control and monitoring
  - Communicate with the embedded firmware via serial
  - Send commands, receive data, and visualize device state

### How to Use
1. Open `pc_gui/WindowsFormsApp1/WindowsFormsApp1.csproj` in Visual Studio.
2. Build and run the project.
3. Connect to the device via the appropriate COM port.

---

## Notes
- All legacy, duplicate, and test code has been removed for clarity.
- Only the latest, working versions are retained.
- For technical details, refer to the code comments and documentation within each main file.

---

**Maintainer:** [Your Name]
**Last Cleaned:** July 2025

