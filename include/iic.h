#include "Wire.h"


void iic_setup();
uint8_t iic_read(char *data_wr, uint8_t ReadAddr,char I2C_ADDR);
uint8_t iic_write(uint8_t WriteAddr, char data_wr,char I2C_ADDR);