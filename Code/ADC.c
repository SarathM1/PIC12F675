/*
 * File:   project.c
 * Author: SARATH
 *
 * Created on 26 January, 2016, 10:04 PM
 */
#include <xc.h>
#define LED GPIO1

void ADC_init()
{
    ADFM = 1;
    VCFG = 0;
    CHS1 = 0;
    CHS0 = 0;
    ADON = 1;
    
    ANSEL = 0X00; // Just clearing all default one's
    ANS0 = 1;
    ADCS2 = 1;
    ADCS0 = 1;
}

int ADC_get()
{
    int value;
    GO_DONE = 1;
    while(!ADIF)
        continue;
    ADIF = 0;
    value = (ADRESH<<8) + ADRESL;
    return value;
}
void main(void) 
{
    TRISIO0 = 1;
    TRISIO1 = 0;
    CMCON = 0x07;
    OPTION_REG = 0X80;
    LED = 0;
    ADC_init();
    
    while(1)
    {
        if(ADC_get())
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
