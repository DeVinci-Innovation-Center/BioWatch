//////////////////////////////////////////////////////////////////////////
///          An Arduino script to receive the temperature &            ///
///    the glucose concentration values from the server (Server.py)    ///
//////////////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <string.h>
#include "wifi-network.h"

#ifndef STASSID
#define STASSID "SSID"                      // Enter your network SSID in wifi-network.h
#define STAPSK  "PASSWORD"                  // Enter your network password in wifi-network.h
#endif

const char* ssid     = STASSID;          
const char* password = STAPSK;           

String host = "172.21.72.179";             // Enter your domain.
const uint16_t port = 1235;                // Choose the port to use.

WiFiClient client;


void setup() {
  
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);                // Start the communication

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  IPAddress ip = WiFi.localIP();

  if (client.connect(host, port)) {
    Serial.println("connection succeeded");
  } else {
    Serial.println("connection failed");
    delay(5000);
    return;
  }
}


void loop() {
  
  if (WiFi.status() == WL_CONNECTED) {                // Check WiFi connection status
 
    HTTPClient http;                                  // Declare an object of class HTTPClient
    http.begin(client, "http://" + host +":" + port + "/get_data");        //Specify the request destination
    int httpCode = http.GET();                        // Request payload from the server
 
    if (httpCode > 0) {                               // The server has new payload available
 
      String payload = http.getString();              // Get the request response payload
      const char* payloadCStr = payload.c_str();      // Convert the string into a char. The char contains the temperature and the glucose concentration, separated by a semicolon
      char* pch = strtok((char*)payloadCStr, ";");    // Recover
      char* copy = strdup(pch);
      Serial.print("Temperature: ");
      Serial.println(copy);
      pch = strtok(NULL, ";");
      Serial.print("Glucose concentration: ");
      Serial.println(pch);
      
      // String token = payload.substring(0, payload.find(";"));
      // Serial.println(Temperature);
 
    }
    http.end();      //Close the connection
  }
  delay(5000);       // Send a request every 5 seconds
}
