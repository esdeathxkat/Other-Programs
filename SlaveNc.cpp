#include "mbed.h"

// Define SPI communication pins (SPI1 for Nucleo STM32F411)
SPI spi_slave(PA_6, PA_7, PA_5);  // MISO, MOSI, SCK
DigitalIn ss(PB_6);               // Slave Select (SS) pin

// Define PWM pin for servo
PwmOut servo(PA_8);               // Adjust to a PWM-capable pin on Nucleo (PA_8)
// Define onboard LED (LD2 on Nucleo)
DigitalOut led1(LED1);             // LED1 on the board (LD2 on Nucleo)

int main() {
    // Set up the SPI slave
    spi_slave.format(8, 0);        // 8-bit data, Mode 0
    spi_slave.frequency(1000000);  // 1 MHz frequency

    // Servo setup - usually between 1ms (0 degrees) and 2ms (180 degrees)
    servo.period_ms(20);           // Set PWM period to 20ms (typical for servos)
    servo.pulsewidth_ms(1.0f);     // Start at 0 degrees (1ms pulse width)

    // Initially turn off the LEDs
    led1 = 0;

    while (1) {
        // Wait for the slave select signal to be low
        while (ss.read() == 1);  // Wait for SS to go low

        // Read the command from the master
        char command = spi_slave.write(0x00);  // Send dummy byte to read data

        // Handle the received command
        switch (command) {
            case 0x00:  // Reset everything
                servo.pulsewidth_ms(static_cast<float>(0.0)); // Servo to 0 degrees
                led1 = 0;                   // Turn off LED1
                break;
            case 0x01:  // Turn on LED1, move servo to 90 degrees
                servo.pulsewidth_ms(static_cast<float>(1.5)); // Servo to 90 degrees
                led1 = 1;                   // Turn on LED1
                break;
            case 0x02:  // Turn off LED1, move servo to 180 degrees
                servo.pulsewidth_ms(static_cast<float>(2.0)); // Servo to 90 degrees
                led1 = 0;                   
                break;
            default:
                servo.pulsewidth_ms(static_cast<float>(0.0)); // Servo to 0 degrees
                led1 = 1;
                break;
        }

        while (ss.read() == 0);  // Wait for SS to go high
    }
}
