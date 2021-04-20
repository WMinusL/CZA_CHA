import matplotlib.pyplot as plt
import numpy as np
import math

Pi = 3.14159265358979323846
e = 23.4
Sin = np.sin
Cos = np.cos
ArcSin = np.arcsin
Abs = np.abs

name = input("Name:")
Lat = float(input("Lat:"))
South = float(input("South(0/1):"))

if(South == 1):
    d='N'
else:
    d='S'

def f(x, y):
    return 90 - Abs((1/Pi)*(180*
   ArcSin(Sin(2*Pi*((x - 1 - 79.73 + South*182.62)/365.24))*
      Sin((Pi*Lat)/180)*
            Sin((Pi*e)/180) + 
     Cos((Pi*Lat)/180)*Cos((1/180)*Pi*15*(y - 12))* 
      Cos(ArcSin(
        Sin(2*Pi*((x - 1 - 79.73 + South*182.62)/365.24))*
         Sin((Pi*e)/180)))))- 90)
         
x = np.linspace(1, 366, 1000)
y = np.linspace(0, 24, 1000)
 
X, Y = np.meshgrid(x, y)

plt.figure(figsize=(15,12))
C = plt.contour(X, Y, f(X, Y),levels=[0, 32.2, 58.8],colors='#DC3C32',linewidths=1.5)
Colors = ('#323270','#A0C8FF','#F5F5F5','#FAF050')

Cf = plt.contourf(X, Y, f(X, Y),levels=[-90,0, 32.2, 58.8,90],colors = Colors)
plt.xlabel(name+' '+str(Lat)+'°'+d)
plt.xticks([1,31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334],np.arange(1, 13, 1))
plt.yticks(np.arange(0, 24, 1))
plt.colorbar(Cf)
plt.grid(linestyle='dashed', linewidth=0.7,color='#000000')
plt.show()