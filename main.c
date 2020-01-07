/*
 * File:   main.c
 * Author: henok
 *
 * Created on January 2, 2020, 2:52 PM
 */


#include "PIC_SETUP.h"

void main(void) {
    SETUP();
    
    uint8_t recived = 0x00;
    uint8_t msg = 0x00;
    while(1)
    {
        recived = SPI1_ExchangeByte(msg);
//        LATB = recived;
        if(recived==0xFF){
            msg = 0x09;
            LATB = 0x03;
        }
        else if(recived==0x01){
            msg = 0x0A;
        }
        else if(recived==0x03){
            msg = 0x0B;
        }
        else{
            msg = 0x00;
        }
    }
}
