/*
 * File:   ADCInterrupt.c
 * Author: Hector
 *
 * Created on 2 de febrero de 2020, 11:07 PM
 */


#include <xc.h>
#include "ADCInterrupt.h"

void initADCconv(void) {
    ADCON0 = 0xB7;          //Control de ADC en el bit B5
    ADCON1 = 0x00;          //Lee el bit menos significativo
    PIE1 = 0x40;            //Habilita la interrupcion ADC
}
