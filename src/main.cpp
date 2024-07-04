#include <Arduino.h>
#include "Wire.h"
#include "iic.h"
#include "ds3231.h"
#include "oled.h"
// put function declarations here:

void setup(){
  iic_setup();
  OLED_Init();
  OLED_Clear();
  uint8_t hello[] = "aSmartClock";
  OLED_ShowString(0,0,hello,16);
  delay(2000);
  
}

DateTImeStruct timeread;
void loop() {
  delay(1000);
  if(DS3231_gettime(&timeread)==0){
    Serial.println(timeread.second);
    OLED_Clear();
    OLED_ShowNum(0,0,timeread.hour,2,16);
    OLED_ShowChar(16,0,':',16);
    OLED_ShowNum(24,0,timeread.minute,2,16);
    OLED_ShowChar(40,0,':',16);
    OLED_ShowNum(48,0,timeread.second,2,16);
  }
}  
    

