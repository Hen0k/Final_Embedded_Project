#include "PIC_SETUP.h"

int ADC_VALUE = 0;
char digital_value = 0;
uint8_t recived = 0x00;
uint8_t msg = 0x00;


void __interrupt() ISR(void)
{
    // For SPI
//    if(PIR1bits.SSP1IF == 1)
//    {
//        LATC2 = !LATC2;
//        
//        SSP1BUF = msg;
//        while(!PIR1bits.SSP1IF);
//        PIR1bits.SSP1IF = 0;
//        if(SSP1CON1bits.WCOL) SSP1CON1bits.WCOL = 0;
//        PIR1bits.SSP1IF = 0;
//    }
    
    
    // For ADC
    if(PIR1bits.ADIF == 1)
    {
        LATC0 = 1;
        START_ADC();
        WAIT_ADC();
        ADC_VALUE = ADRESH;
        PIR1bits.ADIF = 0;
    }
    
    
    // For IOC
    if(INTCONbits.RBIF == 1)
    {
        LATC1 = !LATC1;
        digital_value = PORTBbits.RB5;
        INTCONbits.RBIF = 0;
    }
}