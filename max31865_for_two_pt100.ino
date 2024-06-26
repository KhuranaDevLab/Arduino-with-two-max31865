//This code is developed by KhuranaDevLab, for more visit https://github.com/KhuranaDevLab
//by using this code, you will be able to use two, two wired pt100 sensor with two MAX31865 in arduino uno. 
//use 4 and 11 as cs pin for two MAX31865
#include <Adafruit_MAX31865.h>
// Use software SPI: CS, DI, DO, CLK
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(4, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
Adafruit_MAX31865 thermo1 = Adafruit_MAX31865(9,11, 12, 13);
Adafruit_MAX31865 thermo2 = Adafruit_MAX31865(4,11, 12, 13);
// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
//better if you measure the resistance value manually
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit MAX31865 PT100 Sensor Test!");

  thermo1.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary
  thermo2.begin(MAX31865_2WIRE);
}


void loop() {
  uint16_t rtd1 = thermo1.readRTD();
  uint16_t rtd2 = thermo2.readRTD();

  //Serial.print("RTD value: "); Serial.println(rtd);
  float ratio1 = rtd1;
  ratio1 /= 32768;
    float ratio2 = rtd2;
  ratio2 /= 32768;
  Serial.print("Ratio = "); Serial.println(ratio2,8);
  Serial.print("Resistance = "); Serial.println(RREF*ratio2,8);
  Serial.print("Temperature = "); Serial.println(thermo1.temperature(RNOMINAL, RREF));
  Serial.print("Temperature = "); Serial.println(thermo2.temperature(RNOMINAL, RREF));

  // Check and print any faults
  //mostly these faults shows up when there is loose wire.
  uint8_t fault = thermo1.readFault();
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    thermo1.clearFault();
  }
  Serial.println();
  delay(1000);
}
