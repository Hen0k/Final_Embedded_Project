/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_PIC_SETUP_H
#define	XC_PIC_SETUP_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>
#include <pic18f43k22.h>
#include "CONFIGURATIONS.h"
#include "ADC.h"
#include "Interrupt_Service_Routine.h"
#include "SPI.h"
#include "ACTUATOR.h"

void SETUP(void);
void set_oscilators(void);
void init_pins(void);
void init_interrupts(void);

#endif	/* XC_HEADER_TEMPLATE_H */

