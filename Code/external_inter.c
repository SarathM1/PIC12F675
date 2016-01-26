/*
 * File:   external_inter.c
 * Author: windows 7
 *
 * Created on January 26, 2016, 12:20 PM
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
#define LED GPIO1
void interrupt ISR()
{
    if(INTF)
    {
        INTF = 0;
        LED = ~LED;
    }
}
void inter_init()
{
    GIE = 1;
    INTF = 0;
    INTE = 1;
}

void main(void) {
    TRISIO1 = 0;
    TRISIO2 = 1;
    GPIO1 = 1;
    
    ANSEL = 0x00;
    CMCON = 0x07;
    inter_init();
    while(1);
}
