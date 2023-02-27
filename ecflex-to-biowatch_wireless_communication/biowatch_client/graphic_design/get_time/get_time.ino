#include <Wire.h> // I2C library
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GC9A01A.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "wifi-network.h"

#define TFT_DC 4 // SDA
#define TFT_CS 5 // SCL
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

Adafruit_GC9A01A tft(TFT_CS, TFT_DC);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Network credentials
const char *ssid     = myssid;        // Enter your network SSID in wifi-network.h
const char *password = mypassword;    // Enter your network password in wifi-network.h

//Define an NTP client to get date and time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void setup() {
  Serial.begin(115200);
  
  // Connect the ESP8266 to the internet
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
  // Initialize the NTPClient
  timeClient.begin();

  // Adjust the time for your timezone in seconds
  timeClient.setTimeOffset(3600); // 3600 correspond to GMT +1

  // GC9A01 setup
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  delay(10);
}

void loop() {
  // Get the current time from the NTP server
  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);

  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime); 

  // Get the current date from the NTP server
  String weekDay = weekDays[timeClient.getDay()];
  Serial.print("Week Day: ");
  Serial.println(weekDay); 

  //Get a time structure
  struct tm *ptm = gmtime ((time_t *)&epochTime);

  // Get the hours, minutes or seconds separately
//  int currentHour = timeClient.getHours();
//  Serial.print("Hour: ");
//  Serial.println(currentHour);  
 
//  int currentMinute = timeClient.getMinutes();
//  Serial.print("Minutes: ");
//  Serial.println(currentMinute); 
 
//  int currentSecond = timeClient.getSeconds();
//  Serial.print("Seconds: ");
//  Serial.println(currentSecond);

  // Get the day of the month
  int monthDay = ptm -> tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  // Get the current month
  int currentMonth = ptm -> tm_mon + 1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  // Get the name of the month
  String currentMonthName = months[currentMonth-1];
  Serial.print("Month name: ");
  Serial.println(currentMonthName);

  // Get the current year
  int currentYear = ptm->tm_year+1900;
  Serial.print("Year: ");
  Serial.println(currentYear);

  //Print complete date
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  Serial.print("Current date: ");
  Serial.println(currentDate);

  Serial.println("");

  delay(2000);
}
