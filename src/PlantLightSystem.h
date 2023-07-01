/**
    PlantLightSystem class
*/

#ifndef PLANTLIGHTSYSTEM_h
#define PLANTLIGHTSYSTEM_h

#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "constants.h"
#include "RelayChannel.h"

class PlantLightSystem
{

private:
    SimpleDHT11 _DHT_Sensor;
    LiquidCrystal_I2C _LCD_Display;

    float _temperature;
    float _humidity;

    RelayChannel _relay_channels[NUMBER_OF_CHANNELS];

public:
    PlantLightSystem();
    ~PlantLightSystem();

    /* DHT */
    void initialize_DHT();
    int get_dht_data();
    float get_temperature();
    float get_humidity();

    /* LCD */
    void initialize_LCD();
    void show_message(int8_t type, const char *message);

    /* Relay */
    void initialize_relay(int *relay_pins);
    void change_relay_state_on_pin(int relay_pin, const char *state);
};

#endif /* PLANTLIGHTSYSTEM_h */