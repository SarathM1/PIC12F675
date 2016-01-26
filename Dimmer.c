
unsigned int delay=0,adc_val;
unsigned char low,hi,i;
bit start;

unsigned int ADC_get()
{
    ADRESH=0x00;
    ADRESL=0x00;
    ADCON0 = 0x81;
    Delay_us(25);
    ADCON0.GO = 1;
    while(ADCON0.GO)continue;
    return (ADRESH<<8)+ADRESL;
}

void interrupt()
{
    if(INTF_bit)
    {
        while(!GP2_bit)continue;

        TMR1H         = hi;
        TMR1L         = low;
        T1CON         = 0x01;
        TMR1IF_bit= 0;

        while(!TMR1IF_bit)continue;

        T1CON         = 0x00;
        TMR1IF_bit= 0;
        GP1_bit=1;
        Delay_us(250);
        GP1_bit=0;
        start=1;
        INTF_bit=0;
    }
}

void main() 
{
    GPIO=0x00;
    TRISIO = 0x3D;
    CMCON=0x07;
    IOC=0x00;
    ANSEL = 0x51;
    ADCON0 = 0x81;
    OPTION_REG = 0x80;
    delay=0;
    T1CON         = 0x00;
    TMR1IF_bit    = 0;
    TMR1H         = 0xFC;
    TMR1L         = 0x18;
    TMR1IE_bit         = 0;
    INTEDG_bit = 1;
    INTCON =0x90;


    while(1)
    {

        GP1_bit=0;

        if(start){
            start=0;
            adc_val=0;

            for(i=0;i<31;i++){
                adc_val=adc_val+ADC_get();	// avaraging the values
            }
            
            delay = adc_val >> 5;
            delay = delay * 8.79;                // 64500 - 55500 =9000; 9000/1023 = 8.79
            delay = 55500 + delay;
            low = delay & 0xff;
            hi = delay >> 8;
        }
    }

}