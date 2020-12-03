#include "stm32f10x.h"

#define ADDR_NOOP        0
#define ADDR_DIGIT0      1
#define ADDR_DIGIT1      2
#define ADDR_DIGIT2      3
#define ADDR_DIGIT3      4
#define ADDR_DIGIT4      5
#define ADDR_DIGIT5      6
#define ADDR_DIGIT6      7
#define ADDR_DIGIT7      8
#define ADDR_DECODEMODE  9
#define ADDR_INTENSITY   10
#define ADDR_SCANLIMIT   11
#define ADDR_SHUTDOWN    12
#define ADDR_DISPLAYTEST 15


u8 MAX7219_Buffer[4][8] = {
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
};

static void delay(int i) {
	while (i) {
		i--;
	}
}

void SPI2_Init() {
 	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 
 	GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx; // Only write.
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;        // 
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; // MAX7219's CS pin need to control.
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);
 
	SPI_Cmd(SPI2, ENABLE);	
}

void MAX7219_Write(u8 addr, u8 value) {
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	SPI_I2S_SendData(SPI2, (addr<<8)|value);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
	delay(200); // Must delay.
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void MAX7219_Init() {
	SPI2_Init();
	MAX7219_Write(ADDR_DECODEMODE, 0);
	MAX7219_Write(ADDR_INTENSITY, 0);
	MAX7219_Write(ADDR_SCANLIMIT, 7);
	MAX7219_Write(ADDR_SHUTDOWN, 1);
	MAX7219_Write(ADDR_DISPLAYTEST, 0);
	MAX7219_Write(ADDR_NOOP, 0);
	MAX7219_Write(ADDR_NOOP, 0);
	MAX7219_Write(ADDR_NOOP, 0);
}

void MAX7219_SetBuffer(u8 addr, u8 value) {
	u8 i;
	u8 x10,x1;
	x10 = addr / 8;
	x1 = addr % 8;
	for (i=0;i<8;i++) {
		if (value&(0x80>>i)) {
			MAX7219_Buffer[x10][i] |= 0x80>>x1;
		} else {
			MAX7219_Buffer[x10][i] &= ~(0x80>>x1);
		}
	}
}

void MAX7219_Flush() {
	u8 i, j;
	for (i=0;i<8;i++) {
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		for (j=0;j<4;j++) {
			SPI_I2S_SendData(SPI2, ((ADDR_DIGIT0+i)<<8)|MAX7219_Buffer[j][i]);
			while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
		}
		delay(200); // Must delay.
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	}
}
