/** 
 * 
 * July 10, 2020
 * LV_Embedded
 * nguyenlamvien0110@gmail.com 
 * https://github.com/vien20010
 * 
 **/

#include "ADCx.h"

uint16_t uhADCxConvertedValue = 0;

/**
  * @brief  ADC3 channel07 with DMA configuration
  * @note   This function Configure the ADC peripheral  
            1) Enable peripheral clocks
            2) DMA2_Stream0 channel2 configuration
            3) Configure ADC Channel7 pin as analog input
            4) Configure ADC3 Channel7 
  * @param  None
  * @retval None
  */

void ADC_Config(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable ADCx, GPIO clocks */

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
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADCxx, &ADC_InitStructure);

  /* ADC Common Init **********************************************************/
  /*     ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure); */

  /* ADC3 Init ****************************************************************/
  /*     ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADCxx, &ADC_InitStructure); */

  /* ADC3 regular channel7 configuration **************************************/
  ADC_RegularChannelConfig(ADCxx, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);

  /* Enable ADC3 */
  ADC_Cmd(ADCxx, ENABLE);
}

/**
  * @brief  ADC3 channel07 with DMA configuration
  * @note   This function Configure the ADC peripheral  
            1) Enable peripheral clocks
            2) DMA2_Stream0 channel2 configuration
            3) Configure ADC Channel7 pin as analog input
            4) Configure ADC3 Channel7 
  * @param  None
  * @retval None
  */

void DMA_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;
  /* Enable DMA clock */
  RCC_AHBPeriphClockCmd(ADCx_DMA_CLK, ENABLE);

  /* DMA1 channel7 configuration------------------ */
  DMA_DeInit(ADCx_DMA_CHANNELx);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADCx_DR_ADDRESS;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&uhADCxConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(ADCx_DMA_CHANNELx, &DMA_InitStructure);

  /* Enable DMAx Channel x */
  DMA_Cmd(ADCx_DMA_CHANNELx, ENABLE);



  /* DMA2 Stream0 channel2 configuration **************************************/
  /*     DMA_InitStructure.DMA_Channel = DMA_CHANNELx;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADCx_DR_ADDRESS;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&uhADCxConvertedValue;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA_STREAMx, &DMA_InitStructure);
    DMA_Cmd(DMA_STREAMx, ENABLE); */

  /* Enable DMA request after last transfer (Single-ADC mode) */
  /* ADC_DMARequestAfterLastTransferCmd(ADCxx, ENABLE); */

  /* Enable ADC3 DMA */
  ADC_DMACmd(ADCxx, ENABLE);

    /* Enable ADC1 reset calibration register */
  ADC_ResetCalibration(ADCxx);

  /* Check the end of ADC1 reset calibration register */
  while (ADC_GetResetCalibrationStatus(ADC1))
  {}

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while (ADC_GetCalibrationStatus(ADC1))
  {}

  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
