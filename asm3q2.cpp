#include "mbed.h"

// Define components
AnalogIn potentiometer(p18);   // Potentiometer for controlling brightness
PwmOut led(p21);               // PWM output to control LED brightness

// Define the seven segments of a 7-segment display (common anode)
DigitalOut A(p5);
DigitalOut B(p6);
DigitalOut C(p7);
DigitalOut D(p8);
DigitalOut E(p9);
DigitalOut F(p10);
DigitalOut G(p11);

// Function to calculate duty cycle based on potentiometer value
float calculateDutyCycle(float analogValue) {
    return analogValue;  // Directly map the potentiometer value (0.0 - 1.0) to PWM duty cycle (0.0 - 1.0)
}

// Function to display the brightness level on 7-segment display
void displayBrightnessLevel(int level) {
    // Clear the display (common anode: set 1 to turn off all segments)
    A = B = C = D = E = F = G = 1;

    // Display numbers from 1 to 9 based on the level
    switch(level) {
        case 1: A=1; B=0; C=0; D=1; E=1; F=1; G=1; break;  // Displays '1'
        case 2: A=0; B=0; C=1; D=0; E=0; F=1; G=0; break;  // Displays '2'
        case 3: A=0; B=0; C=0; D=0; E=1; F=1; G=0; break;  // Displays '3'
        case 4: A=1; B=0; C=0; D=1; E=1; F=0; G=0; break;  // Displays '4'
        case 5: A=0; B=1; C=0; D=0; E=1; F=0; G=0; break;  // Displays '5'
        case 6: A=0; B=1; C=0; D=0; E=0; F=0; G=0; break;  // Displays '6'
        case 7: A=0; B=0; C=0; D=1; E=1; F=1; G=1; break;  // Displays '7'
        case 8: A=0; B=0; C=0; D=0; E=0; F=0; G=0; break;  // Displays '8'
        case 9: A=0; B=0; C=0; D=0; E=1; F=0; G=0; break;  // Displays '9'
    }
}

int main() {
    // Set PWM period for LED (optional, usually doesn't need to be adjusted)
    led.period(0.001f);  // Set PWM period to 1ms (1kHz frequency)

    float lastAnalogValue = -1.0;  // To store the last potentiometer reading
    int lastBrightnessLevel = 0;    // To store the last displayed brightness level
    const float threshold = 0.05;    // Define a threshold for change

    while (true) {
        // Read potentiometer value
        float analogValue = potentiometer.read();  // Reads a value between 0.0 and 1.0

        // Calculate and set the PWM duty cycle to control LED brightness
        led = calculateDutyCycle(analogValue);

        // Map the potentiometer value to brightness levels (1 to 9)
        int brightnessLevel = 1 + analogValue * 8;  // Maps 0.0 - 1.0 to 1 - 9

        // Only update display if the analog value has changed significantly
        if (fabs(analogValue - lastAnalogValue) > threshold) {
            displayBrightnessLevel(brightnessLevel);
            lastAnalogValue = analogValue;  
            lastBrightnessLevel = brightnessLevel;  
        }

        // Small delay to prevent overwhelming the system with constant updates
        wait_us(100000);  // 50ms delay
    }
}
