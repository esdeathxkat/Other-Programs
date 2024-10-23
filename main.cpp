#include "mbed.h"

// Define components
AnalogIn potentiometer(p18);       // Potentiometer for frequency selection
DigitalIn button(p19, PullUp);     // Push button with PullUp resistor (active low)
PwmOut buzzer(p21);                // PWM output for buzzer
DigitalOut myled1(LED1);           // Onboard LED that turns on when button is pressed

// Define the seven segments of a 7-segment display (common anode)
DigitalOut A(p5);
DigitalOut B(p6);
DigitalOut C(p7);
DigitalOut D(p8);
DigitalOut E(p9);
DigitalOut F(p10);
DigitalOut G(p11);

// Frequency and beat arrays
float frequencyArray[12] = {0};    // Holds 12 frequency values
int beatArray[12] = {500, 300, 400, 600, 200, 700, 350, 250, 550, 450, 650, 500};  // Beat lengths in milliseconds

int currentIndex = 0;              // To track which frequency is being set

// Function to calculate frequency based on potentiometer value (maps analog value to frequency range)
float calculateFrequency(float analogValue) {
    return 200.0 + analogValue * (2000.0f - 200.0f);  // Maps 0.0 - 1.0 to 200Hz - 2000Hz
}

// Function to display current index on 7-segment display, with index shifted by 1
void displayIndex(int index) {
    // Clear the display (common anode: set 1 to turn off all segments)
    A = B = C = D = E = F = G = 1;

    // Adjust the display so it starts at 1 instead of 0
    switch(index + 1) {
        case 1: A=1; B=0; C=0; D=1; E=1; F=1; G=1; break;  // Displays '1'
        case 2: A=0; B=0; C=1; D=0; E=0; F=1; G=0; break;  // Displays '2'
        case 3: A=0; B=0; C=0; D=0; E=1; F=1; G=0; break;  // Displays '3'
        case 4: A=1; B=0; C=0; D=1; E=1; F=0; G=0; break;  // Displays '4'
        case 5: A=0; B=1; C=0; D=0; E=1; F=0; G=0; break;  // Displays '5'
        case 6: A=0; B=1; C=0; D=0; E=0; F=0; G=0; break;  // Displays '6'
        case 7: A=0; B=0; C=0; D=1; E=1; F=1; G=1; break;  // Displays '7'
        case 8: A=0; B=0; C=0; D=0; E=0; F=0; G=0; break;  // Displays '8'
        case 9: A=0; B=0; C=0; D=0; E=1; F=0; G=0; break;  // Displays '9'
        case 10:A=0; B=0; C=0; D=1; E=0; F=0; G=0; break;  // Displays 'A'
        case 11:A=1; B=1; C=0; D=0; E=0; F=0; G=0; break;  // Displays 'b'
        case 12:A=0; B=1; C=1; D=0; E=0; F=0; G=1; break;  // Displays 'C'
    }
}

// Function to play the song after frequencies are stored
void playSong() {
    for (int i = 0; i < 12; i++) {
        displayIndex(i);                      // Display the current index being played
        buzzer.period(1.0 / frequencyArray[i]);  // Set the frequency
        buzzer = 0.5f;                           // 50% duty cycle
        wait_us(beatArray[i] * 1000);            // Wait for the beat duration
        buzzer = 0.0f;                           // Turn off the buzzer
        wait_us(200000);                          // Short pause between notes (200ms)
    }
    buzzer = 0;  // Ensure the buzzer is off after the song is complete
}

int main() {
    // Initial display of the first index (1 at startup)
    displayIndex(currentIndex);

    while (currentIndex < 12) {
        // Check if the button is pressed (active low)
        if (button.read() == 0) {
            myled1 = 1;  // Turn on the onboard LED to indicate button press

            // Debounce delay
            wait_us(200000);  // 200ms delay for debouncing

            // Confirm the button is still pressed after debounce delay
            if (button.read() == 0) {
                // Read potentiometer value and calculate frequency
                float analogValue = potentiometer.read();
                float frequency = calculateFrequency(analogValue);

                // Store the frequency in the array
                frequencyArray[currentIndex] = frequency;

                // Wait until the button is released to avoid multiple entries
                while (button.read() == 0) {
                    wait_us(100000);  // Wait for 10ms
                }

                // Increment the index and update the 7-segment display
                currentIndex++;
                if (currentIndex < 12) {
                    displayIndex(currentIndex);
                }
            }

            myled1 = 0;  // Turn off the onboard LED
        }
    }

    // All frequencies are stored, now play the song
    playSong();
}
