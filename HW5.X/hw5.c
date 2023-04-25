#include "nu32dip.h"
#include "spi.h"
#include <math.h>


#define PI 3.1415



int main(void){
    NU32DIP_Startup();
    initSPI();

    int sin_w[100000];
    int triangle_w[50000];
    
    for(int i=0;i < 100000; i++){
        sin_w[i] = (int)(511.5*sin(2*PI*i/100000) + 511.5);
    }
    
    for(int j = 0;j<50000;j++){
        if(j<25000){
            triangle_w[j] = (int)(j * 1023/25000);
        }
        else{
            triangle_w[j] = (int)(50000-j) * 1023/25000;
        }
        
    }
    while(1){
        for(int k = 0; k < 100000; k++){
            generate((unsigned short)sin_w[k],0);
            if(k >= 50000){
                generate((unsigned short)triangle_w[k-50000],1);
            }
            else{
                generate((unsigned short)triangle_w[k],1);    
            }
            
        }
        
        
    }

    
    
}
