/*
 * File:   main.c
 * Author: henok
 *
 * Created on January 2, 2020, 2:52 PM
 */


#include "PIC_SETUP.h"

void main(void) {
    SETUP();
    
//    uint8_t recived = 0x00;
//    uint8_t msg = 0x00;
    while(1)
    {
        START_ADC();
//        recived = SPI1_ExchangeByte(msg);
//        LATB = recived;
        
        if(recived==0xFF){
            msg = 0x09;
//            LATB = 0x03;
        }
        else if(recived==0x01){
            msg = ADC_VALUE;
        }
        else if(recived==0x02){
            msg = digital_value;
        }
        else if(recived==0x03){
            Turn_OFF();
            msg = 0x00;
        }
        else if(recived==0x04){
            Turn_ON();
            msg = 0x00;
        }
        else{
            msg = 0x00;
        }
        SSP1BUF = msg;
    }
}
