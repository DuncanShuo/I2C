#include <Wire.h>

#define SLAVE_ADDRESS 0x12
#define SERIAL_BAUD 57600 

#define I2C_BUFFER_SIZE 32  
uint8_t i2cBuffer[I2C_BUFFER_SIZE];
uint8_t i2cBufferCnt = 0;

void setup() {
  Wire.begin(SLAVE_ADDRESS);    // join I2C bus as a slave with address 1
  Wire.onRequest(requestEvent); // register event
 
  Serial.begin(SERIAL_BAUD);
  Serial.println("I2C Slave.04 started\n");
}

void loop() {
}

void requestEvent()
{
  Wire.write("Super169",8);
}
