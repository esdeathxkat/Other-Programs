#include "mbed.h"
DigitalOut MyLed1(LED1);
DigitalOut MyLed2(LED2);
DigitalOut MyLed3(LED3);

// main() runs in its own thread in the OS
int main()
{
    while (true) {
        MyLed1 = 0;
        MyLed2 = 0;
        MyLed3 = 0;
        wait_us(1000000);
        MyLed1 = 0;
        MyLed2 = 0;
        MyLed3 = 1;
        wait_us(1000000);
        MyLed1 = 0;
        MyLed2 = 1;
        MyLed3 = 0;
        wait_us(1000000);
        MyLed1 = 0;
        MyLed2 = 1;
        MyLed3 = 1;
        wait_us(1000000);
        MyLed1 = 1;
        MyLed2 = 0;
        MyLed3 = 0;
        wait_us(1000000);
        MyLed1 = 1;
        MyLed2 = 0;
        MyLed3 = 1;
        wait_us(1000000);
        MyLed1 = 1;
        MyLed2 = 1;
        MyLed3 = 0;
        wait_us(1000000);
        MyLed1 = 1;
        MyLed2 = 1;
        MyLed3 = 1;
        wait_us(1000000);
        

    }
}

