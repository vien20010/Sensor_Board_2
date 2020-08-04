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
#include "EC_Sensor.h"

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

float temp = 0,temp1=0,temp2=0;
float ECData = 0;
uint8_t txbuffer[20]="";

int main(void)
{
  Systick_Configuration();
  TIM4_Config();
  USART_Config();
  DMA_Config();
  ADC_Config();

  while (1)
  {
		uint16_t crc = 0;

    temp = DS18B20_GetTemp();
    ECData = *(uhADCxConvertedValue+2)*2000/4096.0;
    ECData = ECData / (1+0.0185*(temp1 - 25.0));
    temp1=Get_Temp1Data();
    temp2=Get_Temp2Data();
		sprintf(txbuffer,"a%4.1f,%6.1f,%4.1f",7.5,ECData,temp1);
		DBG("\n strlen: %d \n",strlen(txbuffer));
		for (int i = 0; *(txbuffer + i) != '\0'; i++)
		{
			//if (*(txbuffer + i) == ' ')
				//*(txbuffer + i) = '0';
			crc += *(txbuffer + i);	
		}
		
		*(txbuffer+17)=(crc >>8) & 0xFF;
		*(txbuffer + 18) = (crc & 0xFF); 
		*(txbuffer +19)='z';
		*(txbuffer +20)='\0';
				DBG("%x\n",crc);
		DBG("%x\n",*(txbuffer + 17));
		DBG("%x\n",*(txbuffer + 18));
		DBG("%x\n",*(txbuffer + 19));
    DBG("EC = %f, temp = %f, temp1 = %f\n", ECData,temp,temp1);
		DBG("%s\n",txbuffer);
		RS485_PutString(USARTy,txbuffer,20);
		DBG("\n strlen: %d \n",strlen(txbuffer));
    SystickDelay_ms(1000);
    //uhADCxConvertedValue=ADC_GetConversionValue(ADCxx);
  }
}

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USARTy, (uint8_t)ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USARTy, USART_FLAG_TC) == RESET)
  {
  }

  return ch;
}
