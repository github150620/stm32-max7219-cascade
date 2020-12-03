/*

Buffer:

 Addr   0   2   4   6    8   10  12  14   16  18  20  22   24  26  28  30
          1   3   5   7    9   11  13  15   17  19  21  23   25  27  29  31
      +--------------------------------------------------------------------+
MSB 7 | O O O O O O O O  O O O O O O O O  O O O O O O O O  O O O O O O O O |
    6 | O O O O O O O O  O O O O O O O O  O O O O O O O O  O O O O O O O O |
    5 | O O O O O O O O  O O O O O O O O  O O O O O O O O  O O O O O O O O |
    4 | O O O O O O O O  O O O O O O O O  O O O O O O O O  O O O O O O O O |
    3 | O O O O O O O O  O O O O O O O O  O O O O O O O O  O O O O O O O O |
    2 | O O O O O O O O  O O O O O O O O  O O O O O O O O  O O O O O O O O |
    1 | O O O O O O O O  O O O O O O O O  O O O O O O O O  O O O O O O O O |
LSB 0 | O O O O O O O O  O O O O O O O O  O O O O O O O O  O O O O O O O O |
      +--------------------------------------------------------------------+
*/
#ifndef _MAX7219_H
#define _MAX7219_H

#include "stm32f10x.h"

void MAX7219_Init(void);
void MAX7219_Write(u8 addr, u8 value);
void MAX7219_SetBuffer(u8 addr, u8 value);
void MAX7219_Flush(void);

#endif
