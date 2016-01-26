/*
 * File:   timer1_inter.c
 * Author: windows 7
 *
 * Created on January 26, 2016, 5:42 PM
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
#define LED GPIO0

int cntr = 1;
void interrupt ISR()
{
    if(TMR1IF)
    {
        cntr++;
        TMR1H = 0xFC;
        TMR1L = 0x18;
        TMR1IF = 0;
        
        if(cntr == 1000)
        {
            cntr = 0;
            LED = ~LED;
        }
    }
}

void timer_init()
{
    GIE = 1;
    PEIE = 1;
    TMR1IE = 1;
    
    TMR1IF = 0;
    TMR1H = 0XFC;
    TMR1L = 0X18;
    TMR1ON = 1;
}


void main(void) {
    TRISIO0 = 0;
    ANSEL = 0X00;
    CMCON = 0X07;
    timer_init();
    while(1);
    return;
}
