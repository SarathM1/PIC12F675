tmr1 = 64500
#tmr1 = 55500

#tmr1 = 64535
#tmr1 = 55600


fclk = 4 * pow(10,6)
ftmr = fclk/4

fout = ftmr/(65535-tmr1)
tout = 1.0/fout
print fout,'hz or',round(tout*1000,2),'ms'