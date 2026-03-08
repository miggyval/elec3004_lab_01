// Filename: ELEC3004_Lab1_Ex01_LUT.ino

// Rewritten by Miguel Valencia | School of EECS, UQ
// Original code by Ian Clough | School of EECS, UQ

// Number of samples in one period
const uint16_t N = 16;

// Look-up-table (LUT) for one period of sampled sine wave signal x[n]
// 12-bit values written in hexadecimal
const uint16_t x[N] = {
  0x800,0xB0F,0xDA8,0xF64,
  0xFFF,0xF64,0xDA8,0xB0F,
  0x800,0x4F0,0x257,0x09B,
  0x000,0x09B,0x257,0x4F0
};
 
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
  // Note: static used to keep index persistent between function calls
  static uint16_t n = 0;        // Index of current sample
  
  analogWrite(DAC1, x[n]);      // Output current sample x[n]
  n = (n + 1) % N;              // Increment sample index and wrap periodically

  delayMicroseconds(0);         // Adjust to change DAC update rate (us)
}
