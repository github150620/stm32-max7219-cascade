/*
1.Connection:
  PB12(SPI2_NSS)  -> MAX7219 CS
  PB13(SPI2_SCK)  -> MAX7219 CLK
  PB14(SPI2_MISO) -> N/A
  PB15(SPI2_MOSI) -> MAX7219 DIN
2.Buffer
                              11  13  15  17  19  21  23  25  27  29  31
 Addr   0 1 2 3 4 5 6 7 8 9 10  12  14  16  18  20  22  24  26  28  30
      +-----------------------------------------------------------------+
MSB 7 | . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . |
    6 | . @ @ @ . . . . @ . . . . @ @ @ . . . @ @ @ . . . . . @ . . . . |
    5 | @ . . . @ . . @ @ . . . @ . . . @ . @ . . . @ . . . @ @ . . . . |
    4 | @ . . . @ . . . @ . . . . . . . @ . . . . . @ . . @ . @ . . . . |
    3 | @ . . . @ . . . @ . . . . . . @ . . . . @ @ . . @ . . @ . . . . |
    2 | @ . . . @ . . . @ . . . . . @ . . . . . . . @ . @ @ @ @ @ . . . |
    1 | @ . . . @ . . . @ . . . . @ . . . . @ . . . @ . . . . @ . . . . |
LSB 0 | . @ @ @ . . . @ @ @ . . @ @ @ @ @ . . @ @ @ . . . . . @ . . . . |
      +-----------------------------------------------------------------+
*/
#ifndef _MAX7219_H
#define _MAX7219_H

#include "stm32f10x.h"

void MAX7219_Init(void);
void MAX7219_Write(u8 addr, u8 value);
void MAX7219_SetBuffer(u8 addr, u8 value);
void MAX7219_Flush(void);
void MAX7219_Print(char *s);

#endif
