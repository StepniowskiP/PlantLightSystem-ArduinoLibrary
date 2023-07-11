# PlantLightSystem-ArduinoLibrary (WIP)
This Library has status WIP (Work In Progress).

This part is an Arduino Library, which delivers core operability of Rack Node in PLS (Plant Light System) project.
## Description
Collectors of tropical plants may encounter a problem with the lack of light due to seasonal variations or the absence of properly sunlit areas that would guarantee the plants' optimal growth. That is why many of them rely on lamp systems (often homemade) to supplement or even completely replace natural sunlight. Unfortunately, such lamps need to be manually turned on (or used with a timer), require additional accessories for measuring environmental parameters (such as a hygrometer, thermometer), and often do not have an aesthetically pleasing appearance.

This project aims to create a fully automated lighting system for indoor plants that can be constructed by individuals. The system will collect analytical data from various sensors, and you will be able to control the lamp using an external application.

Project consists on three parts:

1. [Central Node] TBD
2. [Rack Node] TBD
3. [Application] TBD

## How to use

### Example 1: DHT Sensor

To enable DHT change in constants.h file:
```
PLS::COMPONENTS::DHT -> true
DHT::TYPE -> 22 or 11 (Only these two are supported)
```


Tested on Arduino Nano:
```
RAM:   [===       ]  34.2% (used 701 bytes from 2048 bytes)
Flash: [====      ]  38.5% (used 11814 bytes from 30720 bytes)
```


Sample output from Serial Monitor (PLS::LOGGING = 1):
```
Initializing DHT sensor...
DHT version: 22
Humidity = 47.10 %
47.10
Temperature = 27.90 *C
27.90
```

Example Code:
```C++
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
```

### Example 2: DHT Sensor and LCD screen

To enable DHT change in constants.h file:
```
PLS::COMPONENTS::DHT -> true
DHT::TYPE -> 22 or 11 (Only these two are supported)
```
To enable LCD change in constants.h file:
```
PLS::COMPONENTS::LCD -> true
```
Customize LCD (constants.h):
```
LCD::ADRESS -> I2C LCD adress
LCD::NUMBER_OF_COLUMNS -> Number of columns on your display (tested only for 16)
LCD::NUMBER_OF_ROWS -> Number of rows on your display (tested only for 2)
```
You can also change headers (currently only two) for first line by changing:
```
LCD::HEADER::INFO
LCD::HEADER::ERROR
```
Tested on Arduino Nano:
```
RAM:   [====      ]  39.8% (used 815 bytes from 2048 bytes)
Flash: [====      ]  38.3% (used 11766 bytes from 30720 bytes)
```
Sample output from Serial Monitor (PLS::LOGGING = 1):
```
Initializing LCD...
LCD backlight ON
PLS INFO:::Initializing components...
Initializing DHT sensor...
DHT version: 22
PLS INFO:::47.50
PLS ERROR!::Some serious error occurred!!!!
...
```
Example Code:
```C++
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
```

More examples in "examples" directory.

