
#include <pic18f43k22.h>
#include "PIC_SETUP.h"

void set_oscilators()
{
     // SCS INTOSC; IRCF 8MHz_HFINTOSC/2; IDLEN disabled; 
    OSCCON = 0x62;
    OSCCONbits.IDLEN = 0;   // Device enters Sleep mode on SLEEP instruction
    OSCCONbits.IRCF = 6;    // Internal RC Oscillator HFINTOSC/2 ? (8 MHz)
    OSCCONbits.OSTS = 0;    // Runnig with Internal OSC(HFINTOSC)
    OSCCONbits.HFIOFS = 0;  // HFINTOSC frequency is not stable
    OSCCONbits.SCS = 2;     // System clock = Internal oscillator block

    // PRISD enabled; SOSCGO disabled; MFIOSEL disabled; 
//    OSCCON2 = 0x04;
    OSCCON2bits.PLLRDY = 0;     //
    OSCCON2bits.SOSCRUN = 0;    //
    OSCCON2bits.MFIOSEL = 0;    //
    OSCCON2bits.SOSCGO = 0;     //
    OSCCON2bits.PRISD = 1;      // Oscillator drive circuit on
    OSCCON2bits.MFIOFS = 0;     //
    OSCCON2bits.LFIOFS = 0;     //
    
    // INTSRC disabled; PLLEN disabled; TUN 0; 
    OSCTUNE = 0x00;
}

void init_pins()
{
    LATA, LATB, LATC, LATD = 0x00;
    // Pin setup for SPI
    TRISC3 = 1;
    TRISC4 = 1;
    TRISC5 = 0;
    TRISA5 = 1;
    ANSELAbits.ANSA5 = 0;
    ANSELC = 0x00;
    
    // Pin setup to show Demo
    TRISB = 0x00;
    ANSELB = 0x00;
}

void init_interrupts()
{
    PIR1bits.SSP1IF = 0;
    PIE1bits.SSP1IE = 1;
    IPEN = 1;
    GIE = 1;
}

void __interrupt() SPI_ISR()
{
    if(PIR1bits.SSP1IF)
    {
        PIR1bits.SSP1IF = 0;
    }
}