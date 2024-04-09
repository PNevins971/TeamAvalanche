#include <si5351.h>
#include <Wire.h>

Si5351 si5351;

void setup() {
  //Wire.setSDA(0); //for rasp_pi pico sda enable pin 0
  //Wire.setSCL(1); //for rasp_pi pico scl enable pin1
  Wire.begin();
  si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
  
  // Set up Clock 0 for 457 kHz
  si5351.set_pll(SI5351_PLL_FIXED,SI5351_PLLA); // attempt at fixed PLL
  //si5351.set_pll_input(SI5351_PLLA,SI5351_PLL_INPUT_CLKIN);
  si5351.set_freq((457000ULL * 100ULL), SI5351_CLK0);
  //si5351.drive_strength(SI5351_CLK0,SI5351_DRIVE_8MA); //Change rise time. Default is 2ma
  //unsigned long long pll_freq = 70500000000ULL;
  //si5351.set_freq_manual((457000ULL * 100ULL),pll_freq, SI5351_CLK0);
  //si5351.set_clock_source(SI5351_CLK0,SI5351_CLK_SRC_MS);
  si5351.output_enable(SI5351_CLK0, true);
}

void loop() {
  // Nothing to do in the loop
}
