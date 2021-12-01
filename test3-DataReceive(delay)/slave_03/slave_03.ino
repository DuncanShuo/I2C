#include <Wire.h>

#define SLAVE_ADDRESS 0x12
#define SERIAL_BAUD 57600 

#define I2C_BUFFER_SIZE 32  
uint8_t i2cBuffer[I2C_BUFFER_SIZE];
uint8_t i2cBufferCnt = 0;
boolean dataPending = false;

void setup() {
  Wire.begin(SLAVE_ADDRESS);    // join I2C bus as a slave with address 1
  Wire.onReceive(receiveEvent); // register event

  Serial.begin(SERIAL_BAUD);
  Serial.println("I2C Slave.03 started\n");
}

void loop() {
  if (dataPending) {
    Serial.println("Receive Data:");
    for (int idx = 0; idx < i2cBufferCnt; idx++) Serial.print((char) i2cBuffer[idx]);
    Serial.println("\n");   
    dataPending = false;
  }
}

void receiveEvent(int count) {
  i2cBufferCnt = 0;
  while(Wire.available()) {
    i2cBuffer[i2cBufferCnt++] = Wire.read();
  }
  dataPending = true;
}
