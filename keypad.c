#include <16F877.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP,PUT
#use delay(clock=20000000)
#use standard_io(B)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)

int higherNibble; int lowerNibble;

//how the keypad is imagined to look
//      RB3 RB2 RB1
// RB7   1   2   3
// RB6   4   5   6
// RB5   7   8   9
// RB4   F   0   E

char matrix[4][3] = {
                        {'1', '2', '3'},
                        {'4', '5', '6'},
                        {'7', '8', '9'},
                        {'F', '0', 'E'}
                     };

void determineHigherNibble(void)
{
   if (input_state(PIN_B7)) higherNibble = 7;
   else if (input_state(PIN_B6)) higherNibble = 6;
   else if (input_state(PIN_B5)) higherNibble = 5;
   else if (input_state(PIN_B4)) higherNibble = 4;
   else higherNibble = 0;
}

void debounce(void)
{
   switch (higherNibble)
   {
      case 7: while(input_state(PIN_B7)); break;
      case 6: while(input_state(PIN_B6)); break;
      case 5: while(input_state(PIN_B5)); break;
      case 4: while(input_state(PIN_B4)); break;
   }
}
int checkB3(void)
{
   output_low(PIN_B3);
   
   if (higherNibble == 7 && !input_state(PIN_B7)) return 3;
   else if (higherNibble == 6 && !input_state(PIN_B6)) return 3;
   else if (higherNibble == 5 && !input_state(PIN_B5)) return 3;
   else if (higherNibble == 4 && !input_state(PIN_B4)) return 3;
   else return 0;
}
int checkB2(void)
{
   output_low(PIN_B2);
   
   if (higherNibble == 7 && !input_state(PIN_B7)) return 2;
   else if (higherNibble == 6 && !input_state(PIN_B6)) return 2;
   else if (higherNibble == 5 && !input_state(PIN_B5)) return 2;
   else if (higherNibble == 4 && !input_state(PIN_B4)) return 2;
   else return 0;
}

char findChar(void)
{
   int row; int col;
   
   switch (higherNibble)
   {
      case 7: row = 0; break;
      case 6: row = 1; break;
      case 5: row = 2; break;
      case 4: row = 3; break;
   }
   
   switch (lowerNibble)
   {
      case 3: col = 0; break;
      case 2: col = 1; break;
      case 1: col = 2; break;
   }
   
   return matrix[row][col];
}

void showOnLCD(char charachter) //should be show on 7Segmet
{
   int output;
   
   switch (charachter)
   {
      case '1': output = 0b00000110; break;
      case '2': output = 0b01011011; break;
      case '3': output = 0b01001111; break;
      case '4': output = 0b01100110; break;
      case '5': output = 0b01101101; break;
      case '6': output = 0b01111101; break;
      case '7': output = 0b00000111; break;
      case '8': output = 0b01111111; break;
      case '9': output = 0b01101111; break;
      case '0': output = 0b00111111; break;
      case 'F': output = 0b01110001; break;
      case 'E': output = 0b01111001; break;
   }
   
   output_c(output);
}

#INT_RB
void interrupt(void)
{
   char charachter;
   
   higherNibble = 0; lowerNibble = 0;

   disable_interrupts(GLOBAL);
   disable_interrupts(INT_RB);

   determineHigherNibble();
   
   if (higherNibble)
   {
      lowerNibble = checkB3();
      if (!lowerNibble)
      {
         lowerNibble = checkB2();
         if (!lowerNibble) lowerNibble = 1;
      }
      
      output_high(PIN_B3);
      output_high(PIN_B2);
      
      debounce();
      
      charachter = findChar();
      
      showOnLCD(charachter);
   }
}

main ()
{
   set_tris_b(0xFE);
   set_tris_c(0x00);
   port_b_pullups(TRUE);
   
   while(1)
   {
      enable_interrupts(GLOBAL);
      enable_interrupts(INT_RB);
   }
}
