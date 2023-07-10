
#ifndef CONSTANTS_h
#define CONSTANTS_h

#include <Arduino.h>

/* Plant Lamp System */
namespace PLS
{
    const uint16_t BAUD_RATE = 9600;
    const uint8_t MESSAGE_INFO = 0;
    const uint8_t MESSAGE_ERROR = 1;
    const uint8_t LOGGING = 1;

    const bool DHT = true;
    const bool LCD = true;
    const bool RELAY = true;
    const bool BLUETOOTH = true;

    const char WELCOME_MSG[] = "All modules ready! Welcome!";
}

/* Temperature and Humidity Sensor */
namespace DHT
{
    const uint8_t SUCCESS = 0;
    const uint8_t PIN = 9;
    const uint16_t TYPE = 22;
}

/* Liquid Crystal Display */
namespace LCD
{
    const uint8_t ADDRESS = 0x27;
    const uint8_t NUMBER_OF_COLUMNS = 16;
    const uint8_t NUMBER_OF_ROWS = 2;
    const bool BACKLIGHT_ON_START = true;

    namespace HEADER
    {
        const char INFO[] = "PLS INFO:";
        const char ERROR[] = "PLS ERROR!";
    }

}

/* Relay Board */
namespace RELAY
{
    const uint8_t NUMBER_OF_CHANNELS = 4;
    const uint8_t MAX_NUMBER_OF_CHANNELS = 8;
    const uint8_t NUMBER_OF_PROPERTIES = 2;

    const char ON[] = "ON";
    const char OFF[] = "OFF";

    const uint8_t RELAY_PINS[RELAY::NUMBER_OF_CHANNELS] = {2, 3, 4, 6};
}

/* Bluetooth Module */
namespace HC05
{
    const uint8_t RX_PIN = 11;
    const uint8_t TX_PIN = 12;
    const uint16_t BAUD_RATE = 9600;

}

/* Command settings and mapping for Plant Light System */
namespace COMMAND
{
    const uint8_t NUMBER_OF_COMMANDS = 19;
    const uint8_t MAX_LENGTH = 13;

    const uint8_t STATUS_SUCCESS = 200;
    const uint8_t STATUS_FAILURE = 0;
    const uint16_t STATUS_NOT_FOUND = 404;

    namespace TURN_ON
    {
        const uint8_t LAMP_1 = 1;
        const uint8_t LAMP_2 = 2;
        const uint8_t LAMP_3 = 3;
        const uint8_t LAMP_4 = 4;
        const uint8_t LAMP_5 = 5;
        const uint8_t LAMP_6 = 6;
        const uint8_t LAMP_7 = 7;
        const uint8_t LAMP_8 = 8;
    }

    namespace TURN_OFF
    {
        const uint8_t LAMP_1 = 11;
        const uint8_t LAMP_2 = 12;
        const uint8_t LAMP_3 = 13;
        const uint8_t LAMP_4 = 14;
        const uint8_t LAMP_5 = 15;
        const uint8_t LAMP_6 = 16;
        const uint8_t LAMP_7 = 17;
        const uint8_t LAMP_8 = 18;
    }

    namespace OTHER
    {
        const uint8_t GET_HUMIDITY = 101;
        const uint8_t GET_TEMPERATURE = 102;
        const uint8_t TEST_PLS_SYSTEM = 200;
    }
}

#endif /* CONSTANTS_h */