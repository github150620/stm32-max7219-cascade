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

int main(void) {
	u8 i=0;
	char a[30]="      1234567890        ";
	USART1_Init();
	MAX7219_Init();

	while (1) {
		MAX7219_Print(&a[i]);
		i++;
		i%=18;
		delay(10000000);
	}
}
