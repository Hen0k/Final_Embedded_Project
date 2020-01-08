/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_ADC_H
#define	XC_ADC_H

#include <xc.h>
//#include "PIC_SETUP.h" // include processor files - each processor file is guarded.  
int ADC_Value = 0;

void INIT_ADC(void);
void START_ADC(void);
void WAIT_ADC(void);

#endif	/* XC_HEADER_TEMPLATE_H */

