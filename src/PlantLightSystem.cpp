#include "PlantLightSystem.h"

/** PlantLightSystem */

PlantLightSystem::PlantLightSystem() {}
PlantLightSystem::~PlantLightSystem() {}

/** DHT */

/**
 * @brief DHT sensor initialization
 */
void PlantLightSystem::initialize_DHT()
{
    if (PLS::LOGGING)
    {
        Serial.println(F("Initializing DHT sensor..."));
        Serial.print(F("DHT version: "));
        Serial.println(DHT::TYPE);
    }
    show_message(PLS::MESSAGE_INFO, "Initializing DHT Sensor...");

    if (DHT::TYPE == 11)
    {
        SimpleDHT11 dht(DHT::PIN);
        _DHT_Sensor11 = dht;
    }
    else if (DHT::TYPE == 22)
    {
        SimpleDHT22 dht(DHT::PIN);
        _DHT_Sensor22 = dht;
    }
    else
    {
        if (PLS::LOGGING)
        {
            Serial.println(F("Wrong DHT sensor type"));
        }
    }
}

/**
 * @brief Get data from DHT sensor and store it in class attributes
 */
uint8_t PlantLightSystem::get_dht_data()
{

    int8_t error_check = DHT::SUCCESS;
    if (DHT::TYPE == 11)
    {
        if ((error_check = _DHT_Sensor11.read2(&_temperature, &_humidity, NULL)) != DHT::SUCCESS)
        {
            // Bitwise AND error selection
            error_check = SimpleDHTErrCode(error_check);
            delay(2000);
        }
    }
    else if (DHT::TYPE == 22)
    {
        if ((error_check = _DHT_Sensor22.read2(&_temperature, &_humidity, NULL)) != DHT::SUCCESS)
        {
            // Bitwise AND error selection
            error_check = SimpleDHTErrCode(error_check);
            delay(2000);
        }
    }

    return error_check;
}

/**
 * @brief Get temperature
 */
float PlantLightSystem::get_temperature()
{
    if (int check_code = get_dht_data() != DHT::SUCCESS)
    {
        if (PLS::LOGGING)
        {
            Serial.print(F("Read DHT11 failed, error: "));
            Serial.println(check_code);
        }
    }

    if (PLS::LOGGING)
    {
        Serial.print(F("Temperature = "));
        Serial.print(_temperature);
        Serial.println(F(" *C"));
    }

    return _temperature;
}

/**
 * @brief Get humidity
 */
float PlantLightSystem::get_humidity()
{
    if (int check_code = get_dht_data() != DHT::SUCCESS)
    {
        if (PLS::LOGGING)
        {
            Serial.print(F("Read DHT11 failed, error: "));
            Serial.println(check_code);
        }
    }

    if (PLS::LOGGING)
    {
        Serial.print(F("Humidity = "));
        Serial.print(_humidity);
        Serial.println(F(" %"));
    }

    return _humidity;
}

/** LCD */

/**
 * @brief LCD initialization
 */
void PlantLightSystem::initialize_LCD()
{
    if (PLS::LOGGING)
    {
        Serial.println(F("Initializing LCD..."));
    }
    show_message(PLS::MESSAGE_INFO, "Initializing LCD Module...");

    LiquidCrystal_I2C lcd(LCD::ADDRESS, LCD::NUMBER_OF_COLUMNS, LCD::NUMBER_OF_ROWS);
    _LCD_Display = lcd;
    _LCD_Display.init();
    _LCD_Display.backlight();
}

/**
 * @brief Show message on LCD. First line is stationary, second one is scrolling if longer than 16 characters.
 */
