#include "PlantLightSystem.h"

/** PlantLightSystem */

PlantLightSystem::PlantLightSystem() {}
PlantLightSystem::~PlantLightSystem() {}

void PlantLightSystem::init_components()
{

    // LCD 16x2
    if (PLS::COMPONENTS::LCD)
    {
        _LCDPanel = LCDPanel();
        _LCDPanel.initialize_LCD();
        if (LCD::BACKLIGHT_ON_START)
        {
            _LCDPanel.backlight_on();
        }
        _LCDPanel.show_message(PLS::MESSAGE_INFO, "Initializing components...");
    }

    // DHT (11 || 22)
    if (PLS::COMPONENTS::DHT)
    {
        _DHTSensor = DHTSensor();
        _DHTSensor.initialize_DHT();
    }

    // RELAY (8 channels)
    if (PLS::COMPONENTS::RELAY)
    {
        _RelayModule = RelayModule();
        _RelayModule.initialize_relay();
    }

    // Bluetooth HC-05
    if (PLS::COMPONENTS::BLUETOOTH)
    {
        _Bluetooth = Bluetooth();
        _Bluetooth.initialize_bluetooth();
    }

    // Button Panel
    if (PLS::COMPONENTS::BUTTON_PANEL)
    {
        _ButtonPanel = ButtonPanel();
        _ButtonPanel.initialize_button_panel();
    }

    // Message Queue
    if (PLS::COMPONENTS::BUTTON_PANEL && PLS::COMPONENTS::LCD)
    {
        if (!PLS::COMPONENTS::MESSAGE_QUEUE)
        {
            _LCDPanel.show_message(PLS::MESSAGE_INFO, "Message queue not initialized...");
        }
        else
        {
            _MessageQueue = MessageQueue();
            _populate_init_msg_queue();
        }
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
    _LCDPanel.show_message(PLS::MESSAGE_INFO, welcome_msg);
    _LCDPanel.show_message(PLS::MESSAGE_INFO, PLS::INSTRUCTION);
}

/**
 * @brief Get temperature from DHT sensor
 */
float PlantLightSystem::get_temperature()
{
    if (int check_code = _DHTSensor.get_dht_data() != DHT::SUCCESS)
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
        Serial.print(_DHTSensor.temperature);
        Serial.println(F(" *C"));
    }

    return _DHTSensor.temperature;
}

/**
 * @brief Get humidity from DHT sensor
 */
float PlantLightSystem::get_humidity()
{
    if (int check_code = _DHTSensor.get_dht_data() != DHT::SUCCESS)
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
        Serial.print(_DHTSensor.humidity);
        Serial.println(F(" %"));
    }

    return _DHTSensor.humidity;
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
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[0].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_2:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[1].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_3:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[2].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_4:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[3].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_5:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[4].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_6:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[5].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_7:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[6].relay_pin, RELAY::ON);
        break;
    case COMMAND::TURN_ON::LAMP_8:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[7].relay_pin, RELAY::ON);
        break;

    // Turn OFF lamp
    case COMMAND::TURN_OFF::LAMP_1:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[0].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_2:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[1].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_3:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[2].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_4:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[3].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_5:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[4].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_6:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[5].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_7:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[6].relay_pin, RELAY::OFF);
        break;
    case COMMAND::TURN_OFF::LAMP_8:
        _RelayModule.change_relay_state_on_pin(_RelayModule.relay_channels[7].relay_pin, RELAY::OFF);
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

void PlantLightSystem::_populate_init_msg_queue()
{
    if (PLS::LOGGING)
    {
        Serial.println(F("Populating initial message queue"));
    }

    _MessageQueue.add_reserved_message(PLS::INSTRUCTION, LCD::MESSAGE_QUEUE::RESERVED_INDEXES::INSTRUCTION);

    if (PLS::COMPONENTS::RTC)
    {
    }
    else
    {
        _MessageQueue.add_reserved_message(PLS::DATE_NOT_AVAILABLE, LCD::MESSAGE_QUEUE::RESERVED_INDEXES::DATE);
        _MessageQueue.add_reserved_message(PLS::TIME_NOT_AVAILABLE, LCD::MESSAGE_QUEUE::RESERVED_INDEXES::TIME);
    }

    if (PLS::COMPONENTS::DHT)
    {
        _DHTSensor.get_dht_data();

        char message[LCD::MESSAGE_QUEUE::MAX_MESSAGE_LENGTH];
        sprintf(message, "Temperature: %s *C", _DHTSensor.str_temperature);
        _MessageQueue.add_reserved_message(message, LCD::MESSAGE_QUEUE::RESERVED_INDEXES::TEMPERATURE);

        message[0] = '\0';
        sprintf(message, "Humidity: %s %%", _DHTSensor.str_humidity);
        _MessageQueue.add_reserved_message(message, LCD::MESSAGE_QUEUE::RESERVED_INDEXES::HUMIDITY);
    }
    else
    {
        _MessageQueue.add_reserved_message(PLS::TEMP_NOT_AVAILABLE, LCD::MESSAGE_QUEUE::RESERVED_INDEXES::TEMPERATURE);
        _MessageQueue.add_reserved_message(PLS::HUM_NOT_AVAILABLE, LCD::MESSAGE_QUEUE::RESERVED_INDEXES::HUMIDITY);
    }

    if (_MessageQueue.current_message == 0)
    {
        _LCDPanel.show_message(PLS::MESSAGE_INFO, PLS::INSTRUCTION);
    }
}

void PlantLightSystem::execute_button_command(int8_t event_number)
{
    if (PLS::LOGGING)
    {
        Serial.print(F("Button event number: "));
        Serial.println(event_number);
    }

    switch (event_number)
    {
    case LCD::BUTTON_PANEL::EVENTS::BACKLIGHT:
        if (_LCDPanel.backlight)
        {
            if (PLS::LOGGING)
            {
                Serial.println(F("Turning OFF backlight with a button."));
            }
            _LCDPanel.backlight_off();
            _LCDPanel.backlight = false;
            delay(LCD::BUTTON_PANEL::DELAY);
        }
        else
        {
            if (PLS::LOGGING)
            {
                Serial.println(F("Turning ON backlight with a button."));
            }
            _LCDPanel.backlight_on();
            _LCDPanel.backlight = true;
            delay(LCD::BUTTON_PANEL::DELAY);
        }
        break;
    case LCD::BUTTON_PANEL::EVENTS::LEFT:
        if (_MessageQueue.current_message == 0)
        {
            break;
        }
        _LCDPanel.show_message(PLS::MESSAGE_INFO, _MessageQueue.get_message_at_index(_MessageQueue.current_message - 1));
        _MessageQueue.current_message--;
        delay(LCD::BUTTON_PANEL::DELAY);
        break;
    case LCD::BUTTON_PANEL::EVENTS::RIGHT:
        if (_MessageQueue.current_message == LCD::MESSAGE_QUEUE::MAX_MESSAGES - 1)
        {
            break;
        }
        _LCDPanel.show_message(PLS::MESSAGE_INFO, _MessageQueue.get_message_at_index(_MessageQueue.current_message + 1));
        ++_MessageQueue.current_message;
        delay(LCD::BUTTON_PANEL::DELAY);
        break;
    default:
        break;
    }
}