/** 
 * 
 * July 10, 2020
 * LV_Embedded
 * nguyenlamvien0110@gmail.com 
 * https://github.com/vien20010
 * 
 **/

#include "ADCx.h"

volatile uint16_t uhADCxConvertedValue[7];

/**
  * @brief  ADC1 Channel 7 PA7 Configuration
  * @param  None
  * @retval None
  */

void ADC_Config(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable ADCx, GPIO clocks */
  //RCC_ADCCLKConfig(RCC_PCLK2_Div8);
  RCC_APB2PeriphClockCmd(ADCx_CHANNEL_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(ADCx_CLK, ENABLE);

  /* Configure ADC1 Channel7 pin as analog input ******************************/
  GPIO_InitStructure.GPIO_Pin = ADCx_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(ADCx_GPIO_PORT, &GPIO_InitStructure);

  /* ADC1 Configuration */

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 7;
  ADC_Init(ADCxx, &ADC_InitStructure);

  /* ADCx regular channel7 configuration **************************************/
  ADC_RegularChannelConfig(ADCxx, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCxx, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCxx, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCxx, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCxx, ADC_Channel_4, 5, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCxx, ADC_Channel_5, 6, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCxx, ADC_Channel_7, 7, ADC_SampleTime_55Cycles5);
  ADC_DMACmd(ADC1, ENABLE);
  /* Enable ADCx */
  ADC_Cmd(ADCxx, ENABLE);

  /* Enable ADC1 reset calibration register */
  ADC_ResetCalibration(ADCxx);

  /* Check the end of ADC1 reset calibration register */
  while (ADC_GetResetCalibrationStatus(ADC1))
  {
  }

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while (ADC_GetCalibrationStatus(ADC1))
  {
  }

  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/**
  * @brief  DMA ADC Configuration
  * @param  None
  * @retval None
  */

void DMA_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;
  /* Enable DMA clock */
  RCC_AHBPeriphClockCmd(ADCx_DMA_CLK, ENABLE);

  /* DMA1 channel1 configuration------------------ */
  DMA_DeInit(ADCx_DMA_CHANNELx);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADCx_DR_ADDRESS;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)uhADCxConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 7;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(ADCx_DMA_CHANNELx, &DMA_InitStructure);

  /* Enable DMAx Channel x */
  DMA_Cmd(ADCx_DMA_CHANNELx, ENABLE);
}
