#include <Wire.h>
 
#define SLAVE_ADDRESS 0x12
#define SERIAL_BAUD 57600 
 
byte data[4];
boolean dataReturned = false;

void setup() {
  Wire.begin(SLAVE_ADDRESS);    // join I2C bus as a slave with address 1
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
  
  Serial.begin(SERIAL_BAUD);
  Serial.println("I2C Slave.06 started\n");
}
 
void loop() {
  if (dataReturned) {
    dataReturned = false;
    Serial.print("Data received: ");
    for (int i = 0; i < 3; i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.print(" => ");
    Serial.println(data[3], HEX);
  }
}
 
void receiveEvent(int count) {
  if (Wire.available()) {
    for (int i = 0; i < 3; i++) data[i] = Wire.read();
    while (Wire.available()) Wire.read();
    dataReturned = false;
  }
}
 
void requestEvent()
{
  char op = (char) data[1];
  Serial.print("op = ");
  Serial.println(op);
  switch (op) {
    case 'A':
      data[3] = 'a';
      break;
    case 'O':
      data[3] = 'o';
      break;
    case 'X':
      data[3] = 'x';
      break;
    default:
      data[3] = 0xFF;
      break;
  }
  Wire.write(data, 4);
  dataReturned = true;
}
