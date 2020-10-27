v 20130925 2
C 53900 43100 1 90 0 input-1.sym
{
T 53600 43100 5 10 0 0 90 0 1
device=INPUT
T 53900 43600 5 10 1 1 270 0 1
net=LED0:1
}
C 54400 43100 1 90 0 input-1.sym
{
T 54100 43100 5 10 0 0 90 0 1
device=INPUT
T 54400 43600 5 10 1 1 270 0 1
net=LED1:1
}
C 54900 43100 1 90 0 input-1.sym
{
T 54600 43100 5 10 0 0 90 0 1
device=INPUT
T 54900 43600 5 10 1 1 270 0 1
net=LED2:1
}
N 56200 41400 56200 41200 4
C 56400 40300 1 90 0 led-3.sym
{
T 55750 41250 5 10 0 0 90 0 1
device=LED
T 56400 40300 5 10 0 0 0 0 1
color=red
T 56400 40300 5 10 0 0 0 0 1
pn=150060RS75000
T 56400 40300 5 10 0 0 0 0 1
footprint=0603
T 55850 40750 5 10 1 1 90 0 1
refdes=D883
}
C 56100 42200 1 270 0 input-1.sym
{
T 56400 42200 5 10 0 0 270 0 1
device=INPUT
T 56100 41700 5 10 1 1 90 0 1
net=LED_T:1
}
C 53500 45900 1 0 0 ledx3.sym
{
T 54750 46950 5 10 0 0 0 0 1
device=LEDx3
T 54550 46650 5 10 1 1 0 0 1
refdes=D880
T 53500 45900 5 10 0 0 0 0 1
pn=LTST-C19HE1WT
T 53500 45900 5 10 0 0 0 0 1
footprint=0606
}
C 54800 44500 1 90 0 resistor-x4.sym
{
T 53500 44800 5 10 0 0 90 0 1
device=RESISTOR_x4
T 54800 44500 5 10 0 0 90 0 1
footprint=0603_4
T 54800 44500 5 10 0 0 90 0 1
pn=YC164-JR-07510RL
T 53600 44700 5 10 1 1 90 0 1
refdes=R880
T 55000 44800 5 10 1 1 90 0 1
value=510
}
C 56300 39200 1 90 0 resistor-1.sym
{
T 55900 39500 5 10 0 0 90 0 1
device=RESISTOR
T 56300 39200 5 10 0 0 90 0 1
footprint=0603
T 56000 39400 5 10 1 1 90 0 1
refdes=R883
T 56500 39400 5 10 1 1 90 0 1
value=1.2 k
T 56300 39200 5 10 0 0 0 0 1
pn=RMCF0603JT1K20
}
C 56100 38700 1 0 0 gnd-1.sym
N 56200 39000 56200 39200 4
N 56200 40300 56200 40100 4
N 55000 45600 55000 45900 4
N 54700 45600 55000 45600 4
N 54700 45400 54700 45600 4
N 54400 45400 54400 45900 4
N 54100 45600 54100 45400 4
N 53100 44300 53100 45600 4
N 53100 45600 54100 45600 4
N 53800 45400 53800 45900 4
N 54300 44100 54400 44100 4
N 54400 44100 54400 44500 4
N 54700 44100 54800 44100 4
N 54700 44500 54700 44100 4
C 54200 47100 1 0 0 5V-plus-1.sym
N 54400 47100 54400 46900 4
C 52600 41400 1 0 0 5V-plus-1.sym
C 52700 38700 1 0 0 gnd-1.sym
N 52800 41400 52800 41200 4
C 53000 40300 1 90 0 led-3.sym
{
T 52350 41250 5 10 0 0 90 0 1
device=LED
T 53000 40300 5 10 0 0 0 0 1
color=green
T 53000 40300 5 10 0 0 0 0 1
pn=150060VS75000
T 53000 40300 5 10 0 0 0 0 1
footprint=0603
T 52450 40750 5 10 1 1 90 0 1
refdes=D882
}
C 52700 40100 1 270 0 resistor-1.sym
{
T 53100 39800 5 10 0 0 270 0 1
device=RESISTOR
T 52700 40100 5 10 0 0 270 0 1
footprint=0603
T 52700 40100 5 10 0 0 0 0 1
pn=RC0603FR-073K16L
T 53000 39900 5 10 1 1 270 0 1
refdes=R882
T 52500 39900 5 10 1 1 270 0 1
value=3.16 k
}
N 52800 40300 52800 40100 4
N 52800 39200 52800 39000 4
C 51800 38700 1 0 0 gnd-1.sym
N 51900 41400 51900 41200 4
C 52100 40300 1 90 0 led-3.sym
{
T 51450 41250 5 10 0 0 90 0 1
device=LED
T 52100 40300 5 10 0 0 0 0 1
color=green
T 52100 40300 5 10 0 0 0 0 1
pn=150060VS75000
T 52100 40300 5 10 0 0 0 0 1
footprint=0603
T 51550 40750 5 10 1 1 90 0 1
refdes=D881
}
C 51800 40100 1 270 0 resistor-1.sym
{
T 52200 39800 5 10 0 0 270 0 1
device=RESISTOR
T 51800 40100 5 10 0 0 270 0 1
footprint=0603
T 51800 40100 5 10 0 0 0 0 1
pn=RC0603JR-071K3L
T 52100 39900 5 10 1 1 270 0 1
refdes=R881
T 51600 39900 5 10 1 1 270 0 1
value=1.3 k
}
N 51900 40300 51900 40100 4
N 51900 39200 51900 39000 4
C 51700 41400 1 0 0 3.3V-plus-1.sym
N 53800 44100 54100 44100 4
N 54100 44100 54100 44500 4
N 53800 44100 53800 43900 4
N 53100 44300 53800 44300 4
N 53800 44300 53800 44500 4
N 54300 44100 54300 43900 4
N 54800 44100 54800 43900 4
C 58100 40300 1 90 0 led-3.sym
{
T 57450 41250 5 10 0 0 90 0 1
device=LED
T 58100 40300 5 10 0 0 0 0 1
color=red
T 58100 40300 5 10 0 0 0 0 1
pn=150060RS75000
T 58100 40300 5 10 0 0 0 0 1
footprint=0603
T 57550 40750 5 10 1 1 90 0 1
refdes=D884
}
C 58000 39000 1 90 0 resistor-1.sym
{
T 57600 39300 5 10 0 0 90 0 1
device=RESISTOR
T 58000 39000 5 10 0 0 90 0 1
footprint=0603
T 57700 39200 5 10 1 1 90 0 1
refdes=R884
T 58200 39200 5 10 1 1 90 0 1
value=20 k
T 58000 39000 5 10 0 0 0 0 1
pn=RMCF0603JT20K0
}
N 57900 38800 57900 39000 4
N 57900 40300 57900 39900 4
C 58300 41200 1 270 0 led-3.sym
{
T 58950 40250 5 10 0 0 270 0 1
device=LED
T 58300 41200 5 10 0 0 180 0 1
color=red
T 58300 41200 5 10 0 0 180 0 1
pn=150060RS75000
T 58300 41200 5 10 0 0 180 0 1
footprint=0603
T 58850 40750 5 10 1 1 270 0 1
refdes=D885
}
N 57900 40100 58500 40100 4
N 58500 40100 58500 40300 4
N 58500 41200 58500 41400 4
N 58500 41400 57900 41400 4
N 57900 41200 57900 41600 4
C 57800 42400 1 270 0 input-1.sym
{
T 58100 42400 5 10 0 0 270 0 1
device=INPUT
T 57800 41900 5 10 1 1 90 0 1
net=SHUNT_HIGH:1
}
C 58000 38000 1 90 0 input-1.sym
{
T 57700 38000 5 10 0 0 90 0 1
device=INPUT
T 58000 38500 5 10 1 1 270 0 1
net=SHUNT_LOW:1
}
N 55100 41400 55100 41200 4
C 55300 40300 1 90 0 led-3.sym
{
T 54650 41250 5 10 0 0 90 0 1
device=LED
T 55300 40300 5 10 0 0 0 0 1
color=red
T 55300 40300 5 10 0 0 0 0 1
pn=150060RS75000
T 55300 40300 5 10 0 0 0 0 1
footprint=0603
T 54750 40750 5 10 1 1 90 0 1
refdes=D886
}
C 55000 42200 1 270 0 input-1.sym
{
T 55300 42200 5 10 0 0 270 0 1
device=INPUT
T 55000 41700 5 10 1 1 90 0 1
net=XBEE_ASC:1
}
C 55200 39200 1 90 0 resistor-1.sym
{
T 54800 39500 5 10 0 0 90 0 1
device=RESISTOR
T 55200 39200 5 10 0 0 90 0 1
footprint=0603
T 54900 39400 5 10 1 1 90 0 1
refdes=R886
T 55400 39400 5 10 1 1 90 0 1
value=1.2 k
T 55200 39200 5 10 0 0 0 0 1
pn=RMCF0603JT1K20
}
C 55000 38700 1 0 0 gnd-1.sym
N 55100 39000 55100 39200 4
N 55100 40300 55100 40100 4
