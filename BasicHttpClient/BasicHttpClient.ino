/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *  
 *  Edited by techiesms for the tutorial Series on ESP32
 *
 */ 
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

WiFiMulti wifiMulti; // Declaring wifiMulti instance in WiFiMulti Class


void setup() {

    Serial.begin(115200);

    Serial.println();
    Serial.println();
    Serial.println();

    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush(); // flush is used to clear the stack
        delay(1000);
    }

    //using wifiMulti, we can add multiple WiFi credentials
    wifiMulti.addAP("SmS", "sms123458955");
    wifiMulti.addAP("SSID1", "PASSWORD1");
    wifiMulti.addAP("SSID2", "PASSWORD2"); 

}

void loop() {
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) 
    {

        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        
        http.begin("http://example.com/index.html"); //HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) 
        {  
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) 
            {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else 
        {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(5000);
}
