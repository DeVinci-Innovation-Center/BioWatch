#include <LMP91000.h>
#include <Wire.h>

LMP91000 pStat = LMP91000();

int16_t opVolt = 3300; //milliVolts if working with a 3.3V device
uint8_t resolution = 10; //10-bits


void setup()
{
  Wire.begin();
  Serial.begin(115200);

delay(50);
  Serial.println("Initializing...");
  while (pStat.isReady() == false) {
    delay(1000);
    Serial.println("pStat not ready.");
  }
  Serial.println("LMP ready ");
  // MODECN: 0x03 (three lead amperometric mode)
  pStat.setThreeLead();
  Serial.println("Three lead Amperometric mode set");  

  // TIA: Whichever makes the best use of the ADC dynamic range. Try 0b00011011 (120 kOhm gain + 100 Ohm load)
  pStat.setGain(6);   // 0 => External resistance (default), 1 => 2.75 kOhm, 2 => 3.5 kOhm, 3 => 7 kOhm, 4 => 14 kOhm, 5 => 35 kOhm, 6 => 120 kOhm, 7 => 350 kOhm,
  pStat.setRLoad(3);  // 0 => 10 Ohm, 1 => 33 Ohm, 2 => 50 Ohm, 3 => 100 Ohm (default),

  // REFCN: This is the hardest bit. Set zero selection to 20 %
  // and bias polarity to positive
  pStat.setBias(11); // 0000 0% (default), 0001 1%, 0010 2%, 0011 4%, 0100 6%, 0101 8%, 0110 10%, 0111 12%, 1000 14%, 1001 16%, 1010 18%, 1011 20%, 1100 22%, 1101 24%
  // corresponding value for Vref = 2.5:   0,025    0,05       0,1     0,15      0,2      0,25      0,3       0,35      0,4       0,45      0,5       0,55      0,6

  pStat.setPosBias();
  //pStat.setNegBias();
  pStat.setIntRefSource();  // Set internal reference voltage source
    // The ref source and bias percentage should be chosen to a configuration that makes the voltage close to 1.05 Volts for the glucose and lactate pStats.
    // If you are not able to get this high, try running maximum (24 % and internal source).

  pStat.setIntZ(1);  // Internal zero selection set to 50%
  // The internal Zero is the voltage at the non-inverting pin of the TIA.
  // The internal zero can be programmed to be either 67%, 50% or 20%, of the supply, or the external reference voltage.

 // pStat.standby();
  delay(2000); //warm-up time for the gas sensor
  Serial.println("Setup complete");
}


void loop()
{ 
  runAmp(6, 0, 5000, 66, 5000, 250, 5000, 1000, 6); 
  delay(2000); 
}

void runAmp(uint8_t user_gain, int16_t pre_stepV, uint32_t quietTime, int16_t v1, uint32_t t1, int16_t v2, uint32_t t2, uint16_t samples, uint8_t range) {
  pStat.disableFET();
  pStat.setGain(user_gain);
  pStat.setRLoad(0);
  pStat.setIntRefSource();
  pStat.setIntZ(1);
  pStat.setThreeLead();
  pStat.setBias(0);

  //Print column headers
  String current = "";
  if (range == 12) current = "Current(pA)";        // picoamperes
  else if (range == 9) current = "Current(nA)";    // nanoamperes
  else if (range == 6) current = "Current(uA)";    // microamperes
  else if (range == 3) current = "Current(mA)";    // milliamperes
  else current = "CURRENT UNITS ERROR";

  Serial.println("Voltage(mV),Time(ms)," + current);

  int16_t voltageArray[3] = { pre_stepV, v1, v2 };
  uint32_t timeArray[3] = { quietTime, t1, t2 };

  //i = 0 is pre-step voltage
  //i = 1 is first step potential
  //i = 2 is second step potential
  for (uint8_t i = 0; i < 3; i++) {
    //For pre-step voltage
    uint32_t fs = timeArray[i]/samples;

    voltageArray[i] = determineLMP91000Bias(voltageArray[i]);

    if (voltageArray[i] < 0) pStat.setNegBias();
    else pStat.setPosBias();

//    unsigned long startTime = millis();
    pStat.setBias(abs(voltageArray[i]));
    while (true) {
      if (voltageArray[i] != 0) {
        Serial.print((uint16_t)(opVolt*TIA_BIAS[abs(voltageArray[i])]*(voltageArray[i]/abs(voltageArray[i]))));
    } else {
        Serial.print("0");
    }
      Serial.print(",");
      Serial.print(millis());
      Serial.print(",");
      Serial.println(pow(10, range) * pStat.getCurrent(pStat.getOutput(A0), opVolt / 1000.0, resolution));
      delay(fs);
      delay(1000);
    }
  }
  pStat.setBias(0);
}


signed char determineLMP91000Bias(int16_t voltage)
{
  signed char polarity = 0;
  if(voltage < 0) polarity = -1;
  else polarity = 1;
  
  int16_t v1 = 0;
  int16_t v2 = 0;
  
  voltage = abs(voltage);

  if(voltage == 0) return 0;
  
  for(int i = 0; i < NUM_TIA_BIAS-1; i++)
  {
    v1 = opVolt*TIA_BIAS[i];
    v2 = opVolt*TIA_BIAS[i+1];

    if(voltage == v1) return polarity*i;
    else if(voltage > v1 && voltage < v2)
    {
      if(abs(voltage-v1) < abs(voltage-v2)) return polarity*i;
      else return polarity*(i+1);
    }
  }
  return 0;
}