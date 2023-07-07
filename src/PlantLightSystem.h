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
#include "CommandMap.h"

class PlantLightSystem
{

private:
    SimpleDHT11 _DHT_Sensor11;
    SimpleDHT22 _DHT_Sensor22;

    LiquidCrystal_I2C _LCD_Display;
    CommandMap _CMD_MAP[COMMAND::NUMBER_OF_COMMANDS];

    float _temperature;
    float _humidity;

    RelayChannel _relay_channels[RELAY::NUMBER_OF_CHANNELS];



public:
    PlantLightSystem();
    ~PlantLightSystem();

    /* DHT */
    void initialize_DHT();
    uint8_t get_dht_data();
    float get_temperature();
    float get_humidity();

    /* LCD */
    void initialize_LCD();
    void show_message(int8_t type, const char *message);
    void show_welcome_message(char *welcome_msg);

    /* Relay */
    void initialize_relay(uint8_t *relay_pins);
    void change_relay_state_on_pin(uint8_t relay_pin, const char *state);

    /* Bluetooth */
    void initialize_bluetooth();
    void populate_cmd_map();
    uint16_t validate_command(char *command);
    uint8_t execute_bluetooth_lamp_command(uint16_t command);
    float execute_bluetooth_dht_command(uint16_t command);

};

#endif /* PLANTLIGHTSYSTEM_h */