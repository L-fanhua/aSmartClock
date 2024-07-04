#include <Arduino.h>

typedef struct DateTImeStruct{
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t dayofmonth;
	uint8_t month;
	uint16_t year;
	uint8_t dayOfWeek;  /*Su=0 Mo=1 Tu=3 We=4 Th=5 Fr=6 Sa=7 */
}DateTime;

void DS3231_test();
uint8_t DS3231_setTime(uint8_t hour , uint8_t min , uint8_t sec);
uint8_t DS3231_setDate(uint8_t year,uint8_t mon,uint8_t day);

uint8_t DS3231_getdate(DateTime* ans);
uint8_t DS3231_gettime(DateTime* ans);