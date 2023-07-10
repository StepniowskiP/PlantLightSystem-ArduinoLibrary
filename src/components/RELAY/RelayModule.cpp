#include "RelayModule.h"


RelayModule::RelayModule(){}
RelayModule::~RelayModule(){}

/**
 * @brief Initialize relay board
 */
void RelayModule::initialize_relay()
{

    if (PLS::LOGGING)
    {
        Serial.println(F("Initializing Relay Board..."));
    }

    for (uint8_t this_pin = 0; this_pin < RELAY::NUMBER_OF_CHANNELS; this_pin++)
    {
        if (PLS::LOGGING)
        {
            Serial.print(F("Initializing relay pin: "));
            Serial.println(RELAY::RELAY_PINS[this_pin]);
        }

        pinMode(RELAY::RELAY_PINS[this_pin], LOW);
        relay_channels[this_pin] = RelayChannel(RELAY::RELAY_PINS[this_pin], LOW);
        delay(300);
    }
}

/**
 * @brief Turn relay channel ON/OFF on given pin
 */
void RelayModule::change_relay_state_on_pin(uint8_t relay_pin, const char *state)
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
        if (relay_channels[channel].get_channel_pin() == relay_pin)
        {
            if (relay_channels[channel].get_channel_state() == channel_state)
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
            relay_channels[channel].set_channel_state(channel_state);
        }
    }
    delay(500);
}