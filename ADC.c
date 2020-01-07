#include "ADC.h"


void INIT_ADC(void)
{
    ANSELA = 0x01;
//    TRISAbits.RA0=1;
    ADCON2bits.ADFM = 0;//select result format Left justified
    ADCON2bits.ACQT = 0b000;//select acquisition delay
    ADCON2bits.ADCS = 0b111; ///select conversion clock
    ADCON1 = 0x00;   
    ADCON0bits.ADON = 1;    //enabling ADC
}

void START_ADC(void)
{
    ADCON0bits.GO = 1;
}

void WAIT_ADC(void)
{
    while(ADCON0bits.GO==1);
}

