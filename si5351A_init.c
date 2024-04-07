#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>

// Si5351A I2C address
#define SI5351A_ADDRESS 0x60

// Register addresses
#define PLL_A_REG_MSB 0x26
#define PLL_A_REG_LSB 0x27
#define CLK_CTRL_REG 0x0F

// Constants for PLL and clock configuration
#define PLL_DIVIDER 1
#define OUTPUT_FREQ 457000 // 457kHz

int main() {
    // Initialize WiringPi and the I2C connection
    wiringPiSetup();
    int si5351a_fd = wiringPiI2CSetup(SI5351A_ADDRESS);

    if (si5351a_fd == -1) {
        fprintf(stderr, "Error opening I2C device\n");
        return 1;
    }

    // Configure PLL A for the desired output frequency
    int pllFreq = OUTPUT_FREQ * PLL_DIVIDER;
    wiringPiI2CWriteReg8(si5351a_fd, PLL_A_REG_MSB, (pllFreq >> 8) & 0xFF);
    wiringPiI2CWriteReg8(si5351a_fd, PLL_A_REG_LSB, pllFreq & 0xFF);

    // Configure Clock 0 for the desired output frequency
    wiringPiI2CWriteReg8(si5351a_fd, CLK_CTRL_REG, 0x4C);  // CLK0 powered on, driven by PLL A

    // Close the I2C connection
    close(si5351a_fd);

    return 0;
}

for raspberry pi
sudo apt-get update
sudo apt-get install wiringpi
gcc -o si5351a_program si5351a_program.c -lwiringPi
./si5351a_program


To use a Raspberry Pi to program the Si5351A, you'll need to connect the Si5351A to the Raspberry Pi using the I2C interface. Here's a step-by-step guide:
Hardware Connections:
Connect Si5351A to Raspberry Pi:
Connect the I2C lines (SCL and SDA) from the Si5351A to the corresponding GPIO pins on the Raspberry Pi. The Si5351A may need pull-up resistors on these lines.

Power Supply:
Provide the required power supply to the Si5351A. Connect the ground (GND) pin of the Si5351A to the ground of your Raspberry Pi.

Software Setup:
Enable I2C Interface on Raspberry Pi:
Ensure that the I2C interface is enabled on your Raspberry Pi. You can enable it through the raspi-config utility or by modifying the /boot/config.txt file.

Install Necessary Software:
Install the i2c-tools package to use utilities for checking I2C devices:
sudo apt-get update
sudo apt-get install i2c-tools

Enable I2C Kernel Module:
Add the I2C kernel modules to the /etc/modules file to ensure they are loaded at boot:
sudo echo "i2c-dev" >> /etc/modules

Reboot Raspberry Pi:
Reboot the Raspberry Pi for the changes to take effect:
sudo reboot

Install WiringPi Library:
If you haven't installed WiringPi (a GPIO access library), you can do so using:
sudo apt-get install wiringpi

Verify:
Check I2C Devices:
Use the i2cdetect command to check if the Si5351A is detected on the I2C bus:
sudo i2cdetect -y 1
