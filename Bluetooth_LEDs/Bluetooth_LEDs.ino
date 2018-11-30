//This code is modified by Sachin Soni(techiesms) for ESP32 tutorial Series
// ESP32 Series :- https://www.youtube.com/playlist?list=PLruzZCuhcsGNFXfOPUfNqdhP3-7_Hh7F0

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


String res = "";

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27,OUTPUT);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop()
{
  while (!SerialBT.available()); // Wait Until anything is coming from bluetooth client
  
  while (SerialBT.available()) // Read until the bluetooth client is sending.
  {
    char add = SerialBT.read();
    res = res + add;
    delay(1);
  }

 

  // Assigning Actions on particular conditions
  if (res == "T")
  {
    Serial.println("Connection Established!!!");
  }
  if (res == "1")
  {
    Serial.println("Turning ON 1st led");
    digitalWrite(12, HIGH);
  }
  if (res == "A")
  {
    Serial.println("Turning OFF 1st led");
    digitalWrite(12, LOW);
  }
  if (res == "2")
  {
    Serial.println("Turning ON 2nd led");
    digitalWrite(14, HIGH);
  }
  if (res == "B")
  {
    Serial.println("Turning OFF 2nd led");
    digitalWrite(14, LOW);
  }
  if (res == "3")
  {
    Serial.println("Turning ON 3rd led");
    digitalWrite(27, HIGH);
  }
  if (res == "C")
  {
    Serial.println("Turning OFF 3rd led");
    digitalWrite(27, LOW);
  }
  if (res == "4")
  {
    Serial.println("Turning ON 4th led");
    digitalWrite(13, HIGH);
  }
  if (res == "D")
  {
    Serial.println("Turning OFF 4th led");
    digitalWrite(13, LOW);
  }
  if (res == "9")
  {
    Serial.println("Turning ON all led");
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(27, HIGH);
    
  }
  if (res == "I")
  {
    Serial.println("Turning OFF all led");
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    digitalWrite(14, LOW);
    digitalWrite(27, LOW);
    
  }


  res = ""; // clearing the string.


}
