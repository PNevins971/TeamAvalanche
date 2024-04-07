#include <si5351.h>
#include <Wire.h>

Si5351 si5351;

void setup() {
  Wire.begin();
  si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
  
  // Set up Clock 0 for 457 kHz
  si5351.set_freq((457000ULL * 100ULL), SI5351_CLK0);
  si5351.output_enable(SI5351_CLK0, true);
}

void loop() {
  // Nothing to do in the loop
}
