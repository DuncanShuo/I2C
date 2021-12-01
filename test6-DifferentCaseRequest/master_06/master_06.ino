#include <Wire.h>
 
#define SLAVE_ADDRESS 0x12
#define SERIAL_BAUD 57600 
#define DATA_SIZE 4

void setup()
{
  Wire.begin();
  
  Serial.begin(SERIAL_BAUD);
  Serial.println("I2C Master.06 started");
  Serial.println();
}

byte data[4];
  
void loop()
{
  if (Serial.available()) {
     
    Wire.beginTransmission(SLAVE_ADDRESS);
    for (int i = 0; i < 3; i++) {
      data[i] = Serial.read();
      delay(1);
    }
    Wire.write(data, 3);
    Wire.endTransmission();
    while(Serial.available()) Serial.read();  // Clear the serial buffer, in this example, just request data from slave
    
    Serial.print("Data sent: ");
    for (int i = 0; i < 3; i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }

    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.requestFrom(SLAVE_ADDRESS, DATA_SIZE);
    if (Wire.available()) {
      for (int i = 0; i < 4; i++) data[i] = Wire.read();
      while (Wire.available()) Serial.print((char) Wire.read());
      Serial.println();
    }
    Wire.endTransmission();

    Serial.print("Data returned: ");
    for (int i = 0; i < 4; i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
    Serial.println();

  }
}
