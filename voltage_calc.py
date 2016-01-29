from math import sin,pi,sqrt,fabs

t = 10					# Give time in ms
alpha = pi*t
alpha = alpha /10

x = sin(2*alpha)

y = pi - alpha + (x/2)
z = y/pi
z = fabs(z)
try:
	vrms = 230 * sqrt(z)
except Exception, e:
	vrms = 0
	print t,alpha,x,y,z
	print e
else:
	print round(vrms,2),"volt"
