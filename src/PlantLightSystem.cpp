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
    this->show_message(MESSAGE_INFO, "Initializing DHT Sensor...");
    SimpleDHT11 dht(DHT_PIN);
    Serial.println(F("Initializing DHT sensor..."));
    this->_DHT_Sensor = dht;
}

/**
 * @brief Get data from DHT sensor and store it in class attributes
 */
int PlantLightSystem::get_dht_data()
{

    int8_t error_check = DHT_SUCCESS;

    if ((error_check = this->_DHT_Sensor.read2(&this->_temperature, &this->_humidity, NULL)) != DHT_SUCCESS)
    {
        // Bitwise AND error selection
        int dht_error = SimpleDHTErrCode(error_check);

        delay(2000);
        return dht_error;
    }
    return DHT_SUCCESS;
}

/**
 * @brief Get temperature
 */
float PlantLightSystem::get_temperature()
{
    Serial.print(F("Temperature = "));
    Serial.print(this->_temperature);
    Serial.println(F(" *C"));

    return this->_temperature;
}

/**
 * @brief Get humidity
 */
float PlantLightSystem::get_humidity()
{
    Serial.print(F("Humidity = "));
    Serial.print(this->_humidity);
    Serial.println(F(" %"));

    return this->_humidity;
}

/** LCD */

/**
 * @brief LCD initialization
 */
void PlantLightSystem::initialize_LCD()
{
    LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

    Serial.println(F("Initializing LCD..."));
    this->_LCD_Display = lcd;
    this->_LCD_Display.init();
    // Turn on backlight
    this->_LCD_Display.backlight();

    this->show_message(MESSAGE_INFO, "Initializing LCD Module...");
}

/**
 * @brief Show message on LCD. First line is stationary, second one is scrolling if longer than 16 characters.
 */
void PlantLightSystem::show_message(int8_t type, const char *message)
{
    // Clear display
    this->_LCD_Display.clear();
    const char *message_type = (type == MESSAGE_INFO) ? "PLS INFO:" : "PLS ERROR:";
    Serial.println(message_type + (String) " " + message);

    // Print header on first line
    this->_LCD_Display.setCursor(0, 0);
    this->_LCD_Display.print(message_type);

    // Print second line
    this->_LCD_Display.setCursor(0, 1);

    // For messages shorter than 17 characters
    if (strlen(message) <= LCD_COLUMNS)
    {
        this->_LCD_Display.print(message);
    }

    // For messages longer than 17 characters
    if (strlen(message) > LCD_COLUMNS)
    {
        for (unsigned int i = 0; i <= LCD_COLUMNS; i++)
        {
            this->_LCD_Display.write(message[i]);
        }
        delay(1500);
        for (unsigned int j = LCD_COLUMNS + 1; j <= strlen(message); j++)
        {
            this->_LCD_Display.write(message[j]);
            this->_LCD_Display.scrollDisplayLeft();
            this->_LCD_Display.setCursor(j - LCD_COLUMNS, 0);
            this->_LCD_Display.print(message_type);
            this->_LCD_Display.setCursor(j + 1, 1);
            delay(300);
        }
        delay(1500);
    }
}

/** Relay */

/**
 * @brief Initialize relay board
 */
void PlantLightSystem::initialize_relay(int *relay_pins)
{

    this->show_message(MESSAGE_INFO, "Initializing Relay Module...");

    for (int this_pin = 0; this_pin < NUMBER_OF_CHANNELS; this_pin++)
    {
        Serial.println("Initializing relay pin: " + (String)relay_pins[this_pin]);
        pinMode(relay_pins[this_pin], LOW);
        this->_relay_channels[this_pin] = RelayChannel(relay_pins[this_pin], LOW);
        delay(300);
    }
}

/**
 * @brief Turn relay channel ON/OFF on given pin
 */
void PlantLightSystem::change_relay_state_on_pin(int relay_pin, const char *state)
{

    int channel_state = (!strcmp(state, RELAY_ON)) ? HIGH : LOW;

    Serial.println("Setting relay channel: " + (String)relay_pin + " " + state);

    for (int channel = 0; channel < NUMBER_OF_CHANNELS; channel++)
    {
        if (this->_relay_channels[channel].get_channel_pin() == relay_pin)
        {
            if (this->_relay_channels[channel].get_channel_state() == channel_state)
            {
                Serial.println(F("Channel is already ON. Nothing to do..."));
                return;
            }
            pinMode(relay_pin, channel_state);
            this->_relay_channels[channel].set_channel_state(channel_state);
        }
    }
    delay(500);
}