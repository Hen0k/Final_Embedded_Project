/*
 * File:   main.c
 * Author: henok
 *
 * Created on January 2, 2020, 2:52 PM
 */


#include "SPI.h"

void main(void) {
    setup();
    
    unsigned char data = 0x00;
    while(1)
    {
        data = SPI1_ExchangeByte(0x09);
        LATB = data;
    }
}
