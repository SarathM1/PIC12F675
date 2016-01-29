
#include <xc.h>
#define PWM GPIO1
#define _XTAL_FREQ 4000000
// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)


unsigned int delay=0,adc_val;
unsigned char low,hi,i;
bit start;

unsigned int ADC_get()
{
    ADRESH = 0x00;
    ADRESL = 0x00;
    ADCON0 = 0x81;
    __delay_us(25);
    GO_nDONE = 1;
    while(GO_nDONE);
    return (ADRESH<<8) + ADRESL;
}

void interrupt ISR()
{
    if(INTF)
    {	

        INTF=0;
        while(!GPIO2);

        TMR1H   = hi;
        TMR1L   = low;
        TMR1ON	= 1;
        TMR1IF 	= 0;

        while(!TMR1IF);

        TMR1ON  = 0;
        TMR1IF	= 0;
        
        PWM	= 1;
        __delay_us(250);
        PWM = 0;
        
        start=1;
    }
}

void adc_init()
{
	ANSEL 	= 0x51;			// ADC freq = FOSC/16; GP0 set as analog input pin(for ADC), rest all digital pins 
    ADCON0 	= 0x81;			// Right justified output, ADC on, ADC channel ANS0/GP0 , GO/nDONE = 0
}

void timer1_init()
{
	T1CON   = 0x00;			//  Tmr1 user Internal clock(FOSC/4), Prescalar 1:1
    TMR1IF  = 0;			
    TMR1H   = 0xFC;			// Timer to generate 1ms delay
    TMR1L   = 0x18;
    TMR1IE	= 0;			// Timer1 Interrupr enable
}

void extInterpt_init()
{
	INTEDG 	= 1;			// Interpt on rising edge on GP2/INT pin
    INTCON 	=0x90;			// GIE = 1, INTE = 1 (Ext Interpt)
}

void main() 
{
	GPIO 	= 0x00;
    TRISIO 	= 0x3D;			//	Making pin GP1 as output and all others input
    CMCON	= 0x07;			// Disabling comparator
    IOC 	= 0x00;			// Disabling Interrupt on change on all pins
    OPTION_REG = 0x80;		// Disable pull-up resistors, Interpt on falling edge on GP2/INT pin
    
    adc_init();
    timer1_init();
    extInterpt_init();

    delay 	= 0;
    
    while(1)
    {

        PWM=0;

        if(start){
            start=0;
            adc_val=0;

            for(i=0;i<31;i++)
            {
                adc_val=adc_val+ADC_get();	// avaraging the values
            }
            
            delay = adc_val >> 5;		// same as delay = adc_val/32
            
	        // The followin two steps are to ensure that tmr1 generated delay remains between 1ms and 10ms
	        // where 64500 => 1ms delay and 55500 => 10ms delay when put to TMR1H and TMR1L
	        // N.B : adc_val ranges from 0 to 1023, to understand clearly substitute adc_val = 0 and adc_val = 1023
	        
            delay = delay * 8.79;                // 64500 - 55500 =9000; 9000/1023 = 8.79 
            delay = 55500 + delay;
            
            low = delay & 0xff;
            hi = delay >> 8;
        }
    }

}