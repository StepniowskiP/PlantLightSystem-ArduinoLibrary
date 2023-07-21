#include "Bluetooth.h"

Bluetooth::Bluetooth() {}

Bluetooth::~Bluetooth() {}

void Bluetooth::initialize_bluetooth()
{
    if (PLS::LOGGING)
    {
        Serial.println(F("Initializing Bluetooth module..."));
    }
    populate_cmd_map();
}

void Bluetooth::populate_cmd_map()
{

    if (PLS::LOGGING)
    {
        Serial.println(F("Populating Bluetooth command map..."));
    }

    // Lamp ON
    _cmd_map[0] = CommandMap("1_ON", COMMAND::TURN_ON::LAMP_1);
    _cmd_map[1] = CommandMap("2_ON", COMMAND::TURN_ON::LAMP_2);
    _cmd_map[2] = CommandMap("3_ON", COMMAND::TURN_ON::LAMP_3);
    _cmd_map[3] = CommandMap("4_ON", COMMAND::TURN_ON::LAMP_4);
    _cmd_map[4] = CommandMap("5_ON", COMMAND::TURN_ON::LAMP_5);
    _cmd_map[5] = CommandMap("6_ON", COMMAND::TURN_ON::LAMP_6);
    _cmd_map[6] = CommandMap("7_ON", COMMAND::TURN_ON::LAMP_7);
    _cmd_map[7] = CommandMap("8_ON", COMMAND::TURN_ON::LAMP_8);

    // Lamp OFF
    _cmd_map[8] = CommandMap("1_OFF", COMMAND::TURN_OFF::LAMP_1);
    _cmd_map[9] = CommandMap("2_OFF", COMMAND::TURN_OFF::LAMP_2);
    _cmd_map[10] = CommandMap("3_OFF", COMMAND::TURN_OFF::LAMP_3);
    _cmd_map[11] = CommandMap("4_OFF", COMMAND::TURN_OFF::LAMP_4);
    _cmd_map[12] = CommandMap("5_OFF", COMMAND::TURN_OFF::LAMP_5);
    _cmd_map[13] = CommandMap("6_OFF", COMMAND::TURN_OFF::LAMP_6);
    _cmd_map[14] = CommandMap("7_OFF", COMMAND::TURN_OFF::LAMP_7);
    _cmd_map[15] = CommandMap("8_OFF", COMMAND::TURN_OFF::LAMP_8);

    // Other
    _cmd_map[16] = CommandMap("HUMIDITY", COMMAND::OTHER::GET_HUMIDITY);
    _cmd_map[17] = CommandMap("TEMPERATURE", COMMAND::OTHER::GET_TEMPERATURE);
    _cmd_map[18] = CommandMap("TEST", COMMAND::OTHER::TEST_PLS_SYSTEM);
}

uint16_t Bluetooth::validate_command(char *command)
{
    uint8_t int_cmd = 0;

    for (uint8_t cmd = 0; cmd < COMMAND::NUMBER_OF_COMMANDS; cmd++)
    {

        if (!strcmp(command, _cmd_map[cmd].get_cmd()))
        {
            int_cmd = _cmd_map[cmd].get_cmd_value();
        }
    }

    delete command;
    return int_cmd;
}