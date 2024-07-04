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
  OLED_ShowChar(0,0,'s',16);
  //uint8_t hello[] = "Hello, World!";
  //if(1){OLED_ShowString(0,0,hello,16);}
  //
}

DateTImeStruct timeread;
void loop() {
  delay(1000);
  if(DS3231_gettime(&timeread)==0){
    Serial.println(timeread.second);
  //  OLED_Clear();
 //   OLED_ShowString(0,0,&timeread.second,16);
  //  OLED_ShowString(0,16,&timeread.minute,16);
  }
}  
    

