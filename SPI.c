#include <pic18f43k22.h>
//#include "PIC_SETUP.h"
#include "SPI.h"


void SPI1_Initialize(void)
{
    //SPI setup
    SSP1STAT = 0x00;
//    SSP1STATbits.CKE = 1;
    SSP1CON1 = 0x24;
//    SSP1CON1bits.SSPEN = 1;
//    SSP1CON1bits.SSPM = 4;
    SSP1ADD = 0x00;
    SSP1CON2 = 0x00;
}


