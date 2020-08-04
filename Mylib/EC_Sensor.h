/** 
 * 
 * July 29, 2020
 * LV_Embedded
 * nguyenlamvien0110@gmail.com 
 * https://github.com/vien20010
 * 
 **/

#ifndef _EC_SENSOR_
#define _EC_SENSOR_

#include "stm32f10x.h"
#include "ADCx.h"
#include <math.h>
#include "debug.h"

#define Vin                     3.3
#define K                       1.0
#define TemperatureCoef         0.019   

float Get_ECData(void);
float Get_Temp1Data(void);
float Get_Temp2Data(void);

#endif
