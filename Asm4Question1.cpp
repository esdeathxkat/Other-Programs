#include "mbed.h"

PwmOut servo(p21);  // Servo motor connected to PWM pin P21
AnalogIn pot(p20);  // Potentiometer connected to analog pin P20

int main() {
    servo.period(0.02f); // Set 50Hz PWM period for servo
    
    while (1) {
        float potValue = pot.read(); // Read potentiometer value
        float pulseWidth = 0.001 + potValue * 0.001; // Map to 1ms-2ms pulse width
        servo.pulsewidth(pulseWidth); // Set servo position
        wait_us(1000000); // Short delay
    }
}