#include <Arduino.h>
#include "Wire.h"
#include "iic.h"
#include "ds3231.h"

#define DS3231_ADDRESS	        0x68 //I2C Slave address
#define	DS3231_ADDRESS_Write	0xD0
#define	DS3231_ADDRESS_Read		0xD1

/* DS3231 Registers. Refer Sec 8.2 of application manual */
#define DS3231_SEC_REG        0x00    // 秒
#define DS3231_MIN_REG        0x01    //
#define DS3231_HOUR_REG       0x02
#define DS3231_WDAY_REG       0x03
#define DS3231_MDAY_REG       0x04
#define DS3231_MONTH_REG      0x05
#define DS3231_YEAR_REG       0x06

#define DS3231_AL1SEC_REG     0x07
#define DS3231_AL1MIN_REG     0x08
#define DS3231_AL1HOUR_REG    0x09
#define DS3231_AL1WDAY_REG    0x0A

#define DS3231_AL2MIN_REG     0x0B
#define DS3231_AL2HOUR_REG    0x0C
#define DS3231_AL2WDAY_REG    0x0D

#define DS3231_CONTROL_REG          0x0E
#define DS3231_STATUS_REG           0x0F
#define DS3231_AGING_OFFSET_REG     0x0F
#define DS3231_TMP_UP_REG           0x11
#define DS3231_TMP_LOW_REG          0x12

#define EverySecond     0x01
#define EveryMinute     0x02
#define EveryHour       0x03

uint8_t DS3231_setTime(uint8_t hour , uint8_t min , uint8_t sec)
{
	uint8_t temp_H , temp_L;
	temp_L = hour%10;
	temp_H = hour/10;
	hour = (temp_H << 4) + temp_L;
	if(iic_write(DS3231_HOUR_REG,hour, DS3231_ADDRESS)) //set hour
		return 1;
	temp_L = min%10;
	temp_H = min/10;
	min = (temp_H << 4) + temp_L;
	if(iic_write(DS3231_MIN_REG,min, DS3231_ADDRESS)) //SET min
		return 2;	
	temp_L = sec%10;
	temp_H = sec/10;
	sec = (temp_H << 4) + temp_L;	
	if(iic_write(DS3231_SEC_REG,sec, DS3231_ADDRESS))		//SET sec
		return 3;
	return 0;
}
uint8_t DS3231_setDate(uint8_t year,uint8_t mon,uint8_t day)
{
	uint8_t temp_H , temp_L;
	temp_L = year%10;
	temp_H = year/10;
	year = (temp_H << 4) + temp_L;
	if(iic_write(DS3231_YEAR_REG,year, DS3231_ADDRESS)) //set year
	{
			printf("set year error\r\n");
			return 1;
	}	
	temp_L = mon%10;
	temp_H = mon/10;
	mon = (temp_H << 4) + temp_L;	
	if(iic_write(DS3231_MONTH_REG,mon, DS3231_ADDRESS)) //set mon
	{
		printf("set month error\r\n");
		return 2;
	}
	temp_L = day%10;
	temp_H = day/10;
	day = (temp_H << 4) + temp_L;		
	if(iic_write(DS3231_MDAY_REG,day, DS3231_ADDRESS)) //set day
	{
		printf("set day error\r\n");
		return 3;
	}
	return 0;
}


char data_buf = 0x00;
void DS3231_test() {
  Serial.print("TIME:");
   if(iic_read(&data_buf, 0x00, DS3231_ADDRESS) == 0)
    {
        Serial.print(data_buf, HEX);
        Serial.print(":");
        iic_read(&data_buf, 0x01, DS3231_ADDRESS);
        Serial.print(data_buf, HEX);
        Serial.print(":");
        iic_read(&data_buf, 0x02, DS3231_ADDRESS);
        Serial.print(data_buf, HEX);
        Serial.print(" week:");
        iic_read(&data_buf, 0x03, DS3231_ADDRESS);
        Serial.print(data_buf, HEX);
        Serial.print(" Date:");
        iic_read(&data_buf, 0x06, DS3231_ADDRESS);
        Serial.print(data_buf, HEX);
        Serial.print("-");
        iic_read(&data_buf, 0x05, DS3231_ADDRESS);
        Serial.print(data_buf, HEX);
        Serial.print("-");
        iic_read(&data_buf, 0x04, DS3231_ADDRESS);
        Serial.println(data_buf, HEX);

    }
    else
        Serial.print("Read DS3231 err \n");
}
static uint8_t bcdToDec(uint8_t byte)
{
	uint8_t temp_H , temp_L;
	temp_L = byte & 0x0f;
	temp_H = (byte & 0xf0) >> 4;
	return ( temp_H * 10 )+ temp_L;
}

uint8_t DS3231_gettime(DateTime* ans)
{
	char receive = 0;
	if(iic_read(&receive, 0x02, DS3231_ADDRESS))
		return 1;
	ans->hour = bcdToDec(receive);
	if(iic_read(&receive, 0x01, DS3231_ADDRESS))
		return 2;
	ans->minute = bcdToDec(receive);
	if(iic_read(&receive, 0x00, DS3231_ADDRESS))
		return 3;
	ans->second = bcdToDec(receive);
	return 0;
}

uint8_t DS3231_getdate(DateTime* ans)
{
	char receive = 0;
	if(iic_read(&receive, 0x06, DS3231_ADDRESS))
		return 1;
	ans->year = bcdToDec(receive) + 2000;
	if(iic_read(&receive, 0x05, DS3231_ADDRESS))
		return 2;
	ans->month = bcdToDec(receive);
	if( iic_read(&receive, 0x06, DS3231_ADDRESS))
		return 3;
	ans->dayofmonth = bcdToDec(receive);
	return 0;
}
