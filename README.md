# ELEC3004 Signals, Systems & Control
## Semester 1, 2026

## Quick Links
- [Pre-lab](#pre-lab)
- [Lab Instructions](#lab-instructions)
- [Experiment 1: Sine Wave Generation](#experiment-1-sine-wave-generation)
- [Experiment 2: Sampling and Reconstruction](#experiment-2-sampling-and-reconstruction)
- [Experiment 3: Feedforward Echo](#experiment-3-feedforward-echo)
- [Experiment 4: Feedback Echo](#experiment-4-feedback-echo)
- [Summary Questions](#summary-questions)

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
5. In Tools > Port, select the correct port that the Arduino is connected to.

### Experimental Aims
- To use the Arduino Due DAC as a look-up-table (LUT) signal generator.
- To observe the real-world characteristics of reconstructed signals.
- To observe the effect of filtering on a DAC output signal
- To produce the signal output defined mathematically as:

$$
  x[n] = A\sin{\left(\frac{2\pi n}{N}\right)} + C
$$

### Learning Outcomes
By the end of this experiment, you should be able to:
- To configure, program and upload code to an Arduino
- Explain how to use a look-up-table to generate a signal and why it is used
- Describe the shape of a DAC output
- Determine the sampling rate and signal frequency of a reconstructed signal
- Explain the effects of filtering on a reconstructed signal

### Experimental Procedure
- After setting up the hardware and software, open the Arduino file `ELEC3004_Lab1_Ex01_LUT.ino`
- Upload the program to the Arduino Due
- Measure and record:
  - the sample rate
  - the signal frequency
  - the signal amplitude
- Modify the `delayMicroseconds(0)` line to so that the sample rate is at 50 kHz.
- Measure and record:
  -  the *new* sample rate
  -  the *new* signal frequency
  -  the signal amplitude
- If the sample rate is not as expected change the delay accordingly
- Modify the code so that:
  - the signal frequency doubles
  - the sampling rate stays the same
- Hint: What does the line `n = (n + 1) % 1` do?
 
### Questions
- What did you observe from this experiment? State your findings.
- If the sample rate did not change as expected, why was it different?
- Describe what happened when you modified `n = (n + 1) % 1`.
- What are the advantages of using a look-up-table and what is the alternative?

# Experiment 2: Sampling and Reconstruction
## Introduction
In this experiment you will use the Arduino Due to sample an analogue input using the ADC, optionally apply a simple DSP operation, and reconstruct the signal through the DAC.

## Setup
### Hardware Setup
1. Fit both the ADC filter board and the DAC filter board.
2. Connect the output of the oscilloscope wave generator to the input of the ADC filter board.
3. Use a BNC T-piece if you want to observe both the input and output signals simultaneously.
4. Connect the DAC output to the oscilloscope.
5. Set the wave generator to a sine wave with parameters:
   - frequency: 1 kHz
   - offset: 1.65 V
   - amplitude: no more than about 3.3 Vpp

### Software Setup
Ensure that the Arduino IDE is setup according to the last experiment:
1. Download and open the Arduino IDE (Legacy Version 1.8)
2. Go to Tools > Board > Board Manager
3. Search for the Arduino Due library and install it
4. In Tools > Board, select the Arduino Due (Programming Port)
5. In Tools > Port, select the correct port that the Arduino is connected to.
1. Open the Arduino file `ELEC3004_Lab1_Ex02_SampRecon.ino`

### Experimental Aims
- To sample an analogue input and reconstruct it using the Arduino Due.
- To observe the effects of sample rate on reconstruction.
- To compare raw and filtered input/output signals.
- To connect the code implementation to the mathematical model:

$$
  y[n] = f(x[n]),\quad x[n] = x\left(n T_{s}\right)
$$

### Learning Outcomes
By the end of this experiment, you should be able to:
- describe the signal path from ADC to DSP to DAC,
- explain the meaning of the memoryless system $y[n] = f(x[n])$,
- distinguish between raw and filtered analogue input channels,
- relate changes in sample rate to reconstruction quality and aliasing effects,
- explain why some DSP modifications can cause clipping or overflow.


### Experimental Procedure
- After setting up the hardware and software, open `ELEC3004_Lab1_Ex02_SampRecon.ino`
- Upload the program to the Arduino Due
- Verify that the DAC output follows the ADC input for a 1 kHz sine wave
- Measure and record:
  - the input frequency
  - the output frequency
  - the input amplitude
  - the output amplitude
- Modify `delayMicroseconds(0)` to reduce the sample processing rate to approx. 20 kHz
- Connect the 'raw' input and 'raw' output
- Change the input sine wave frequency to the following frequencies and note observations:
  - 1 kHz, 9 kHz, 10 kHz, 11 kHz, 19 kHz, 20 kHz, 21 kHz,
  - 29 kHz, 30 kHz, 31 kHz, 39 kHz, 40 kHz and 41 kHz.
  - Note the shape of the signal and the signal output frequency
- Repeat the experiment for:
  - Filtered input + raw output
  - Raw input + filtered output
  - Filtered input + filtered output
- Modify the line `uint16_t y = x` to test another memoryless system.

### Questions
- What did you observe when the input frequency approached the sampling limit?
- Why did the output amplitude reduce towards zero at some frequencies?
- What differences did you observe between the raw and filtered outputs?
- What happened when you reduced the sample rate?
- What is the effect of changing the DSP line to scale or offset the signal?
- What do integer overflow and clipping look like in theory and in practice?
- What do you expect to happen to input components above 10 kHz when using the filtered input?

---

# Experiment 3: Feedforward Echo
## Introduction
In this experiment you will implement an echo effect using a system with memory. The current input sample is combined with a delayed version of the input signal stored in a circular buffer.

## Setup
### Hardware Setup
1. Fit both the ADC filter board and the DAC filter board.
2. Connect an audio source or the oscilloscope wave generator to the ADC filter input.
3. Connect the DAC output to powered speakers or another safe audio output.
4. Ensure the input signal is appropriately offset via the ADC filter board.

### Software Setup
Ensure that the Arduino IDE is setup according to the last experiment:
1. Download and open the Arduino IDE (Legacy Version 1.8)
2. Go to Tools > Board > Board Manager
3. Search for the Arduino Due library and install it
4. In Tools > Board, select the Arduino Due (Programming Port)
5. In Tools > Port, select the correct port that the Arduino is connected to.
1. Open the Arduino file `ELEC3004_Lab1_Ex02_SampRecon.ino`

### Experimental Aims
- To implement a discrete-time echo system with memory.
- To relate the program to the feedforward echo model
  
$$
  y[n] = (1 - \alpha) x[n] + \alpha x[n-D]
$$
  
- To investigate the effects of delay, mixing ratio, and sample rate on the output signal.

### Learning Outcomes
By the end of this experiment, you should be able to:
- explain why this system is not memoryless,
- describe the purpose of a circular buffer,
- relate the delay $D$ in samples to the echo delay in seconds,
- explain how the coefficient $\alpha$ affects the relative strength of the direct and delayed signals,
- describe how sample rate affects perceived echo time.

### Experimental Procedure
- After setting up the hardware and software, open `ELEC3004_Lab1_Ex03_EchoFeedforward.ino`
- Upload the program to the Arduino Due
- Apply an audio signal or sinusoidal input and listen to the output
- Vary the delay $D$ and observe the effect on the echo time
- Vary the mixing ratio $\alpha$ and observe how the direct and delayed signals change
  Note: a default delay is set as 0.5
- Change the sample rate by modifying `delayMicroseconds(...)`
- Compare the effect of:
  - a small delay
  - a large delay
  - a faster sample rate
  - a slower sample rate
- Try both slowly varying and rapidly varying audio inputs

### Questions
- Why is this system classified as a system with memory?
- What role does the circular buffer play?
- How does changing $D$ affect the echo?
- How does changing the sample rate affect the echo time in seconds?
- What happens when $\alpha = 0$?
- What happens when the delayed term is much larger or much smaller than the direct term?
- How is this experiment different from the memoryless system in Experiment 2?

---

# Experiment 4: Feedback Echo
## Introduction
In this experiment you will modify the previous echo system so that the delayed signal is based on the output rather than the input. This creates a feedback echo system, which can produce repeated decaying echoes.

## Setup
### Hardware Setup
1. Keep the same hardware setup as in Experiment 3.
2. Ensure both ADC and DAC filter boards are fitted.
3. Use powered speakers or a safe monitoring setup for audio output.

### Software Setup
Ensure that the Arduino IDE is setup according to the last experiment:
1. Download and open the Arduino IDE (Legacy Version 1.8)
2. Go to Tools > Board > Board Manager
3. Search for the Arduino Due library and install it
4. In Tools > Board, select the Arduino Due (Programming Port)
5. In Tools > Port, select the correct port that the Arduino is connected to.
1. Open the Arduino file `ELEC3004_Lab1_Ex04_EchoFeedback.ino`

### Experimental Aims
- To implement an echo system with feedback.
- To compare feedforward and feedback echo.
- To investigate the effect of feedback gain on decay, persistence, and instability.

### Learning Outcomes
By the end of this experiment, you should be able to:
- explain the difference between feedforward and feedback systems,
- relate the code to the model

$$
  y[n] = (1 - \alpha) x[n] + \alpha y[n-D]
$$
  
- explain why feedback causes repeated echoes,
- predict how the system behaves as the feedback factor increases,
- describe why large feedback values can lead to instability or saturation.

### Experimental Procedure
- After setting up the hardware and software, open `ELEC3004_Lab1_Ex04_EchoFeedback.ino`
- Upload the program to the Arduino Due
- Apply an audio input and listen to the resulting output
- Compare the feedback echo with the feedforward echo from Experiment 3
- Adjust the feedback strength and observe:
  - fast decay
  - slow decay
  - sustained response
- Try values of the feedback factor near:
  - 0.9
  - 1.0
- Use a small-amplitude input when testing values near 1.0
- Change the delay $D$ and the sample rate, and observe the effect on the repeated echoes

### Questions
- What is the difference between feedforward echo and feedback echo?
- Why does feedback produce repeated echoes?
- What happens as the feedback factor approaches 1?
- What do you think would happen if the feedback factor is greater than 1?
- Why can the system become unstable or saturate for large feedback values?
- How does changing $D$ affect the sound of the feedback echo?
- How does the feedback echo relate to ideas such as reverberation?
- Which system (feedforward / feedback) do you think models an echo more accurately?

---

# Summary Questions
- Which experiments were memoryless, and which had memory?
- What role did filtering play across the experiments?
- How did sample rate influence waveform quality, aliasing, and echo time?
- What practical limitations did you observe when using integer arithmetic and finite memory?

# Challenge Exercises
Find the impulse response of the following systems:

Feedforward Echo:

$$
y[n] = (1 - \alpha) x[n] + \alpha x[n - D]
$$

Feedback Echo:

$$
y[n] = (1 - \alpha) x[n] + \alpha y[n - D]
$$
