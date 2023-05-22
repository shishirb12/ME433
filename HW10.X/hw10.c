#include "nu32dip.h" // constants, functions for startup and UART
#include <stdio.h>
#include "ws2812b.h"

void blink(int iterations, int time_ms); // blink the LEDs function

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    ws2812b_setup();
    int numLEDs = 4;
    int hue = 0;
    wsColor colors[numLEDs];
    while (1) {
        for (int i = 0; i < numLEDs; i++) {
            colors[i] = HSBtoRGB(hue, 0.5, 1);
            
        if (hue < 360) {
            hue = hue + 1;
        } else {
            hue = 0;
            }}
        ws2812b_setColor(colors, numLEDs);
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 48000000 / 2 / 10) {
    }
    }
}