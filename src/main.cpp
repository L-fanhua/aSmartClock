#include <Arduino.h>
#include "Wire.h"
#include "iic.h"
#include "ds3231.h"
#include "oled.h"
// put function declarations here:

void setup(){
  iic_setup();
  OLED_Init();
  OLED_Display_On();
  OLED_ShowNum(0,0,12,6,2);
  OLED_Display_On();
}

void loop() {
  delay(1000);
  DS3231_test();

}  
    

