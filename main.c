/*
 * PB12(SPI2_NSS)  -> MAX7219 CS
 * PB13(SPI2_SCK)  -> MAX7219 CLK
 * PB14(SPI2_MISO) -> N/A
 * PB15(SPI2_MOSI) -> MAX7219 DIN
 */

#include "stm32f10x.h"
#include "max7219.h"

void delay(int i) {
	while (i) {
		i--;
	}
}

u8 font5x7[12][5] = {
	{0x00,0x7f,0x41,0x41,0x7f}, // 0
	{0x00,0x00,0x00,0x7f,0x00}, // 1
	{0x00,0x4f,0x49,0x49,0x79}, // 2
	{0x00,0x49,0x49,0x49,0x7f}, // 3
	{0x00,0x78,0x08,0x08,0x7f}, // 4
	{0x00,0x79,0x49,0x49,0x4f}, // 5
	{0x00,0x7f,0x49,0x49,0x4f}, // 6
	{0x00,0x40,0x40,0x40,0x7f}, // 7
	{0x00,0x7f,0x49,0x49,0x7f}, // 8
	{0x00,0x79,0x49,0x49,0x7f}, // 9
	{0x00,0x00,0x36,0x36,0x00}, // :
	{0x00,0x00,0x00,0x00,0x00}, // black
};

int main(void) {
	u8 i;
	MAX7219_Init();

	for (i=0;i<5;i++) {
		MAX7219_SetBuffer(0+i, font5x7[0][i]);
	}

	for (i=0;i<5;i++) {
		MAX7219_SetBuffer(5+i, font5x7[1][i]);
  	}

	for (i=0;i<5;i++) {
		MAX7219_SetBuffer(10+i, font5x7[2][i]);
	}

	for (i=0;i<5;i++) {
		MAX7219_SetBuffer(15+i, font5x7[3][i]);
	}
  
	MAX7219_Flush();
	while (1) {
		delay(10000000);
	}
}
