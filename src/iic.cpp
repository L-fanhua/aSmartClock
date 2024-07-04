#include <Arduino.h>
#include "Wire.h"


void iic_setup(){
  Serial.begin(115200); 
  while(!Serial){} // Waiting for serial connection
 
  Serial.println();
  Serial.println("Start I2C scanner ...");
  Serial.print("\r\n");
  byte count = 0;
  Wire.setClock(3400000);
  Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0)
      {
      Serial.print("Found I2C Device: ");
      Serial.print(" (0x");
      Serial.print(i, HEX);
      Serial.println(")");
      count++;
      delay(1);
      }
  }
    Serial.print("\r\n");
  Serial.println("Finish I2C scanner");
  Serial.print("Found ");
  Serial.print(count, HEX);
  Serial.println(" Device(s).");
}
uint8_t iic_read(char *data_wr, uint8_t ReadAddr,char I2C_ADDR)
{
  uint8_t t = 200;
  uint8_t ret = 0;
  /* 1. 开始一次传输，设置I2C器件地址 */
  Wire.beginTransmission(I2C_ADDR);

  /* 2. 需要读出的位置 */
  Wire.write(ReadAddr);

  /* 3. 完成一次I2C通信，发送一个开始位(即重发码) */
  ret = Wire.endTransmission(false);

  /* 4. 开始一次读取，设置I2C器件地址，读取一个字节 */
  Wire.requestFrom(I2C_ADDR, 1);

  /* 5. 读出返回的值，成功读取后写入缓存变量处，读取失败返回失败码 */
  while (!Wire.available()) 
  {
    t--;
    delay(1); 
    if(t == 0)
    {
      return 1;
    }
  }
  *data_wr= Wire.read(); // receive a byte as character
  return ret;
}

uint8_t iic_write(uint8_t WriteAddr, char data_wr,char I2C_ADDR)
{
  /* 1. 开始一次传输，设置I2C器件地址 */
  Wire.beginTransmission(I2C_ADDR);

  /* 2. 需要写入的位置 */
  Wire.write(WriteAddr);

  /* 3. 需要写入的值 */
  Wire.write(data_wr);

  /* 4. 完成一次I2C通信，默认发送一个停止位 */
  return Wire.endTransmission();
}
