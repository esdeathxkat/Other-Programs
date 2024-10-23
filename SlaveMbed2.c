#include "mbed.h"

// Define SPI communication pins (SPI0)
SPI spi_slave(p11, p12, p13);  // MISO, MOSI, SCK
DigitalIn ss(p14);             // Slave Select (SS)
PwmOut servo(p25);             // Servo control pin

// Define onboard LEDs (LED1 and LED2)
DigitalOut led1(LED1);         // LED for Button S1
DigitalOut led2(LED2);         // LED for Button S2

int main() {
    // Set up the SPI slave
    spi_slave.format(8, 0);        // 8-bit data, Mode 0
    spi_slave.frequency(1000000);  // 1 MHz frequency

    // Servo setup - usually between 1ms (0 degrees) and 2ms (180 degrees)
    servo.period_ms(20);  // Set PWM period to 20ms (typical for servos)
    servo.pulsewidth_ms(1.0f);  // Start at 0 degrees (1ms pulse width)

    // Initially turn off the LEDs
    led1 = 0;
    led2 = 0;

    while (1) {
        // Wait for the slave select signal to be low
        while (ss.read() == 1);  // Wait for SS to go low

        // Read the command from the master
        char command = spi_slave.write(0x00);  // Send dummy byte to read data

        // Handle the received command
        switch (command) {
            case 0x00:  // Reset everything
                servo.pulsewidth_ms(1.0f);  // Servo to 0 degrees (1 ms)
                led1 = 0;                   // Turn off LED1
                led2 = 0;                   // Turn off LED2
                break;
            case 0x01:  // Turn on LED1, move servo to 90 degrees
                servo.pulsewidth_ms(1.5f);  // Servo to 90 degrees (1.5 ms)
                led1 = 1;                   // Turn on LED1
                led2 = 0;                   // Turn off LED2
                break;
            case 0x02:  // Turn on LED2, move servo to 180 degrees
                servo.pulsewidth_ms(2.0f);  // Servo to 180 degrees (2 ms)
                led1 = 0;                   // Turn off LED1
                led2 = 1;                   // Turn on LED2
                break;
            case 0x03:  // Reset everything (optional)
                servo.pulsewidth_ms(1.0f);  // Servo to 0 degrees (1 ms)
                led1 = 0;                   // Turn off LED1
                led2 = 0;                   // Turn off LED2
                break;
            default:
                // Handle invalid commands by turning both LEDs on as an error indicator
                servo.pulsewidth_ms(1.0f);  // Servo to default 0 degrees
                led1 = 1;
                led2 = 1;
                break;
        }

        // Wait for the slave select signal to go high (end of communication)
        while (ss.read() == 0);  // Wait for SS to go high
    }
}
