/*
author: PStepniowski
description: PLS example with only DHT sensor

To enable DHT change in constants.h file:
PLS::COMPONENTS::DHT -> true
DHT::TYPE -> 22 or 11 (Only these two are supported)

Tested on Arduino Nano:
RAM:   [===       ]  34.2% (used 701 bytes from 2048 bytes)
Flash: [====      ]  38.5% (used 11814 bytes from 30720 bytes)

Sample output from Serial Monitor (PLS::LOGGING = 1):

Initializing DHT sensor...
DHT version: 22
Humidity = 47.10 %
47.10
Temperature = 27.90 *C
27.90
...
*/

#include <Arduino.h>
#include <PlantLightSystem.h>

PlantLightSystem pls;

void setup()
{
    Serial.begin(9600);
    pls.init_components();
}

void loop()
{

    // Get humidity
    float humidity = pls.get_humidity();
    Serial.println(humidity);
    delay(1000);

    // Get temperature
    float temperature = pls.get_temperature();
    Serial.println(temperature);
    delay(1000);
}
