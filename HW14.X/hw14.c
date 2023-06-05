#include "nu32dip.h"


int main(void){
    RPA0Rbits.RPA0R = 0b0101; // setting RPA0 pin to OC1
    T2CONbits.TCKPS = 4;     // Timer2 prescaler N=4 (1:4)
    PR2 = 60000-1;              // period = (PR2+1) * N * (1/48000000) = 6 kHz
    TMR2 = 0;                // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0; 
    OC1RS = 4500;// Use timer2            // duty cycle = OC1RS/(PR2+1) = 25%
    OC1R = 500;              // initialize before turning OC1 on; afterward it is read-only
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1
    
    while(1){
        OC1RS = 3000;
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 24000000*2){}

        OC1RS = 6000;
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 24000000*2){}
    }
}
