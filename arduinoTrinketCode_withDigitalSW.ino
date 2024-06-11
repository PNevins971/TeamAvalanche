/*
 * Avalanche Rescue Transmitter Code 
 * 
 * PSU Electrical and Computer Engineering Department
 * Senior Project 2024
 * 
 * Github:(insert link)
 * 
 * Program Authors:
 *  Phil Nevins
 *  Roberto Torres
 *  
 * Description:
 *    - Avalanche Transmitter Code runs on an Adafruit Pro Trinket 3v which programs an Adafruit Si5351 Clock Generator Breakout to generate the
 *    international standard 457 kHZ frequency for Avalanche Rescue Transceivers. This signal is then pulsed via BJT transistor with an AND Gate by
 *    the Trinket at programmable duty cycle. This pulsed signal is then transmitted via a ferrite rod antenna tuned to the programmed frequency.
 * 
 * Design Notes:
 *    - Includes battery check feature with button and 4 LEDs. The number of LEDs turned on corresponds with the estimated voltage remainging in the
 *    battery pack
 *    - LED Trasnmitting indicator.
 *    - Designed around 4xAA alkaline battery pack. About 6.2V input voltage.
 *    - Utilizes Etherkit Si5351 library. (insert link)
 */

//
#include <Wire.h>
#include <si5351.h>

Si5351 si5351;
const int outputGatePin = 12; //Pin 12 to transistor
const int buttonPin = 8;  // Pin 8 to Push button for battery check feature 
const int ledPins[] = {3, 4, 5, 6}; // LED pins for 25%, 50%, 75%, 90%
const int ledPinTx = 13; // Green Led when transmitting
unsigned long desiredOnTime = 200; //Duty cycle on time
unsigned long desiredOffTime = 800; //Duty cycle off time


// Voltage thresholds for 25%, 50%, 75%, 90% of battery capacity. True voltage div by 2 via voltage divider
const float voltageThresholds[] = {2.5, 2.7, 2.9, 3.0}; 

void setup() {
  //Setup all I/O pins
  pinMode(outputGatePin, OUTPUT);
  digitalWrite(outputGatePin, LOW);

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  pinMode(ledPinTx, OUTPUT);
  digitalWrite(ledPinTx, LOW);

  pinMode(buttonPin, INPUT);

  //Setup Si5351 board
  Wire.begin();
  si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0); // (insert comment)
  si5351.set_pll(SI5351_PLL_FIXED, SI5351_PLLA); // (insert comment)
  si5351.set_freq((457000ULL * 100ULL), SI5351_CLK0); // (insert comment)
  si5351.output_enable(SI5351_CLK0, true); // enables output CLK0 
}

void loop() {
  
  //Reads buttonPin input, if battery check button has been pushed, runs checkBattery function.
  if (digitalRead(buttonPin) == HIGH) { //read if button has been pushed
    checkBattery();               
  }

  //Loops ouputGatePin and LedPinTx HIGH for desiredOnTime then LOW for desiredOnTime. 
  digitalWrite(outputGatePin, HIGH);  
  digitalWrite(ledPinTx, HIGH);
  delay(desiredOnTime);

  digitalWrite(outputGatePin, LOW);
  digitalWrite(ledPinTx, LOW);
  delay(desiredOffTime);
}

void checkBattery() {
  float batteryVoltage = analogRead(A1) * (3.3 / 1023.0); // A1 connected to battery voltage via voltage divider

  // Light up corresponding LEDs based on battery voltage
  for (int i = 0; i < 4; i++) {
    if (batteryVoltage >= voltageThresholds[i]) {
      digitalWrite(ledPins[i], HIGH);
    } 
    else {
      break;
    }
  }
  delay(2000);
  // Turn off all LEDs
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}
