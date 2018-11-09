// This code is modified by techiesms for ESP32 Series
// ESP32 Series :- https://www.youtube.com/watch?v=5eXhauyWPLc&list=PLruzZCuhcsGNFXfOPUfNqdhP3-7_Hh7F0


extern "C" // Extern C is used when we are using a funtion written in "C" language in a C++ code.
{

  uint8_t temprature_sens_read(); // This function is written in C language
}

uint8_t temprature_sens_read();

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Temperature in deg Celcius: ");

  // Convert raw temperature in F to Celsius degrees
  Serial.print((temprature_sens_read() - 32) / 1.8);
  Serial.println(" C");
  delay(5000);
}
