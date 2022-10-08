/**
 * StAuth10184: I Jiawei Zhang, 000730840 certify that this material is my original work.
 * No other person's work has been used without due acknowledgement.
 */

// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the  DS18B20 is connected to
const int oneWireBus = D3;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

DeviceAddress address;

void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // Start the DS18B20 sensor
  DS18B20.begin();

  if (!DS18B20.getAddress(address, 0))
  {
    Serial.println("No DS18B20 temparature sensors are installed!");
  }
  else
  {
    Serial.print("Found DS18B20 sensor with address: ");
    for (uint8_t i = 0; i < 8; i++)
    {
      if (address[i] < 16)
        Serial.print("0");
      Serial.print(address[i], HEX);
    }
    Serial.println("");
  }
}

void loop()
{
  float fTemp;

  // ask DS18B20 for the current temperature
  DS18B20.requestTemperatures();

  // fetch the temperature.  We only have 1 sensor, so the index is 0.
  fTemp = DS18B20.getTempCByIndex(0);

  if (fTemp < 10)
  {
    Serial.println("Current temperature is: " + String(fTemp) + "°C or Cold!");
  }
  else if (fTemp < 15)
  {
    Serial.println("Current temperature is: " + String(fTemp) + "°C or Cool");
  }
  else if (fTemp < 25)
  {
    Serial.println("Current temperature is: " + String(fTemp) + "°C or Perfect");
  }
  else if (fTemp < 30)
  {
    Serial.println("Current temperature is: " + String(fTemp) + "°C or Warm");
  }
  else if (fTemp < 35)
  {
    Serial.println("Current temperature is: " + String(fTemp) + "°C or Hot");
  }
  else
  {
    Serial.println("Current temperature is: " + String(fTemp) + "°C or Too Hot!");
  }

  delay(5000);
}