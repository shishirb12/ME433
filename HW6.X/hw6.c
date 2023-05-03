#include "nu32dip.h"
#include "i2c_master_noint.h"

void switch_gp7(unsigned char val);
unsigned char read_Pin(unsigned char add, unsigned char reg);

int main(void){
    i2c_master_setup();
    i2c_master_start();
    i2c_master_send(0b01000000);
    i2c_master_send(0x00);
    i2c_master_send(0b00000001);
    i2c_master_stop();
    while(1){
        if(read_Pin(0b01000000, 0x09)){
            switch_gp7(0b0<<7);
        }
        else{
            switch_gp7(0b1<<7);
        }
        
    }
    
    
}

void switch_gp7(unsigned char val){
    i2c_master_start();
    i2c_master_send(0b01000000);
    i2c_master_send(0x0A);
    i2c_master_send(val);
    i2c_master_stop();
}

unsigned char read_Pin(unsigned char add, unsigned char reg){
    i2c_master_start();
    i2c_master_send(add); //write
    i2c_master_send(reg);
    i2c_master_restart();
    i2c_master_send(add|1); //read
    unsigned char rf = (i2c_master_recv());
    i2c_master_ack(1);
    i2c_master_stop();
    return (rf&0b00000001);
    
}