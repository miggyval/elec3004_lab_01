// Filename: ELEC3004_Lab1_Ex02_SampRecon.ino

// Rewritten by Miguel Valencia | School of EECS, UQ
// Original code by Ian Clough | School of EECS, UQ
 
void setup() {
  // Power for ADC and DAC filter boards
  pinMode(A0, OUTPUT);        // ADC filter - Vcc
  pinMode(A1, OUTPUT);        // ADC filter - GND
  pinMode(A8, OUTPUT);        // DAC filter - Vcc
  pinMode(A9, OUTPUT);        // DAC filter - GND

  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A8, HIGH);
  digitalWrite(A9, LOW);
  
  analogReadResolution(12);   // 12-bit ADC resolution (analog input)
  analogWriteResolution(12);  // 12-bit DAC resolution (analog output)
}

void loop() {
  uint16_t x_raw = analogRead(A5);
  uint16_t x_filt = analogRead(A3);

  uint16_t x = x_raw;   // Select raw/filtered input sample
  
  delayMicroseconds(0); // Delay between sample/reconstruct (us)

  // Digital Signal Processor (DSP)
  // You can modify this to implement a DSP filter:
  // E.g., y[n] = 0.5*(x[n] + x[n-1]),
  //    or y[n] = x[n] * 2,
  //    or y[n] = x[n] + 10
  // Note: Take care to consider limitations of integers.
  //       You will also need to consider memory storage
  //       for systems that are not memoryless, i.e.,
  //       if it relies on past-input / output samples.
  // Default to identity filter H(z) = 1 <=> y[n] = x[n]
  uint16_t y = x;
  
  analogWrite(DAC1, y); // Reconstruct y[n] through DAC1

}
