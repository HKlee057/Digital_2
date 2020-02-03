/* 
 * File:   ADCInterrupt.h
 * Author: Hector
 *
 * Created on 2 de febrero de 2020, 11:04 PM
 */

#ifndef __ADCINTERRUPT_H_
#define	__ADCINTERRUPT_H_

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)

#include <xc.h>


void initADCconv(void);

#endif



