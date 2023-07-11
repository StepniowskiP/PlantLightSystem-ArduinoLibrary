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
#include "components/LCD/ButtonPanel.h"
#include "components/LCD/MessageQueue.h"
#include "components/DHT/DHTSensor.h"
#include "components/RELAY/RelayModule.h"
#include "components/BT/Bluetooth.h"


class PlantLightSystem
{

private:
    DHTSensor _DHTSensor;
    RelayModule _RelayModule;

    void _populate_init_msg_queue();

public:
    MessageQueue _MessageQueue;
    Bluetooth _Bluetooth;
    LCDPanel _LCDPanel;
    ButtonPanel _ButtonPanel;

    PlantLightSystem();
    ~PlantLightSystem();

    void init_components();
    void show_welcome_message(const char *welcome_msg);
    void execute_button_command(int8_t event_number);

    uint8_t execute_lamp_command(uint16_t command);

    float get_temperature();
    float get_humidity();
    float execute_dht_command(uint16_t command);

};

#endif /* PLANTLIGHTSYSTEM_h */