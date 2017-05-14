# 16F877MCU-KeypadMatrixInput-7SegOutput
Reads the built in PIC C Simulator IDE keypad matrix inputs and displays output onto a 7 segmet display.
Compiler used: CCS C v.4
Simulator used: PIC Simulator IDE v6.40

They keypad is meant to be configured as following:

<&nbsp><&nbsp><&nbsp><&nbsp><&nbsp>RB3<&nbsp><&nbsp>RB2<&nbsp><&nbsp>RB1<br />
RB7<&nbsp><&nbsp><&nbsp>1<&nbsp><&nbsp><&nbsp>2<&nbsp><&nbsp><&nbsp>3<br />
RB6<&nbsp><&nbsp><&nbsp>4<&nbsp><&nbsp><&nbsp>5<&nbsp><&nbsp><&nbsp>6<br />
RB5<&nbsp><&nbsp><&nbsp>7<&nbsp><&nbsp><&nbsp>8<&nbsp><&nbsp><&nbsp>9<br />
RB4<&nbsp><&nbsp><&nbsp>F<&nbsp><&nbsp><&nbsp>0<&nbsp><&nbsp><&nbsp><&nbsp>E<br />

RB4:RB7 are used for RB interrupts (connected to 10k resistors),<br />
RB1:RB3 are logical "1" for reading inputs(connected to 1k resistors).<br />

A ports used for the 7 segment display.

What will (needs to) be included:

- Key pressed debounce
- More than one key pressed handling
- And more...
