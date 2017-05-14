# 16F877MCU-KeypadMatrixInput-7SegOutput
Reads the built in PIC C Simulator IDE keypad matrix inputs and displays output onto a 7 segmet display.<br />
Compiler used: CCS C v.4<br />
Simulator used: PIC Simulator IDE v6.40<br />

They keypad is meant to be configured as following:

----RB3---RB2---RB1<br />
RB7--1-----2-----3<br />
RB6--4-----5-----6<br />
RB5--7-----8-----9<br />
RB4--F-----0-----E<br />

RB4:RB7 are used for RB interrupts (connected to 10k resistors),<br />
RB1:RB3 are logical "1" for reading inputs(connected to 1k resistors).<br />

A ports used for the 7 segment display.

What will (needs to) be included:

- Key pressed debounce
- More than one key pressed handling
- And more...
