//#include "PIC_SETUP.h"
#include "Interrupt_Service_Routine.h"


void __interrupt() ISR(void)
{
    // For SPI
    if(PIR1bits.SSP1IF == 1)
    {
        LATC2 = !LATC2;
        if(SSP1CON1bits.WCOL) SSP1CON1bits.WCOL = 0;
        recived = SSP1BUF;
        
        PIR1bits.SSP1IF = 0;
    }
    
    
    // For ADC
    if(PIR1bits.ADIF == 1)
    {
        LATC0 = !LATC0;
//        START_ADC();
        WAIT_ADC();
        ADC_VALUE = ADRESL;
        
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