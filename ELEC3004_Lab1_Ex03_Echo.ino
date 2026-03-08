// Filename: ELEC3004_Lab1_Ex03_Echo.ino

// Rewritten by Miguel Valencia | School of EECS, UQ
// Original code by Ian Clough | School of EECS, UQ
// Feedforward echo:
// y[n] = a*x[n] + (1 - a)*x[n - D]

// Note: We require D < N to ensure the buffer is large enough
const uint16_t N = 44900; // Circular buffer length in samples
const uint16_t D = 39000; // Echo delay in samples

uint16_t x_arr[N];            // Array storing past samples of input signal
 
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

  // Initialise buffer to half-way so stored silence corresponds to zero AC signal
  for (uint16_t n = 0; n < N; n++) {
    x_arr[n] = 2048;
  }
  
}

void loop() {
  static uint16_t n = 0;                  // Current write index in circular buffer
  
  uint16_t x_raw = analogRead(A5);        // Current raw input sample x[n]
  uint16_t x = x_raw;                     // Select raw/filtered input sample
  
  uint16_t n_delay = (n + N - D) % N;     // Index corresponding to x[n - D]
  uint16_t x_delay = x_arr[n_delay];      // Delayed sample x[n - D]
  x_arr[n] = x;                           // Store current sample in array
  
  uint16_t y = (x + x_delay) / 2;         // y[n] = 0.5*x[n] + 0.5*x[n - D]
  analogWrite(DAC1, y);

  n = (n + 1) % N;                        // Advance circular buffer

  delayMicroseconds(20);                  // Adjust sample rate

}
