/**
    PlantLightSystem class
*/

#ifndef PLANTLIGHTSYSTEM_h
#define PLANTLIGHTSYSTEM_h

#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "constants.h"
#include "components/LCD/LCDPanel.h"
#include "components/DHT/DHTSensor.h"
#include "components/RELAY/RelayModule.h"
#include "components/BT/Bluetooth.h"

class PlantLightSystem
{

private:

    DHTSensor _DHT_Sensor;
    LCDPanel _LCD_Panel;
    RelayModule _Relay_Module;


public:
    Bluetooth _Bluetooth;

    PlantLightSystem();
    ~PlantLightSystem();

    void init_components();
    void show_welcome_message(const char *welcome_msg);

    float get_temperature();
    float get_humidity();
    float execute_dht_command(uint16_t command);

    uint8_t execute_lamp_command(uint16_t command);
};

#endif /* PLANTLIGHTSYSTEM_h */