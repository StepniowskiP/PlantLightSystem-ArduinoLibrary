/*
author: PStepniowski
description: PLS example with DHT sensor and LCD 16x2 screen

To enable DHT change in constants.h file:
PLS::COMPONENTS::LCD -> true

LCD::ADRESS -> I2C LCD adress
LCD::NUMBER_OF_COLUMNS -> Number of columns on your display (tested only for 16)
LCD::NUMBER_OF_ROWS -> Number of rows on your display (tested only for 2)

You can also change headers (currently only two) for first line by changing:
LCD::HEADER::INFO
LCD::HEADER::ERROR

Tested on Arduino Nano:
RAM:   [====      ]  39.8% (used 815 bytes from 2048 bytes)
Flash: [====      ]  38.3% (used 11766 bytes from 30720 bytes)

Sample output from Serial Monitor (PLS::LOGGING = 1):

Initializing LCD...
LCD backlight ON
PLS INFO:::Initializing components...
Initializing DHT sensor...
DHT version: 22
PLS INFO:::47.50
PLS ERROR!::Some serious error occurred!!!!
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

    // get string humidity and print it on LCD panel
    pls._DHTSensor.get_dht_data();

    // info message from dht
    pls._LCDPanel.show_message(PLS::MESSAGE_INFO, pls._DHTSensor.str_humidity);
    delay(1000);

    // some error message
    pls._LCDPanel.show_message(PLS::MESSAGE_ERROR, "Some serious error occurred!!!!");

    delay(1000);
}
