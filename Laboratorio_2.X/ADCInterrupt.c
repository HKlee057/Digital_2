/*
 * File:   ADCInterrupt.c
 * Author: Hector
 *
 * Created on 2 de febrero de 2020, 10:43 PM
 */


#include <xc.h>
#include "ADCInterrupt.h"
void initADInterrrupt(void) {
    ADCON0 = 0xB7;             //Control del ADC en el bit B5
    ADCON1 = 0x00;             //Lee el bit mas significativo
    PIE1 = 0x40;               //Habilita la Interrupcion ADC
    return;
}
