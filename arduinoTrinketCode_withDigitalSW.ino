
#include <Wire.h>
#include <si5351.h>

Si5351 si5351;
const int outputGatePin = 12;
const int buttonPin = 8;
const int ledPins[] = {3, 4, 5, 6}; // LED pins for 25%, 50%, 75%, 90%
const int ledPinTx = 13; // Green Led when transmitting.
unsigned long ledOnTime = 1000;
unsigned long desiredOnTime = 200;
unsigned long desiredOffTime = 800;


// Voltage thresholds for 25%, 50%, 75%, 90% of battery capacity. True voltage div by 2
const float voltageThresholds[] = {2.5, 2.7, 2.9, 3.0}; 

void setup() {
  pinMode(outputGatePin, OUTPUT);
  digitalWrite(outputGatePin, LOW);

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  pinMode(buttonPin, INPUT);

  Wire.begin();
  si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
  si5351.set_pll(SI5351_PLL_FIXED, SI5351_PLLA);
  si5351.set_freq((457000ULL * 100ULL), SI5351_CLK0);
  si5351.output_enable(SI5351_CLK0, true);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    checkBattery();
  }

  digitalWrite(outputGatePin, HIGH);
  digitalWrite(ledPinTx, HIGH);
  delay(desiredOnTime);

  digitalWrite(outputGatePin, LOW);
  digitalWrite(outputGatePin, LOW);
  delay(desiredOffTime);
}

void checkBattery() {
  float batteryVoltage = analogRead(A1) * (3.3 / 1023.0); // A1 connected to battery voltage

  // Light up LEDs based on battery voltage
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
