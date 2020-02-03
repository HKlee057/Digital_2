/*
 * File:   7Segments_Multiplex.c
 * Author: Hector
 *
 * Created on 3 de febrero de 2020, 12:25 AM
 */


#include <xc.h>
#include <stdint.h>
#include "7Segments_Multiplex.h"

//Números a desplegar en display desde 0 a F
//uint8_t SEGMENT_MAP[16] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

uint8_t dual7segSetValue(uint8_t val_ADC, uint8_t val_Dis){
    switch(val_ADC){
        case 0x00:
            val_Dis = 0x3F;
            break;
        case 0x01:
            val_Dis = 0x06;
            break;
        case 0x02:
            val_Dis = 0x5B;
            break;
        case 0x03:
            val_Dis = 0x4F;
            break;  
        case 0x04:
            val_Dis = 0x66;
            break;
        case 0x05:
            val_Dis = 0x6D;
            break;
        case 0x06:
            val_Dis = 0x7D;
            break;
        case 0x07:
            val_Dis = 0x07;
            break;
        case 0x08:
            val_Dis = 0x7F;
            break;
        case 0x09:
            val_Dis = 0x6F;
            break;
        case 0x0A:
            val_Dis = 0x77;
            break;
        case 0x0B:
            val_Dis = 0x7C;
            break;  
        case 0x0C:
            val_Dis = 0x39;
            break;
        case 0x0D:
            val_Dis = 0x5E;
            break;
        case 0x0E:
            val_Dis = 0x79;
            break;
        case 0x0F:
            val_Dis = 0x71;
            break;            
    }
}