void PlantLightSystem::show_message(int8_t type, const char *message)
{
    // Clear display
    _LCD_Display.clear();
    const char *message_type = (type == PLS::MESSAGE_INFO) ? LCD::HEADER::INFO : LCD::HEADER::ERROR;

    if (PLS::LOGGING)
    {
        Serial.print(message_type);
        Serial.print(F("::"));
        Serial.println(message);
    }

    // Print header on first line
    _LCD_Display.setCursor(0, 0);
    _LCD_Display.print(message_type);

    // Print second line
    _LCD_Display.setCursor(0, 1);

    // For messages shorter than 17 characters
    if (strlen(message) <= LCD::NUMBER_OF_COLUMNS)
    {
        _LCD_Display.print(message);
    }

    // For messages longer than 17 characters
    if (strlen(message) > LCD::NUMBER_OF_COLUMNS)
    {
        for (unsigned int i = 0; i <= LCD::NUMBER_OF_COLUMNS; i++)
        {
            _LCD_Display.write(message[i]);
        }
        delay(1500);
        for (unsigned int j = LCD::NUMBER_OF_COLUMNS + 1; j <= strlen(message); j++)
        {
            _LCD_Display.write(message[j]);
            _LCD_Display.scrollDisplayLeft();
            _LCD_Display.setCursor(j - LCD::NUMBER_OF_COLUMNS, 0);
            _LCD_Display.print(message_type);
            _LCD_Display.setCursor(j + 1, 1);
            delay(300);
        }
        delay(1500);
    }
}

/** Relay */

/**
 * @brief Initialize relay board
 */
void PlantLightSystem::initialize_relay(uint8_t *relay_pins)
{

    if (PLS::LOGGING)
    {
        Serial.println(F("Initializing Relay Board..."));
    }
    show_message(PLS::MESSAGE_INFO, "Initializing Relay Module...");

    for (uint8_t this_pin = 0; this_pin < RELAY::NUMBER_OF_CHANNELS; this_pin++)
    {
        if (PLS::LOGGING)
        {
            Serial.print(F("Initializing relay pin: "));
            Serial.println(relay_pins[this_pin]);
        }

        pinMode(relay_pins[this_pin], LOW);
        _relay_channels[this_pin] = RelayChannel(relay_pins[this_pin], LOW);
        delay(300);
    }
}

/**
 * @brief Turn relay channel ON/OFF on given pin
 */
void PlantLightSystem::change_relay_state_on_pin(uint8_t relay_pin, const char *state)
{

    int channel_state = (!strcmp(state, RELAY::ON)) ? HIGH : LOW;

    if (PLS::LOGGING)
    {
        Serial.print(F("Setting relay channel: "));
        Serial.print(relay_pin);
        Serial.print(F(" "));
        Serial.println(state);
    }

    for (int channel = 0; channel < RELAY::NUMBER_OF_CHANNELS; channel++)
    {
        if (_relay_channels[channel].get_channel_pin() == relay_pin)
        {
            if (_relay_channels[channel].get_channel_state() == channel_state)
            {
                if (PLS::LOGGING)
                {
                    Serial.print(F("Channel: "));
                    Serial.print(relay_pin);
                    Serial.print(F("is already set to: "));
                    Serial.print(channel_state);
                    Serial.println(F(". Nothing to do..."));
                }
                return;
            }
            pinMode(relay_pin, channel_state);
            _relay_channels[channel].set_channel_state(channel_state);
        }
    }
    delay(500);
}

/** Bluetooth */

void PlantLightSystem::initialize_bluetooth()
{
    if (PLS::LOGGING)
    {
        Serial.println(F("Initializing Bluetooth module..."));
    }
    show_message(PLS::MESSAGE_INFO, "Initializing Bluetooth module...");

    populate_cmd_map();
}

void PlantLightSystem::show_welcome_message(char *welcome_msg)
{
    if (PLS::LOGGING)
    {
        Serial.print(F("Showing welcome message: "));
        Serial.println(welcome_msg);
    }
    show_message(PLS::MESSAGE_INFO, welcome_msg);
}

uint16_t PlantLightSystem::validate_command(char *command)
{
    int int_cmd = 0;

    for (int cmd = 0; cmd < COMMAND::NUMBER_OF_COMMANDS; cmd++)
    {

        if (!strcmp(command, _CMD_MAP[cmd].get_cmd()))
        {
            Serial.println("wchodzi");
            int_cmd = _CMD_MAP[cmd].get_cmd_value();
            Serial.println(int_cmd);
        }
    }

    delete command;
    return int_cmd;
}

