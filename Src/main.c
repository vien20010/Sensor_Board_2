#include <string.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "Systick.h"
#include "DS18B20.h"
#include "GPIO.h"
#include "Timerx.h"
#include "Uart.h"
#include "debug.h"
#include "ADCx.h"


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

float temp = 0;
uint8_t txbuffer[21];

int main(void)
{
	Systick_Configuration();
	TIM4_Config();
	USART_Config();
  DMA_Config();
	ADC_Config();
	
	while (1)
	{
		RS485_PutString(USARTy,"Vien dep trai",2);
		DBG("\nVien"); 
		temp=DS18B20_GetTemp();
    //uhADCxConvertedValue=ADC_GetConversionValue(ADCxx);
	}
}

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USARTy, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USARTy, USART_FLAG_TC) == RESET)
  {}

  return ch;
}
