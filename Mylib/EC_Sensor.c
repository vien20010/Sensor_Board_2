/** 
 * 
 * July 29, 2020
 * LV_Embedded
 * nguyenlamvien0110@gmail.com 
 * https://github.com/vien20010
 * 
 **/

#include "EC_Sensor.h"

extern float temp;

float Get_ECData(void)
{
    float EC = 0, EC25 = 0;
    EC = *(uhADCxConvertedValue + 2) / 4096.0;
    EC *= Vin;
    EC25 = EC / (1 + TemperatureCoef * (temp - 25.0));
    return EC25;
}

float Get_Temp1Data(void)
{
    float Vtemp = 0;
    float Rt = 0, tempk = 0;
    Vtemp = (float)*(uhADCxConvertedValue + 4) * 3.3 / 4096.0;

    Rt = Vtemp / ((3.3 - Vtemp) / 10000.0);

    tempk = 1 / (log(Rt / 10000.0) / 3900.0 + 1 / (25 + 273.15)); 

    return tempk - 273.15;
}

float Get_Temp2Data(void)
{
    float Vtemp = 0;
    float Rt = 0, tempk = 0;
    Vtemp = (float)*(uhADCxConvertedValue + 4) * 3.3 / 4096.0;

    Rt = Vtemp / ((3.3 - Vtemp) / 10000.0);

    tempk = 1 / (log(Rt / 10000.0) / 3900.0 + 1 / (25 + 273.15)); 

    return tempk - 273.15;
}