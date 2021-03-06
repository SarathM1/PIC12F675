/*
 * File:   Led.c
 * Author: windows 7
 *
 * Created on January 26, 2016, 12:01 PM
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#define _XTAL_FREQ 4000000
void main(void) {
    //TRISIO = 0x00;
    TRISIO0 = 0;
    
    while(1)
    {
        //GPIO = 0xff;
        GPIO0 = 1;
        __delay_ms(500);
        //GPIO0 = 0x00;
        GPIO0 = 0;
        __delay_ms(500);
    }
}
