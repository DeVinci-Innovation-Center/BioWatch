/////  Debugmode wemos d1 mini OTA programming  /////

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "debugmode"
#define STAPSK  "debugmode"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

bool debugMode = false;
//pinout wemos mini
/*
  D0=16;
  D1=5;
  D2=4;
  D3=0;
  D4=2;
  D5=14;
  D6=12;
  D7=13;
  D8=15;
  TX=1;
  RX=3;
*/
void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  pinMode(D4, OUTPUT);
  blinkD4();
  //try to enter debugmode
  for (byte t = 1; t <= 5; t++) {
    if (WiFi.waitForConnectResult() == WL_CONNECTED) {
      Serial.println("entering debug mode");
      debugMode = true;
      t = 5;
    }
    else {
      Serial.println("Retrying connection...");
      blinkD4();
      delay(1000);
    }
  }

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (debugMode == true) {
    Serial.println("entering debug mode");
    ArduinoOTA.handle();
    blinkD4();
  }
  if (debugMode == false) {
   
    //////////////////   INPUT MAIN CODE HERE   /////////////////

  }
}

void blinkD4() {
  digitalWrite(D4, LOW); delay(50);
  digitalWrite(D4, HIGH); delay(50);
}