#include "mbed.h"

// Define the onboard LED pins
DigitalOut led1(LED1); // Onboard LED1
DigitalOut led2(LED2); // Onboard LED2
DigitalOut led3(LED3); // Onboard LED3

AnalogIn pot(p20);      // Potentiometer connected to analog pin P20

int main() {
    // Define base blink rates for each LED (in microseconds)
    int baseRate1 = 200000; // Base rate for LED1 (200 ms)
    int baseRate2 = 500000; // Base rate for LED2 (500 ms)
    int baseRate3 = 800000; // Base rate for LED3 (800 ms)

    while (true) {
        // Read the potentiometer value (ranges from 0.0 to 1.0)
        float potValue = pot.read();
        
        // Map potentiometer value to a speed factor (e.g., 0.1 to 1.0)
        float speedFactor = 0.1f + potValue * 0.9f; // Range from 0.1 to 1.0

        // Calculate the blink rates for each LED
        int blinkRate1 = static_cast<int>(baseRate1 * speedFactor); // Adjusted blink rate for LED1
        int blinkRate2 = static_cast<int>(baseRate2 * speedFactor); // Adjusted blink rate for LED2
        int blinkRate3 = static_cast<int>(baseRate3 * speedFactor); // Adjusted blink rate for LED3

        // Blink LED1
        led1 = 1;          // Turn on LED1
        wait_us(blinkRate1); // Wait for the mapped blink rate for LED1
        led1 = 0;          // Turn off LED1
        wait_us(blinkRate1); // Wait for the same amount of time

        // Blink LED2
        led2 = 1;          // Turn on LED2
        wait_us(blinkRate2); // Wait for the mapped blink rate for LED2
        led2 = 0;          // Turn off LED2
        wait_us(blinkRate2); // Wait for the same amount of time

        // Blink LED3
        led3 = 1;          // Turn on LED3
        wait_us(blinkRate3); // Wait for the mapped blink rate for LED3
        led3 = 0;          // Turn off LED3
        wait_us(blinkRate3); // Wait for the same amount of time
    }
}
