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
	ADCON0 = 0x81;		 // Turn on the A/D Converter
	CMCON  = 0x07;		 // Shut off the Comparator, so that pins are available for ADC
	VRCON  = 0x00;	     // Shut off the Voltage Reference for Comparator
}


/*
 * Function Name: GetADCValue
 * Input(s) :     Channel name, it can be AN0, AN1, AN2 or AN3 only.
 *                Channel is selected according to the pin you want to use in
 *                the ADC conversion. For example, use AN0 for GP0 pin.
 *				  Similarly for GP1 pin use AN1 etc.
 * Output(s):     10 bit ADC value is read from the pin and returned.
 * Author:        M.Saeed Yasin   20-06-12
 */
unsigned int ADC_get()
{
    ADRESH=0x00;
    ADRESL=0x00;
    ADCON0 = 0x81;
    __delay_us(25);
    
    GO_nDONE = 1;                //Initializes A/D conversion
    while(GO_nDONE);             //Waiting for conversion to complete
    
    return (ADRESH<<8)+ADRESL;
}
void main(void) 
{
    GPIO=0x00;
    LED = 0;
    ADC_init();
    
    while(1)
    {
        __delay_ms(500);
        if(ADC_get())
        {
            LED = 0;
        }
        else
        {
            LED = 1;
        }
        
    }
    return;
}
