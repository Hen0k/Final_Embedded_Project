#include "ADC.h"


void INIT_ADC(void)
{
//    ANSELA = 0x01;
//    TRISAbits.RA0=1;
//    ADCON2bits.ADFM = 0;//select result format Left justified
//    ADCON2bits.ACQT = 0b000;//select acquisition delay
//    ADCON2bits.ADCS = 0b000; ///select conversion clock
    ADCON0 = 0x01; 
    ADCON2 = 0x87;    //Conversion Clock = FRC and ACQT = 0
                        //Right shifted Formating
     
//    ADCON0 = 1;     //Channel = RA0 ---> analog input port
//    ADCON0bits.ADON = 1;    //enabling ADC
}

void START_ADC(void)
{
    ADCON0bits.GO = 1;
}

void WAIT_ADC(void)
{
    while(ADCON0bits.GO==1);
}

