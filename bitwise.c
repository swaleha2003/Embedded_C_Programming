#include <stdio.h>
#include <stdint.h>

int main()
{
   //Initialize an 8-bit unsigned integer.
   uint8_t control_reg = 0b10100000;
   
   //Set (turn ON) Bit 3. Print the result in Hexadecimal.
   control_reg |=(1<<3);
   printf("control_reg_hex_value: %x\n",control_reg);
   
   //Clear (turn OFF) Bit 7. Print the result in Hexadecimal.
   control_reg &= ~(1<<7);
   printf("control_reg_hex_value: %x\n",control_reg);
   
   //Toggle Bit 0. Print the result in Hexadecimal.
   control_reg ^= (1<<0);
   printf("control_reg_hex_value: %x\n",control_reg);
   
}