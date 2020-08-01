/** 
 * 
 * July 10, 2020
 * LV_Embedded
 * nguyenlamvien0110@gmail.com 
 * https://github.com/vien20010
 * 
 **/

#ifndef _ADCx_H_
#define _ADCx_H_

#include "stm32f10x.h"

extern uint16_t uhADCxConvertedValue;

#define ADCxx                       ADC1
#define ADC_CHANNEL                 ADC_Channel_7
#define ADCx_CLK                    RCC_APB2Periph_ADC1
#define ADCx_CHANNEL_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ADCx_GPIO_PIN               GPIO_Pin_7
#define ADCx_GPIO_PORT              GPIOA
#define ADCx_DMA_CHANNELx           DMA1_Channel1
#define ADCx_DMA_STREAMx            DMA2_Stream0
#define ADCx_DR_ADDRESS             ((uint32_t)0x4001244C)
#define ADCx_DMA_CLK                RCC_AHBPeriph_DMA2


void ADC_Config(void);
void DMA_Config(void);

#endif
