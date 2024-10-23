#include "mbed.h"

// Define SPI communication pins (SPI0)
SPI spi_master(p11, p12, p13);  // MOSI, MISO, SCK
DigitalOut ss(p14);             // Slave Select (SS)
DigitalIn S1(p5);               // Button S1
DigitalIn S2(p6);               // Button S2

// Define onboard LEDs (adjust pins as per your mbed board specifications)
DigitalOut led1(LED1);           // LED for Button S1 (usually LED1)
DigitalOut led2(LED2);           // LED for Button S2 (usually LED2)

// Define PWM pin for servo
PwmOut servo(p21);               // Set servo output pin to pin 21

int main() {
    // Set the SPI format and frequency
    spi_master.format(8, 0);  // 8-bit data, Mode 0
    spi_master.frequency(1000000);  // 1 MHz frequency

    ss = 1;  // Disable slave by setting SS high

    // Initially turn off the LEDs and set servo to 0 degrees
    led1 = 0;
    led2 = 0;
    servo.period_ms(20);           // Set PWM period to 20ms
    servo.pulsewidth_ms(0.0f);     // Start at 0 degrees (1ms pulse width)

    while (1) {
        ss = 0;  // Enable slave

        // Check button states and send appropriate command
        if (!S1 && !S2) {
            spi_master.write(0x00);  // Both switches are open, OFF
            led1 = 0;                 // Turn off LED1
            led2 = 0;                 // Turn off LED2
        } else if (!S1 && S2) {
            spi_master.write(0x01);  // S1 pressed, S2 open, rotate clockwise
            led1 = 1;                 // Turn on LED1
            led2 = 0;                 // Turn off LED2
        } else if (S1 && !S2) {
            spi_master.write(0x02);  // S1 open, S2 pressed, rotate counterclockwise
            led1 = 0;                 // Turn off LED1
            led2 = 1;                 // Turn on LED2
        } else if (S1 && S2) {
            spi_master.write(0x03);  // Both switches pressed, OFF
            led1 = 1;                 // Turn on LED1
            led2 = 1;                 // Turn on LED2
        }

        ss = 1;  // Disable slave
        wait_us(200000);  // Small delay for debouncing
    }
}
