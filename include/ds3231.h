#include <Arduino.h>

void DS3231_test();
uint8_t DS3231_setTime(uint8_t hour , uint8_t min , uint8_t sec);
uint8_t DS3231_setDate(uint8_t year,uint8_t mon,uint8_t day);