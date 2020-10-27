v 20130925 2
C 29300 54500 1 180 0 connector5-1.sym
{
T 27500 53000 5 10 0 0 180 0 1
device=CONNECTOR_5
T 29200 52800 5 10 1 1 180 0 1
refdes=CONN271
T 29300 54500 5 10 0 0 180 0 1
pn=502352-0500
T 29300 54500 5 10 0 0 180 0 1
footprint=502352-05XX
}
C 29300 49200 1 180 0 connector5-1.sym
{
T 27500 47700 5 10 0 0 180 0 1
device=CONNECTOR_5
T 29200 47500 5 10 1 1 180 0 1
refdes=CONN270
T 29300 49200 5 10 0 0 180 0 1
pn=502352-0500
T 29300 49200 5 10 0 0 180 0 1
footprint=502352-05XX
}
C 21800 54900 1 0 0 quad-tvs-diode-unidirectional.sym
{
T 21800 54900 5 10 0 0 0 0 1
footprint=TSOT6L
T 21800 54900 5 10 0 0 0 0 1
pn=PESD5V0S4UD,115
T 21900 56200 5 10 1 1 0 0 1
device=QUAD_TVS
T 23000 56200 5 10 1 1 0 0 1
refdes=U261
}
N 19700 53700 27600 53700 4
C 26900 53200 1 270 0 gnd-1.sym
C 25500 55600 1 0 0 3.3V-plus-1.sym
C 24700 55600 1 0 0 5V-plus-1.sym
C 26300 54700 1 0 0 capacitor-1.sym
{
T 26500 55400 5 10 0 0 0 0 1
device=CAPACITOR
T 26500 55600 5 10 0 0 0 0 1
symversion=0.1
T 26300 54700 5 10 0 0 0 0 1
voltage=25 V
T 26300 54700 5 10 0 0 0 0 1
footprint=0603
T 26300 54700 5 10 0 0 0 0 1
pn=885012206072
T 26500 55200 5 10 1 1 0 0 1
refdes=C251
T 26500 54500 5 10 1 1 0 0 1
value=0.15 uF
}
C 24800 55400 1 270 0 resistor-1.sym
{
T 25200 55100 5 10 0 0 270 0 1
device=RESISTOR
T 24800 55400 5 10 0 0 270 0 1
footprint=0603
T 25100 55200 5 10 1 1 270 0 1
refdes=R265
T 24600 55200 5 10 1 1 270 0 1
value=DNP
}
N 23900 53400 27600 53400 4
N 27200 53100 27600 53100 4
N 25700 54500 25700 53400 4
N 24900 54500 24900 53400 4
N 27200 54900 27400 54900 4
N 27400 54900 27400 53100 4
N 26300 54900 26100 54900 4
N 26100 54900 26100 53400 4
N 25700 55600 25700 55400 4
N 24900 55600 24900 55400 4
N 20500 54000 27600 54000 4
N 20100 54300 27600 54300 4
N 18300 53700 17400 53700 4
N 15700 53400 18300 53400 4
N 18300 54300 17400 54300 4
C 21300 55600 1 270 0 gnd-1.sym
N 21800 55500 21600 55500 4
C 24000 55400 1 90 0 gnd-1.sym
N 23500 55500 23700 55500 4
N 23500 55900 24400 55900 4
N 23900 55100 23900 53400 4
N 23500 55100 23900 55100 4
N 24400 55900 24400 53700 4
N 21800 55100 21500 55100 4
N 21500 55100 21500 54300 4
N 21800 55900 20900 55900 4
N 20900 55900 20900 54000 4
C 25600 55400 1 270 0 resistor-1.sym
{
T 26000 55100 5 10 0 0 270 0 1
device=RESISTOR
T 25600 55400 5 10 0 0 270 0 1
footprint=0603
T 25600 55400 5 10 0 0 270 0 1
pn=CR0603-J/-000ELF
T 25900 55200 5 10 1 1 270 0 1
refdes=R282
T 25400 55200 5 10 1 1 270 0 1
value=0
}
C 17400 53800 1 180 0 io-1.sym
{
T 17200 53200 5 10 0 0 180 0 1
device=none
T 17100 53600 5 10 1 1 180 0 1
net=M_ABS:1
}
C 15700 53500 1 180 0 io-1.sym
{
T 15500 52900 5 10 0 0 180 0 1
device=none
T 15400 53300 5 10 1 1 180 0 1
net=M_EB:1
}
C 17400 54400 1 180 0 io-1.sym
{
T 17200 53800 5 10 0 0 180 0 1
device=none
T 17100 54200 5 10 1 1 180 0 1
net=M_EA:1
}
C 18300 53300 1 0 0 resistor-x4.sym
{
T 18600 54600 5 10 0 0 0 0 1
device=RESISTOR_x4
T 18300 53300 5 10 0 0 0 0 1
footprint=0603_4
T 18300 53300 5 10 0 0 0 0 1
pn=RAVF164DJT100R
T 18500 54500 5 10 1 1 0 0 1
refdes=R299
T 18600 53100 5 10 1 1 0 0 1
value=100
}
N 19200 54300 19700 54300 4
N 19700 54300 19700 53700 4
N 20100 54300 20100 53900 4
N 20100 53900 19500 53900 4
N 19500 53900 19500 53700 4
N 19500 53700 19200 53700 4
C 21500 61100 1 0 0 TJF1051.sym
{
T 24200 62300 5 10 0 1 0 0 1
footprint=SO8
T 21500 61100 5 10 0 0 0 0 1
pn=TJF1051T/3
T 21700 62500 5 10 1 1 0 0 1
device=TJF1051T/3
T 22900 62500 5 10 1 1 0 0 1
refdes=U251
}
N 27100 61300 23500 61300 4
N 23500 61600 26100 61600 4
C 22900 60300 1 0 0 5V-plus-1.sym
C 23000 58700 1 0 0 gnd-1.sym
N 23100 60300 23100 60100 4
N 23100 59200 23100 59000 4
C 21700 58700 1 0 0 gnd-1.sym
N 21800 60300 21800 60100 4
N 21800 59200 21800 59000 4
C 21600 60300 1 0 0 3.3V-plus-1.sym
C 20400 61400 1 90 0 3.3V-plus-1.sym
C 20900 61700 1 90 0 5V-plus-1.sym
C 20600 61400 1 270 0 gnd-1.sym
C 20100 62300 1 270 0 gnd-1.sym
N 20400 62200 21500 62200 4
N 20900 61900 21500 61900 4
N 20400 61600 21500 61600 4
N 20900 61300 21500 61300 4
C 25500 62600 1 90 0 dual-tvs-diode.sym
{
T 25500 62600 5 10 0 0 0 0 1
footprint=SOT23-3L
T 25500 62600 5 10 0 0 0 0 1
pn=ESDCAN24-2BLY
T 24200 62600 5 10 1 1 90 0 1
device=DUAL_TVS
T 24200 63700 5 10 1 1 90 0 1
refdes=U252
}
N 24500 62700 24500 61900 4
N 25300 62700 25300 62200 4
C 25000 64400 1 180 0 gnd-1.sym
N 24900 64100 24900 63900 4
N 28100 62200 23500 62200 4
N 23500 61900 28100 61900 4
C 29800 62400 1 180 0 connector2-1.sym
{
T 29600 61400 5 10 0 0 180 0 1
device=CONNECTOR_2
T 29800 62400 5 10 0 0 0 0 1
footprint=SOLDER_WIRE_x2
T 29800 61600 5 10 1 1 180 0 1
refdes=CONN260
}
C 27100 61200 1 0 0 output-1.sym
{
T 27200 61500 5 10 0 0 0 0 1
device=OUTPUT
T 27300 61400 5 10 1 1 0 0 1
net=CAN_RX:1
}
C 26900 61700 1 180 0 input-1.sym
{
T 26900 61400 5 10 0 0 180 0 1
device=INPUT
T 26400 61700 5 10 1 1 0 0 1
net=CAN_TX:1
}
C 24300 60600 1 0 0 resistor-1.sym
{
T 24600 61000 5 10 0 0 0 0 1
device=RESISTOR
T 24300 60600 5 10 0 0 0 0 1
footprint=0603
T 24500 60900 5 10 1 1 0 0 1
refdes=R260
T 24500 60400 5 10 1 1 0 0 1
value=DNP
}
N 25200 60700 25400 60700 4
N 25400 60700 25400 61900 4
N 24300 60700 24100 60700 4
N 24100 60700 24100 62200 4
C 21600 60100 1 270 0 capacitor-1.sym
{
T 22300 59900 5 10 0 0 270 0 1
device=CAPACITOR
T 22500 59900 5 10 0 0 270 0 1
symversion=0.1
T 21600 60100 5 10 0 0 270 0 1
voltage=25 V
T 21600 60100 5 10 0 0 270 0 1
footprint=0603
T 21600 60100 5 10 0 0 270 0 1
pn=885012206072
T 22100 59900 5 10 1 1 270 0 1
refdes=C253
T 21400 59900 5 10 1 1 270 0 1
value=0.15 uF
}
C 22900 60100 1 270 0 capacitor-1.sym
{
T 23600 59900 5 10 0 0 270 0 1
device=CAPACITOR
T 23800 59900 5 10 0 0 270 0 1
symversion=0.1
T 22900 60100 5 10 0 0 270 0 1
voltage=25 V
T 22900 60100 5 10 0 0 270 0 1
footprint=0603
T 22900 60100 5 10 0 0 270 0 1
pn=885012206072
T 23400 59900 5 10 1 1 270 0 1
refdes=C254
T 22700 59900 5 10 1 1 270 0 1
value=0.15 uF
}
C 21800 49600 1 0 0 quad-tvs-diode-unidirectional.sym
{
T 21800 49600 5 10 0 0 0 0 1
footprint=TSOT6L
T 21800 49600 5 10 0 0 0 0 1
pn=PESD5V0S4UD,115
T 21900 50900 5 10 1 1 0 0 1
device=QUAD_TVS
T 23000 50900 5 10 1 1 0 0 1
refdes=U265
}
N 17700 48400 27600 48400 4
C 26900 47900 1 270 0 gnd-1.sym
C 25500 50300 1 0 0 3.3V-plus-1.sym
C 24700 50300 1 0 0 5V-plus-1.sym
C 26300 49400 1 0 0 capacitor-1.sym
{
T 26500 50100 5 10 0 0 0 0 1
device=CAPACITOR
T 26500 50300 5 10 0 0 0 0 1
symversion=0.1
T 26300 49400 5 10 0 0 0 0 1
voltage=25 V
T 26300 49400 5 10 0 0 0 0 1
footprint=0603
T 26300 49400 5 10 0 0 0 0 1
pn=885012206072
T 26500 49900 5 10 1 1 0 0 1
refdes=C270
T 26500 49200 5 10 1 1 0 0 1
value=0.15 uF
}
C 24800 50100 1 270 0 resistor-1.sym
{
T 25200 49800 5 10 0 0 270 0 1
device=RESISTOR
T 24800 50100 5 10 0 0 270 0 1
footprint=0603
T 25100 49900 5 10 1 1 270 0 1
refdes=R270
T 24600 49900 5 10 1 1 270 0 1
value=DNP
}
N 23900 48100 27600 48100 4
N 27200 47800 27600 47800 4
N 25700 49200 25700 48100 4
N 24900 49200 24900 48100 4
N 27200 49600 27400 49600 4
N 27400 49600 27400 47800 4
N 26300 49600 26100 49600 4
N 26100 49600 26100 48100 4
N 25700 50300 25700 50100 4
N 24900 50300 24900 50100 4
N 18900 48700 27600 48700 4
N 16600 49000 27600 49000 4
N 9700 48400 16800 48400 4
N 8000 48700 18000 48700 4
N 15700 49000 9700 49000 4
C 21300 50300 1 270 0 gnd-1.sym
N 21800 50200 21600 50200 4
C 24000 50100 1 90 0 gnd-1.sym
N 23500 50200 23700 50200 4
N 23500 50600 24400 50600 4
N 23900 49800 23900 48100 4
N 23500 49800 23900 49800 4
N 24400 50600 24400 48400 4
N 21800 49800 21500 49800 4
N 21500 49800 21500 49000 4
N 21800 50600 20900 50600 4
N 20900 50600 20900 48700 4
C 25600 50100 1 270 0 resistor-1.sym
{
T 26000 49800 5 10 0 0 270 0 1
device=RESISTOR
T 25600 50100 5 10 0 0 270 0 1
footprint=0603
T 25600 50100 5 10 0 0 270 0 1
pn=CR0603-J/-000ELF
T 25900 49900 5 10 1 1 270 0 1
refdes=R71
T 25400 49900 5 10 1 1 270 0 1
value=0
}
C 9700 48500 1 180 0 io-1.sym
{
T 9500 47900 5 10 0 0 180 0 1
device=none
T 9400 48300 5 10 1 1 180 0 1
net=SENSE2:1
}
C 8000 48800 1 180 0 io-1.sym
{
T 7800 48200 5 10 0 0 180 0 1
device=none
T 7700 48600 5 10 1 1 180 0 1
net=SENSE1:1
}
C 9700 49100 1 180 0 io-1.sym
{
T 9500 48500 5 10 0 0 180 0 1
device=none
T 9400 48900 5 10 1 1 180 0 1
net=SENSE0:1
}
C 20100 49200 1 90 0 resistor-1.sym
{
T 19700 49500 5 10 0 0 90 0 1
device=RESISTOR
T 20100 49200 5 10 0 0 90 0 1
footprint=0603
T 19800 49400 5 10 1 1 90 0 1
refdes=R272
T 20300 49400 5 10 1 1 90 0 1
value=DNP
}
C 19200 49200 1 90 0 resistor-1.sym
{
T 18800 49500 5 10 0 0 90 0 1
device=RESISTOR
T 19200 49200 5 10 0 0 90 0 1
footprint=0603
T 18900 49400 5 10 1 1 90 0 1
refdes=R273
T 19400 49400 5 10 1 1 90 0 1
value=DNP
}
N 20000 49200 20000 49000 4
N 19100 49200 19100 48700 4
C 16800 48300 1 0 0 resistor-1.sym
{
T 17100 48700 5 10 0 0 0 0 1
device=RESISTOR
T 16800 48300 5 10 0 0 0 0 1
footprint=0603
T 17000 48600 5 10 1 1 0 0 1
refdes=R274
T 17000 48100 5 10 1 1 0 0 1
value=100
T 16800 48300 5 10 0 0 0 0 1
pn=RMCF0603JT100R
}
C 18000 48600 1 0 0 resistor-1.sym
{
T 18300 49000 5 10 0 0 0 0 1
device=RESISTOR
T 18000 48600 5 10 0 0 0 0 1
footprint=0603
T 18200 48900 5 10 1 1 0 0 1
refdes=R276
T 18200 48400 5 10 1 1 0 0 1
value=100
T 18000 48600 5 10 0 0 0 0 1
pn=RMCF0603JT100R
}
C 15700 48900 1 0 0 resistor-1.sym
{
T 16000 49300 5 10 0 0 0 0 1
device=RESISTOR
T 15700 48900 5 10 0 0 0 0 1
footprint=0603
T 15900 49200 5 10 1 1 0 0 1
refdes=R275
T 15900 48700 5 10 1 1 0 0 1
value=100
T 15700 48900 5 10 0 0 0 0 1
pn=RMCF0603JT100R
}
C 19800 50300 1 0 0 3.3V-plus-1.sym
N 20000 50300 20000 50100 4
C 18900 50300 1 0 0 3.3V-plus-1.sym
N 19100 50300 19100 50100 4
C 15300 47200 1 90 0 resistor-1.sym
{
T 14900 47500 5 10 0 0 90 0 1
device=RESISTOR
T 15300 47200 5 10 0 0 90 0 1
footprint=0603
T 15000 47400 5 10 1 1 90 0 1
refdes=R277
T 15500 47400 5 10 1 1 90 0 1
value=DNP
}
C 14500 47200 1 90 0 capacitor-1.sym
{
T 13800 47400 5 10 0 0 90 0 1
device=CAPACITOR
T 13600 47400 5 10 0 0 90 0 1
symversion=0.1
T 14500 47200 5 10 0 0 90 0 1
footprint=0603
T 14000 47400 5 10 1 1 90 0 1
refdes=C277
T 14700 47400 5 10 1 1 90 0 1
value=DNP
}
C 15100 46700 1 0 0 gnd-1.sym
N 15200 47000 15200 47200 4
C 14200 46700 1 0 0 gnd-1.sym
N 14300 47000 14300 47200 4
C 13400 47200 1 90 0 resistor-1.sym
{
T 13000 47500 5 10 0 0 90 0 1
device=RESISTOR
T 13400 47200 5 10 0 0 90 0 1
footprint=0603
T 13100 47400 5 10 1 1 90 0 1
refdes=R278
T 13600 47400 5 10 1 1 90 0 1
value=DNP
}
C 12600 47200 1 90 0 capacitor-1.sym
{
T 11900 47400 5 10 0 0 90 0 1
device=CAPACITOR
T 11700 47400 5 10 0 0 90 0 1
symversion=0.1
T 12600 47200 5 10 0 0 90 0 1
footprint=0603
T 12100 47400 5 10 1 1 90 0 1
refdes=C278
T 12800 47400 5 10 1 1 90 0 1
value=DNP
}
C 13200 46700 1 0 0 gnd-1.sym
N 13300 47000 13300 47200 4
C 12300 46700 1 0 0 gnd-1.sym
N 12400 47000 12400 47200 4
C 11500 47200 1 90 0 resistor-1.sym
{
T 11100 47500 5 10 0 0 90 0 1
device=RESISTOR
T 11500 47200 5 10 0 0 90 0 1
footprint=0603
T 11200 47400 5 10 1 1 90 0 1
refdes=R279
T 11700 47400 5 10 1 1 90 0 1
value=DNP
}
C 10700 47200 1 90 0 capacitor-1.sym
{
T 10000 47400 5 10 0 0 90 0 1
device=CAPACITOR
T 9800 47400 5 10 0 0 90 0 1
symversion=0.1
T 10700 47200 5 10 0 0 90 0 1
footprint=0603
T 10200 47400 5 10 1 1 90 0 1
refdes=C279
T 10900 47400 5 10 1 1 90 0 1
value=DNP
}
C 11300 46700 1 0 0 gnd-1.sym
N 11400 47000 11400 47200 4
C 10400 46700 1 0 0 gnd-1.sym
N 10500 47000 10500 47200 4
N 15200 48100 15200 48400 4
N 14300 48100 14300 48400 4
N 13300 48100 13300 48700 4
N 12400 48100 12400 48700 4
N 11400 48100 11400 49000 4
N 10500 48100 10500 49000 4
N 19200 53400 20500 53400 4
N 20500 53400 20500 54000 4