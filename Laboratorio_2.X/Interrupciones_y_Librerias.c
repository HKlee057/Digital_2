/*
 * File:   Interrupciones_y_Librerias.c
 * Author: Hector Klee
 *
 * Created on 1 de febrero de 2020, 06:44 PM
 */
//******************************************************************************
//Librerias
//******************************************************************************
#include <xc.h>
#include <stdint.h>
#include "ADCInterrupt.h"
#include "7Segments_Multiplex.h"
//******************************************************************************
//Palabra de Configuracion
//******************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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
uint8_t ADC_val=0;          //Variable de ADC
uint8_t ADC_val_U=0;          //Variable de unidades en display
uint8_t MenSig = 0x0F;      //Variable para sacar los primeros 4 bits 
uint8_t ADC_val_D=0;          //Variable de decimales en display
//******************************************************************************
//Interrupcion
//******************************************************************************
void __interrupt() ISR(void){
    //Interrupcion por boton
    if (INTCONbits.RBIF == 1){                  //Verificar si ocurrio la interrupcion
       if (BUTTON_ADD == 1){                    //Verificar el boton preisonado y activar variable de comparacion
            add_button=1;               
            INTCONbits.RBIF = 0;                //Apaga bandera
        }
        if (add_button == 1 && BUTTON_ADD == 1){    //Si boton no sigue presionado y variable esta activa
            counter++;                              //Sumar 1 al valor del contador
            INTCONbits.RBIF = 0;                    //Limpiar bandera
        }
        if (BUTTON_SUB == 1){                       //Verifica el boton presionado
            sub_button=1;                           //Variable de comparacion
            INTCONbits.RBIF = 0;                    //Apaga bandera
        }
        if (sub_button == 1 && BUTTON_SUB == 1){    //Si boton no sigue presionado y variable esta activa
            counter--;                              //Restar 1 al valor de contador
            INTCONbits.RBIF = 0;                    //Limpiar bandera
        }     
    }
    //Interrupcion ADC
    if (PIR1bits.ADIF == 1){                    //Revisa si ocurrio la interrupcion
        PIR1bits.ADIF = 0;                      //Limpia la badera
        if (ADCON0bits.GO_nDONE == 0){          //Si la conversion termino realice lo siguiente
            ADC_val = ADRESH;                   //Guardar valor del ADRESH en una variable
            ADC_val_U = ADRESH & MenSig;        //Guardar los primeros cuatro bits
            ADC_val_D = ADRESH >> 4;            //Guardar los ultimos cuatro bits
        }
    }
    //Interrupcion Timer0
        if (INTCONbits.T0IF){                   //Revisa si ocurrio la interrupcion
        INTCONbits.T0IF = 0;                    //Limpia la badera
        TMR0 = 156;                             //Asigna valor para desbordar cada 0.2 ms
    }
}
//******************************************************************************
//Funcion Principal
//******************************************************************************
void main(void) {
    initPorts();               //Llama a funciones de inicio
    initADCconv();
    SegMultiplex();
    counter = counter;         //Iguala valores de contador
    while (1){                 //Loop infinto
        __delay_ms(90);        //Delay para aumentar puerto 
        PORTD = counter;       //Iguala el Puerto D a la variable del contador
        if(counter == ADC_val){
            PORTAbits.RA1 = 1;
        }
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
    OSCCON = 0X77;             //Control del oscilador
    INTCON = 0xE8;             //Habilita interrupciones
    IOCB = 0x03;               //Se habilita la interrupcion al cambio en puerto B en RB0 y RB2
    TMR0 = 156;                //Desborde cada 0.2 ms
    OPTION_REG = 0x81;         //Asignacion de prescaler al Timer0 a 1:4
}
