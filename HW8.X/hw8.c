#include "nu32dip.h"
#include "ssd1306.h"
#include "font.h"
#include "mpu6050.h"

void drawLetter(int x, int y, char c);
void drawString(int x, int y, char * c);
char message[50];
unsigned char data[14];

int main(void){
    
    NU32DIP_Startup();
    i2c_master_setup();
    ssd1306_setup();
    ssd1306_clear();
    ssd1306_update();
    init_mpu6050();
    
    while(1){
        _CP0_SET_COUNT(0);
//        NU32DIP_YELLOW = 1;
//                
//        while(_CP0_GET_COUNT()<24000000){
//            
//        }
//        NU32DIP_YELLOW = 0;
//        _CP0_SET_COUNT(0);
//        while(_CP0_GET_COUNT()<24000000){
//            
//        }
//        
//              
//        }
        burst_read_mpu6050(data);
		// convert data
        float z = conv_zXL(data);
        sprintf(message, "%f", z);
        drawString(10,10, message);
        ssd1306_update();
        float time = _CP0_GET_COUNT() / 24000000;
        float freq = 1/time;
        drawString(10, 20, message);
        ssd1306_update();
        
    }
}

void drawLetter(int x, int y, char c){
    int i = 0;
    int j = 0;
    
    for(i = 0; i < 5; i ++){
        for(j = 0; j < 8; j++){
            ssd1306_drawPixel(x+i, y+j, (ASCII[c-32][i]&(0b1<<j))>>j);
        }
    
    }
    
}

void drawString(int x, int y, char * c){
    int posx = x;
    int posy = y;
    for(int i = 0; i < 50; i++){
        if(c[i] != '\0'){
            drawLetter(posx, posy, c[i]);
            if(posx + 5 > 128){
                posx = 0;
                posy = y + 8;
            }
            else{
                posx = posx + 5;
            }
            
        }
        else{
            continue;
        }
        
    }
    
}
