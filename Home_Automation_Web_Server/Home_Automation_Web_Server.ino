#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "SSID";
const char* password = "PASS";


String button = "<html><center><body><h2>Home Automation WebInterface</h2><p>Click on the respected button to switch the appliances:</p><h3>Lamp1</h3><input type=button onClick=\"parent.location='/lamp1/on'\" value='On'>              <input type=button onClick=\"parent.location='/lamp1/off'\" value='Off'><h3>Lamp2</h3><input type=button onClick=\"parent.location='/lamp2/on'\" value='On'>              <input type=button onClick=\"parent.location='/lamp2/off'\" value='Off'></center></body></html>";

WebServer server(80);


void handleRoot() // (192.168.1.1/)
{

  server.send(200, "text/html", button);
  
}

void handleNotFound() {
  
  String message = "File Not Found\n\n";
  message += "URI: "; // (192.168.1.1/page1/on)
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
 
}

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); //WiFi Station Mode
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) { //esp32.local/
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot); // esp32.local/

  server.on("/lamp1/on", []() {
    server.send(200, "text/html",button);
    digitalWrite(LED_BUILTIN,HIGH);
    
  });

  server.on("/lamp1/off", []() {
    server.send(200, "text/html",button);
    digitalWrite(LED_BUILTIN,LOW);
    
  });

  server.on("/lamp2/on", []() {
    server.send(200, "text/html",button);
    digitalWrite(LED_BUILTIN,HIGH);
    
  });

  server.on("/lamp2/off", []() {
    server.send(200, "text/html",button);
    digitalWrite(LED_BUILTIN,LOW);
    
  });


  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
