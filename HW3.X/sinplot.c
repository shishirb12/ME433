#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>
# define PI 3.14159

void makeSin();
float Waveform[100];

int main(void) {
  char message[100];
  int i;
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  makeSin();
  for(i=0;i<100;i++){
    sprintf(message, "%f\r\n", Waveform[i]);
    NU32DIP_WriteUART1(message); // send data point
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT() < 24000000 * 0.01){}
  }
  while (1) {
	}
  }



void makeSin(){
    int i;
    for(i=0;i<100;i++){
      Waveform[i] = (3.3/2)*sin(i*(2*PI)/100) + (3.3/2);  
    }
    
    
}


		
