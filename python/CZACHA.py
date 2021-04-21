from matplotlib.pyplot import xlabel,xticks,yticks,figure,contour,contourf,colorbar,grid,show
from matplotlib import use
from numpy import sin,cos,arcsin,abs,linspace,meshgrid,arange
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QWidget

use("Qt5Agg")

Pi = 3.14159265358979323846
e = 23.4
Sin = sin
Cos = cos
ArcSin = arcsin
Abs = abs

name = input("Name:")
Lat = float(input("Lat:"))
South = float(input("South(0/1):"))

if(South == 1):
    d='N'
else:
    d='S'

def f(x, y):
    return 90 - Abs((1/Pi)*(180*
   ArcSin(Sin(2*Pi*((x  - 79.73 + South*182.62)/365.24))*
      Sin((Pi*Lat)/180)*
            Sin((Pi*e)/180) + 
     Cos((Pi*Lat)/180)*Cos((1/180)*Pi*15*(y - 12))* 
      Cos(ArcSin(
        Sin(2*Pi*((x  - 79.73 + South*182.62)/365.24))*
         Sin((Pi*e)/180)))))- 90)
print(f(1,11))      
x = linspace(1, 365.24, 1000)
y = linspace(0, 24, 1000)
 
X, Y = meshgrid(x, y)

figure(figsize=(15,12))
C = contour(X, Y, f(X, Y),levels=[0, 32.2, 58.8],colors='#DC3C32',linewidths=1.5)
Colors = ('#323270','#A0C8FF','#F5F5F5','#FAF050')

Cf = contourf(X, Y, f(X, Y),levels=[-90,0, 32.2, 58.8,90],colors = Colors)
xlabel(name+' '+str(Lat)+'°'+d)
xticks([1,32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335],arange(1, 13, 1))
yticks(arange(0, 24, 1))
colorbar(Cf)
grid(linestyle='dashed', linewidth=0.7,color='#000000')
show()
