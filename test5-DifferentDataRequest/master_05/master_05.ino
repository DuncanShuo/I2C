#include <Wire.h>

#define SLAVE_ADDRESS 0x12
#define SERIAL_BAUD 57600 
#define DATA_SIZE 8
 
void setup()
{
  Wire.begin();
 
  Serial.begin(SERIAL_BAUD);
  Serial.println("I2C Master.05 started");
  Serial.println();
}
 
 
void loop()
{
  if (Serial.available()) {
    
    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write(Serial.read());
    delay(1);
    Wire.endTransmission();

    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.requestFrom(SLAVE_ADDRESS, DATA_SIZE);
    if (Wire.available()) {
      Serial.print("Data returned: ");
      while (Wire.available()) Serial.print((char) Wire.read());
      Serial.println();
    }
    Wire.endTransmission();
    while(Serial.available()) Serial.read();  // Clear the serial buffer, in this example, just request data from slave

  }
}
