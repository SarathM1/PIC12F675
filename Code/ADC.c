/*
 * File:   project.c
 * Author: SARATH
 *
 * Created on 26 January, 2016, 10:04 PM
 */
#include <xc.h>
#define LED GPIO1
#define _XTAL_FREQ 4000000
// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)


void ADC_init()
{
	ANSEL   = 0xA1;	     // Clear Pin selection bits
	
    TRISIO1  = 0;      // GP3 input, rest all output
	TRISIO0 = 1;	 // Make selected channel pins input
	
    ADFM = 1;
    ADON = 1;
}

int ADC_get()
{
    GO_nDONE = 1;                //Initializes A/D conversion
    while(GO_nDONE);             //Waiting for conversion to complete
    return (ADRESH<<8)+ADRESL;
}
void main(void) 
{
    ADC_init();
    
    while(1)
    {
        __delay_ms(10);
        if( ADC_get() == 1023 )
        {
            LED = 1;
        }
        else
        {
            LED = 0;
        }
        
    }
    return;
}
