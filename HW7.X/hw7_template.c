#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include <stdio.h>

void blink(int, int); // blink the LEDs function

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    init_mpu6050();
	
	// char array for the raw data
    unsigned char data[14];
    char message[100];
	NU32DIP_YELLOW = 1;
	// read whoami
    NU32DIP_WriteUART1("here");
    uint8_t who = whoami();
    sprintf(message, "%x", who);
    NU32DIP_WriteUART1(message);
	// if whoami is not 0x68, stuck in loop with LEDs on
	// wait to print until you get a newline
    if(who != 0x68){
        while(1){
            NU32DIP_YELLOW = 0;
        }
    }
    

    while (1) {
		// use core timer for exactly 100Hz loop
        _CP0_SET_COUNT(0);
        NU32DIP_YELLOW = 0;
        // read IMU
        burst_read_mpu6050(data);
		// convert data
        float x = conv_xXL(data);
        float y = conv_yXL(data);
        float z = conv_zXL(data);
        // print out the data
        sprintf(message, "%f %f %f\r\n",x,y,z);
        NU32DIP_WriteUART1(message);
        while (_CP0_GET_COUNT() < 48000000 / 2 / 100) {
        }
      
    }
}

// blink the LEDs
void blink(int iterations, int time_ms) {
    int i;
    unsigned int t;
    for (i = 0; i < iterations; i++) {
        NU32DIP_GREEN = 0; // on
        NU32DIP_YELLOW = 1; // off
        t = _CP0_GET_COUNT(); // should really check for overflow here
        // the core timer ticks at half the SYSCLK, so 24000000 times per second
        // so each millisecond is 24000 ticks
        // wait half in each delay
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }

        NU32DIP_GREEN = 1; // off
        NU32DIP_YELLOW = 0; // on
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
    }
}

