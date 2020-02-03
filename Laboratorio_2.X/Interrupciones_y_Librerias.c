/*
 * File:   Interrupciones_y_Librerias.c
 * Author: Hector
 *
 * Created on 1 de febrero de 2020, 06:44 PM
 */
<<<<<<< Updated upstream

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

=======
//******************************************************************************
//Librerias
//******************************************************************************
#include <xc.h>
#include <stdint.h>
#include "ADCInterrupt.h"
//******************************************************************************
//Palabra de Configuracion
//******************************************************************************
>>>>>>> Stashed changes
// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
<<<<<<< Updated upstream

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000                  //Definición de frecuencia de oscilación
#define BUTTON_ADD PORTEbits.RB0           //Definición de bit en Puerto B con nombre coloquial
#define BUTTON_SUB PORTEbits.RB2           //Definición de bit en Puerto B con nombre coloquial

void main(void) {
     TRISA = 0x01;              //Definir Puerto A como entrada (Potenciometro)
     TRISB = 0x01;              //Definir Puerto B como entrada (Botones)
     TRISC = 0x00;              //Definir Puerto C como salida  (Displays)
     TRISD = 0x00;              //Definir Puerto D como salida  (Contador)
     TRISE = 0x01;              //Definir Puerto E como entrada (Alarma)
     ANSEL = 0x01;              //Datos analogicos
     ANSELH = 0x00;             //Datps digitales 
     OSCCON = 0X67;             //Control del oscilador
     INTCON = 0xFF;             //Habilita interrupciones
     PIE1 = 0x40;               //Habilita la Interrupcion ADC
     PIE2 = 0x40;               //Habilita la bandera de Interrupcion ADC
     IOCB = 0x03;               //Se habilita la interrupcion al cambio en puerto B en RB0 y RB2
     
     
    return;
}
=======
//******************************************************************************
//Definiciones extra
//******************************************************************************
#define _XTAL_FREQ 8000000                  //Definición de frecuencia de oscilación
#define BUTTON_ADD PORTBbits.RB1           //Definición de bit en Puerto B con nombre coloquial
#define BUTTON_SUB PORTBbits.RB2           //Definición de bit en Puerto B con nombre coloquial
//******************************************************************************
//Funciones prototipo
//******************************************************************************
void initPorts(void);
//******************************************************************************
//Variables
//******************************************************************************
uint8_t add_button=0;        //Variable para incrementar el valor del contador
uint8_t sub_button=0;        //Variable para decrementar el valor del contador
uint8_t counter=0;          //Variable de contador
//******************************************************************************
//Interrupcion
//******************************************************************************
void __interrupt() ISR(void){
    if (INTCONbits.RBIF == 1){
       if (BUTTON_ADD == 1){
            add_button=1;
            INTCONbits.RBIF = 0;
        }
        if (add_button == 1 && BUTTON_ADD == 0){
            add_button = 0;
            counter++;
            INTCONbits.RBIF = 0;
        }
        if (BUTTON_SUB == 1){
            sub_button=1;
            INTCONbits.RBIF = 0;
        }
        if (sub_button == 1 && BUTTON_SUB == 0){
            sub_button = 0;
            counter--;
            INTCONbits.RBIF = 0;
        }     
    }
}
//******************************************************************************
//Funcion Principal
//******************************************************************************
void main(void) {
    /*counter = 0;
    PORTD = 0;*/
    initPorts();
    while (1){
        counter = counter;
        __delay_ms(90);
        PORTD = counter;
    }
   
    return;
}
//******************************************************************************
//Funcion para inicializacion de puertos
//******************************************************************************
void initPorts(void){
    TRISA = 0x00;              //Definir Puerto A como salida (Alarma)
    TRISB = 0xFF;              //Definir Puerto B como entrada (Botones y potenciometro)
    TRISC = 0x00;              //Definir Puerto C como salida  (Display)
    TRISD = 0x00;              //Definir Puerto D como salida  (Contador)
    TRISE = 0x00;              //Definir Puerto E como salida (Por seguridad)
    ANSEL = 0x00;              //Datos analogicos
    ANSELH = 0x20;             //Datos analogicos en RB5 
    OSCCON = 0x77;             //Control del oscilador
    INTCON = 0xE8;             //Habilita interrupciones
    IOCB = 0x03;               //Se habilita la interrupcion al cambio en puerto B en RB0 y RB2
}
>>>>>>> Stashed changes
