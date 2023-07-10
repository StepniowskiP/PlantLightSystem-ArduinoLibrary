#include "PlantLightSystem.h"

/** PlantLightSystem */

PlantLightSystem::PlantLightSystem() {}
PlantLightSystem::~PlantLightSystem() {}


void PlantLightSystem::init_components(){

    // LCD
    if(PLS::LCD){
        _LCD_Panel = LCDPanel();
        _LCD_Panel.initialize_LCD();
        if(LCD::BACKLIGHT_ON_START){
            _LCD_Panel.backlight_on();
        }
        _LCD_Panel.show_message(PLS::MESSAGE_INFO, "Initializing components...");
    }

    // DHT
    if(PLS::DHT){
        _DHT_Sensor = DHTSensor();
        _DHT_Sensor.initialize_DHT();
    }

    // RELAY
    if(PLS::RELAY){
        _Relay_Module = RelayModule();
        _Relay_Module.initialize_relay();
    }

    if(PLS::BLUETOOTH){
        _Bluetooth = Bluetooth();
        _Bluetooth.initialize_bluetooth();
    }
}

/**
 * @brief Show welcome message on lcd screen.
 */
void PlantLightSystem::show_welcome_message(const char *welcome_msg)
{
    if (PLS::LOGGING)
    {
        Serial.print(F("Showing welcome message: "));
        Serial.println(welcome_msg);
    }
    _LCD_Panel.show_message(PLS::MESSAGE_INFO, welcome_msg);
}


/**
 * @brief Get temperature from DHT sensor
 */
float PlantLightSystem::get_temperature()
{
    if (int check_code = _DHT_Sensor.get_dht_data() != DHT::SUCCESS)
    {
        if (PLS::LOGGING)
        {
            Serial.print(F("Read DHT data failed, error: "));
            Serial.println(check_code);
        }
    }

    if (PLS::LOGGING)
    {
        Serial.print(F("Temperature = "));
        Serial.print(_DHT_Sensor.temperature);
        Serial.println(F(" *C"));
    }

    return _DHT_Sensor.temperature;
}

/**
 * @brief Get humidity from DHT sensor
 */
float PlantLightSystem::get_humidity()
{
    if (int check_code = _DHT_Sensor.get_dht_data() != DHT::SUCCESS)
    {
        if (PLS::LOGGING)
        {
            Serial.print(F("Read DHT data failed, error: "));
            Serial.println(check_code);
        }
    }

    if (PLS::LOGGING)
    {
        Serial.print(F("Humidity = "));
        Serial.print(_DHT_Sensor.humidity);
        Serial.println(F(" %"));
    }

    return _DHT_Sensor.humidity;
}


uint8_t PlantLightSystem::execute_lamp_command(uint16_t command)
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
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[0].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_2:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[1].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_3:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[2].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_4:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[3].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_5:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[4].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_6:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[5].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_7:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[6].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_8:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[7].relay_pin, RELAY::ON);
        break;

    // Turn OFF lamp
    case COMMAND::TURN_OFF::LAMP_1:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[0].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_2:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[1].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_3:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[2].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_4:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[3].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_5:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[4].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_6:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[5].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_7:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[6].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_8:
        _Relay_Module.change_relay_state_on_pin(_Relay_Module.relay_channels[7].relay_pin, RELAY::OFF);
        break;
    default:
        status = COMMAND::STATUS_FAILURE;
        break;
    }

    return status;
}

float PlantLightSystem::execute_dht_command(uint16_t command)
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
