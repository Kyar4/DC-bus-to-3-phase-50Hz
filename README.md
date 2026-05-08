# 3-Phase Pure Sine Wave Inverter

STM32-based 3-Phase DC-AC Inverter using SPWM modulation for generating low-distortion 3-phase sine wave output.

---

# Overview

This project focuses on the development of a low-voltage 3-phase pure sine wave inverter using STM32 microcontrollers and Sinusoidal Pulse Width Modulation (SPWM).

The system converts DC input power into a 3-phase AC output with 120° phase-shifted sine wave signals. The inverter is designed for educational research, embedded control experimentation and power electronics studies.

The project includes:

* STM32-based SPWM generation
* 3-phase waveform generation with 120° phase shift
* High-frequency MOSFET switching
* IR2110 high/low-side gate driving
* LC output filtering
* Oscilloscope-based waveform validation
* Real hardware testing under load

---

# Features

* 3-Phase SPWM generation using STM32 timers
* 20kHz switching frequency
* 50Hz sine wave output
* 120° phase-shifted waveform generation
* High-side and low-side MOSFET driving using IR2110
* LC low-pass filtering for sine wave reconstruction
* Real-time modulation index adjustment
* Oscilloscope validation and waveform calibration
* Hardware-tested inverter prototype

---

# Hardware Architecture

## Main Components

| Component          | Description                         |
| ------------------ | ----------------------------------- |
| STM32F103C8T6      | Main controller for SPWM generation |
| IR2110             | High/Low-side MOSFET gate driver    |
| MOSFET Power Stage | 3-phase switching stage             |
| LC Filter          | Output sine wave filtering          |
| DC Supply          | Main inverter input source          |

---

# SPWM Control Strategy

The inverter uses Sinusoidal Pulse Width Modulation (SPWM) to synthesize sinusoidal AC waveforms.

Three sinusoidal reference signals are generated with 120° phase displacement:

* Phase A = 0°
* Phase B = 120°
* Phase C = 240°

These references are compared against a high-frequency carrier waveform to generate PWM switching signals.

STM32 timers are configured for synchronized PWM generation at 20kHz switching frequency.

---

# Output Filter Design

An LC low-pass filter is implemented to reduce high-frequency switching harmonics and reconstruct clean sine wave outputs.

## Filter Parameters

| Parameter           | Value  |
| ------------------- | ------ |
| Inductor            | 3.3mH  |
| Capacitor           | 0.68uF |
| Output Frequency    | 50Hz   |
| Switching Frequency | 20kHz  |

The filter significantly improves waveform quality and reduces output distortion.

---

# Firmware Structure

```text
Core/
├── Inc/
├── Src/
│   ├── main.c
│   ├── pwm_control.c
│   ├── sine_table.c
│   ├── timer_config.c
│   └── protection.c
└── Drivers/
```

Main firmware responsibilities:

* SPWM waveform generation
* Timer synchronization
* Duty cycle updates
* Phase shifting
* Frequency control
* Modulation index adjustment

---

# Experimental Results

The inverter output was analyzed using a Tektronix digital oscilloscope.

## Validation Results

* Stable 3-phase waveform generation
* Correct 120° phase shift between phases
* Successful LC-filtered sine wave reconstruction
* Stable 20kHz PWM switching
* Reduced high-frequency output ripple

---

# Challenges & Debugging

Several engineering challenges were encountered during development:

* MOSFET failures caused by incorrect switching timing
* Shoot-through protection tuning
* Gate-driving instability during high-frequency operation
* Noise and ringing during switching transitions
* Output waveform distortion before LC filter optimization

The system was iteratively improved through oscilloscope measurements and hardware debugging.

---

# Development Tools

| Tool             | Usage                    |
| ---------------- | ------------------------ |
| STM32CubeIDE     | Firmware development     |
| Oscilloscope     | Waveform analysis        |
| EasyEDA / Altium | PCB and schematic design |
| MATLAB / PSIM    | Simulation and analysis  |

---

# Project Images

Recommended repository contents:

* Oscilloscope waveform captures
* Hardware prototype photos
* LC filter implementation
* PCB/schematic screenshots
* SPWM waveform analysis
<img width="1280" height="960" alt="P2pha" src="https://github.com/user-attachments/assets/3df66513-65b1-4280-a9c8-b18cfc34ef4e" />

---

# Applications

Potential applications include:

* Educational power electronics platforms
* Embedded motor-control experiments
* Low-power inverter systems
* Industrial automation research
* SPWM and modulation studies

---

# Future Improvements

Planned improvements:

* Closed-loop voltage regulation
* Deadtime optimization
* Protection circuitry enhancement
* SVPWM implementation
* Current feedback control
* PCB optimization for high-current operation
* FreeRTOS integration

---

# Author

Nguyen Vuong Trieu

Embedded Systems | Power Electronics | IoT Engineering

GitHub: [https://github.com/Kyar4](https://github.com/Kyar4)
