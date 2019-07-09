#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define BAUDRATE 115200

const char* ssid = "wifi_ssid";
const char* password = "wifi_password";

String server = "http://webservice/";

void wifiConnecting(){
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Menghubungkan ke Access Point");
    for(int c=0;c<3;c++){
      Serial.print(" .");
      delay(1000);  
    }
    Serial.println();
  }
}

void httpRequest(){
  Serial.println("--------------------HTTP Request--------------------");
  HTTPClient http;  
  http.begin(server);  
  int httpCode = http.GET();                                                       
  if (httpCode > 0) { 
    String payload = http.getString();
    Serial.println("HTTP Response Payload : ");
    Serial.println(payload); 
  }
  http.end(); 
  Serial.println();
}


void setup() {
  Serial.println("-------------------------------------------------");
  Serial.println("Setup NodeMCU Baudrate . . .");
  WiFi.begin(ssid, password);
  Serial.begin(BAUDRATE);
  Serial.println("Setup koneksi. . .");
  wifiConnecting();
  Serial.println("-------------------------------------------------");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { 
   httpRequest();
  }else
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("NodeMCU tidak terhubung ke Access Point");
    wifiConnecting();
  }
  Serial.println("\n");
  delay(2000);
}

