# ELEC3004 Signals, Systems & Control
## Semester 1, 2026
## Lab 1 - Introduction to Arduino Due: Sampling and Reconstruction

# Pre-lab
- Revise basic sampling and the Nyquist sampling theorem
- Familiarise yourself with Arduino Due by reading the documentation
- Review analogue low-pass filters (low-pass filter, Sallen-Key topology for Butterworth filter)

# Lab Instructions
- Work together in groups of 2-3.
- The experiments are designed to help you understand concepts
- Ask questions and practice mindfulness and reflectivity when completing the lab
- This lab isn't a step-by-step recipe. Feel free to experiment with the parameters (within reason)
- Be sure to practice standard laboratory safety measures when working with electrical circuits


# Experiment 1: Sine Wave Generation
## Introduction
In this experiment you will be using the Arduino Due to generate and output a sine wave.

## Setup
### Hardware Setup
1. Connect the Arduino Due to a computer with the micro-B USB cable using the programming port
2. Connect the DAC filter board to the Arduino Due with the 'Raw' board pin is connected to DAC1 and the 'Vcc' board pin connected to A8.
3. Connect the PMOD-CON4 (pin to RCA) to the filter board with the 'P1' pin connected to the 'Raw' socket and 'GD' pin connected to the 'GND' socket.
4. Using an RCA to BNC cable, connect the socket aligned to the raw output to an oscilloscope (CH1)

### Software Setup
1. Download and open the Arduino IDE (Legacy Version 1.8)
2. Go to Tools > Board > Board Manager
3. Search for the Arduino Due library and install it
4. In Tools > Board, select the Arduino Due (Programming Port)
5. In Tools > Port, select the correct port that the Arduino is connected to

### Experimental Aims
- To use the Arduino Due DAC as a look-up-table (LUT) signal generator.
- To observe the real-world characteristics of reconstructed signals.
- To observe the effect of filtering on a DAC output signal

### Learning Outcomes
By the end of this experiment, you should be able to:
- To configure, program and upload code to an Arduino
- Explain how to use a look-up-table to generate a signal and why it is used
- Describe the shape of a DAC output
- Determine the sampling rate and signal frequency of a reconstructed signal
- Explain the effects of filtering on a reconstructed signal

### Experimental Procedure
- After setting up the hardware and software, open the Arduino file `ELEC3004_Lab1_Ex01.ino`
- Upload the program to the Arduino Due
- Measure and record:
  - the sample rate
  - the signal frequency
  - the signal amplitude
- Change the `delayMicroseconds(0)` to so that the sample rate is at 50 kHz.
- Measure and record:
  -  the *new* sample rate
  -  the *new* signal frequency
  -  the signal amplitude
- If the sample rate is not as expected change the delay accordingly
- Change the line `analogWrite(DAC1, LUT[ctr1%16])` so that:
  - the signal frequency doubles
  - the sampling rate stays the same
 
### Questions
- What did you observe from this experiment? State your findings.
- If the sample rate did not change as expected, why was it different?
- Describe what happened when you changed `analogWrite(DAC1, LUT[ctr1%16])`.
- What are the advantages of using a look-up-table and what is the alternative?
