/* 
 * File:   7Segments_Multiplex.h
 * Author: Hector
 *
 * Created on 3 de febrero de 2020, 12:22 AM
 */

#ifndef __7SEGMENTS_MULTIPLEX_H_
#define	__7SEGMENTS_MULTIPLEX_H_

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)

#include <xc.h>

void SegMultiplex(void);

#endif	/* 7SEGMENTS_MULTIPLEX_H */

