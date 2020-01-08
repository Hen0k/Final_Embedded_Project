#include "PIC_SETUP.h"


void SETUP()
{
    set_oscilators();
    init_pins();
    init_interrupts();
    INIT_ADC();
    SPI1_Initialize();
}


void set_oscilators()
{
     // SCS INTOSC; IRCF 8MHz_HFINTOSC/2; IDLEN disabled; 
//    OSCCON = 0x62;
//    OSCCONbits.IDLEN = 0;   // Device enters Sleep mode on SLEEP instruction
    OSCCONbits.IRCF = 6;    // Internal RC Oscillator HFINTOSC/2 ? (8 MHz)
//    OSCCONbits.OSTS = 0;    // Runnig with Internal OSC(HFINTOSC)
//    OSCCONbits.HFIOFS = 0;  // HFINTOSC frequency is not stable
    OSCCONbits.SCS = 2;     // System clock = Internal oscillator block

    // PRISD enabled; SOSCGO disabled; MFIOSEL disabled; 
//    OSCCON2 = 0x04;
//    OSCCON2bits.PLLRDY = 0;     //
//    OSCCON2bits.SOSCRUN = 0;    //
//    OSCCON2bits.MFIOSEL = 0;    //
//    OSCCON2bits.SOSCGO = 0;     //
    OSCCON2bits.PRISD = 1;      // Oscillator drive circuit on
//    OSCCON2bits.MFIOFS = 0;     //
//    OSCCON2bits.LFIOFS = 0;     //
    
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
    
    // Pin setup for the IOC
    TRISB5 = 1;
    ANSELBbits.ANSB5 = 0;
    
    // Pin setup for the ADC
    TRISAbits.RA0 = 1;
    ANSELAbits.ANSA0 = 1;;
    
    // Pin setup for Actuator (LED))
    TRISD5 = 0;
    ANSELDbits.ANSD5 = 0;
    
    // For Debugging
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    LATCbits.LATC0 = 0;
    LATCbits.LATC1 = 0;
    LATCbits.LATC2 = 0;
}

void init_interrupts()
{
    // SPI Interrupt
    PIR1bits.SSP1IF = 0;
    PIE1bits.SSP1IE = 1;
    
    // ADC Interrupt
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    
    // PORTB IOC 
    INTCONbits.RBIF = 0;
    INTCONbits.RBIE = 1;
    
    // Interrupt on change bit is set for PORTB5
    IOCBbits.IOCB5 = 1;
    
    // Interrupt Priority Disabled
    IPEN = 0;
    
    // Peripheral Interrupt Enabled
    INTCONbits.PEIE  =1;
    
    // Global Interrupt Enabled
    INTCONbits.GIE = 1;
}