uint8_t PlantLightSystem::execute_bluetooth_lamp_command(uint16_t command)
{

    if (PLS::LOGGING)
    {
        Serial.print(F("Executing lamp command: "));
        Serial.println(command);
    }

    uint8_t status = COMMAND::STATUS_SUCCESS;

    switch (command)
    {

    // Turn ON lamp
    case COMMAND::TURN_ON::LAMP_1:
        change_relay_state_on_pin(_relay_channels[0].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_2:
        change_relay_state_on_pin(_relay_channels[1].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_3:
        change_relay_state_on_pin(_relay_channels[2].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_4:
        change_relay_state_on_pin(_relay_channels[3].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_5:
        change_relay_state_on_pin(_relay_channels[4].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_6:
        change_relay_state_on_pin(_relay_channels[5].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_7:
        change_relay_state_on_pin(_relay_channels[6].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_8:
        change_relay_state_on_pin(_relay_channels[7].relay_pin, RELAY::ON);
        break;

    // Turn OFF lamp
    case COMMAND::TURN_OFF::LAMP_1:
        change_relay_state_on_pin(_relay_channels[0].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_2:
        change_relay_state_on_pin(_relay_channels[1].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_3:
        change_relay_state_on_pin(_relay_channels[2].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_4:
        change_relay_state_on_pin(_relay_channels[3].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_5:
        change_relay_state_on_pin(_relay_channels[4].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_6:
        change_relay_state_on_pin(_relay_channels[5].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_7:
        change_relay_state_on_pin(_relay_channels[6].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_8:
        change_relay_state_on_pin(_relay_channels[7].relay_pin, RELAY::OFF);
        break;
    default:
        status = COMMAND::STATUS_FAILURE;
        break;
    }

    return status;
}

float PlantLightSystem::execute_bluetooth_dht_command(uint16_t command)
{
    if (PLS::LOGGING)
    {
        Serial.print(F("Executing command: "));
        Serial.println(command);
    }

    float return_value = 0.00f;

    switch (command)
    {
    case COMMAND::OTHER::GET_HUMIDITY:
        return_value = get_humidity();
        break;
    case COMMAND::OTHER::GET_TEMPERATURE:
        return_value = get_temperature();
        break;
    default:
        break;
    }

    return return_value;
}

void PlantLightSystem::populate_cmd_map()
{

    // Lamp ON
    _CMD_MAP[0] = CommandMap("1_ON", COMMAND::TURN_ON::LAMP_1);
    _CMD_MAP[1] = CommandMap("2_ON", COMMAND::TURN_ON::LAMP_2);
    _CMD_MAP[2] = CommandMap("3_ON", COMMAND::TURN_ON::LAMP_3);
    _CMD_MAP[3] = CommandMap("4_ON", COMMAND::TURN_ON::LAMP_4);
    _CMD_MAP[4] = CommandMap("5_ON", COMMAND::TURN_ON::LAMP_5);
    _CMD_MAP[5] = CommandMap("6_ON", COMMAND::TURN_ON::LAMP_6);
    _CMD_MAP[6] = CommandMap("7_ON", COMMAND::TURN_ON::LAMP_7);
    _CMD_MAP[7] = CommandMap("8_ON", COMMAND::TURN_ON::LAMP_8);

    // Lamp OFF
    _CMD_MAP[8] = CommandMap("1_OFF", COMMAND::TURN_OFF::LAMP_1);
    _CMD_MAP[9] = CommandMap("2_OFF", COMMAND::TURN_OFF::LAMP_2);
    _CMD_MAP[10] = CommandMap("3_OFF", COMMAND::TURN_OFF::LAMP_3);
    _CMD_MAP[11] = CommandMap("4_OFF", COMMAND::TURN_OFF::LAMP_4);
    _CMD_MAP[12] = CommandMap("5_OFF", COMMAND::TURN_OFF::LAMP_5);
    _CMD_MAP[13] = CommandMap("6_OFF", COMMAND::TURN_OFF::LAMP_6);
    _CMD_MAP[14] = CommandMap("7_OFF", COMMAND::TURN_OFF::LAMP_7);
    _CMD_MAP[15] = CommandMap("8_OFF", COMMAND::TURN_OFF::LAMP_8);

    // Other
    _CMD_MAP[16] = CommandMap("HUMIDITY", COMMAND::OTHER::GET_HUMIDITY);
    _CMD_MAP[17] = CommandMap("TEMPERATURE", COMMAND::OTHER::GET_TEMPERATURE);
    _CMD_MAP[18] = CommandMap("TEST", COMMAND::OTHER::TEST_PLS_SYSTEM);
}