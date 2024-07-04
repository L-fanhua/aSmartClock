#include "Wire.h"

void OLED_Init(void);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void) ;
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size2);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size2);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size2);