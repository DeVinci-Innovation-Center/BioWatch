#include <LMP91000.h>
#include <Wire.h>

// #define SDA D2 // SDA
// #define SCL D1 // SCL

LMP91000 pstat = LMP91000(); // Instancie l'objet Pstat. LMP91000() est la classe.


// double getTemp_Mode = getTemp();
// setMode(getTemp_Mode);

// Je dois regarder le taux du convertisseur numérique analogique pour 
float T1 = 15;  //°C
float Vtemp1 = 1440;   //mV
float T2 = 40;  //°C
float Vtemp2 = 1236;   //mV

void setup() {

  Wire.begin();
  Serial.begin(115200);
  delay(50);
  Serial.println("Initializing...");
  while (pstat.isReady() == false){
    delay(1000);
    Serial.println("Pstat not ready.");
  }
  Serial.println("LMP ready ");

//  pstat.setTwoLead();
//  Serial.println("Mode TwoLead ready ");

  // setTempSensor(uint8_t pin);
  pstat.getTemp();      ///////// Voir getTemp ligne 556 du .cpp /////////
  Serial.println("Mode getTemp ready ");

  delay(2000); // Warm-up time for the gas sensor
  }


void loop() {

  float Vtemp = analogRead(A0); // Put a wire between A0 and Vout.
  Vtemp = 3000.0 * Vtemp / 1023.0;
//float Vtemp = getTempSensor();
  Serial.print(Vtemp);
  Serial.println(" mV"); 
  delay(10);
  float Temp = (Vtemp - Vtemp1)*(T2 - T1) / (Vtemp2 - Vtemp1) + T1; // Cf datasheet page 16
  Serial.print(Temp);
  Serial.println(" °C");
  delay(1990);

}
