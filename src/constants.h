
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

/* Plant Light System */
namespace PLS
{
    const uint16_t BAUD_RATE = 9600;
    const uint8_t MESSAGE_INFO = 0;
    const uint8_t MESSAGE_ERROR = 1;
    const uint8_t LOGGING = 1;

    namespace COMPONENTS
    {
        const bool DHT = false;
        const bool LCD = false;
        const bool RELAY = false;
        const bool BLUETOOTH = false;
        const bool BUTTON_PANEL = false;
        const bool MESSAGE_QUEUE = false;
        const bool RTC = true;
    }

    const char WELCOME_MSG[] = "All modules ready! Welcome!";
    const char INSTRUCTION[] = "Messages ->";
    const char HUM_NOT_AVAILABLE[] = "Humidity not available";
    const char TEMP_NOT_AVAILABLE[] = "Temperature not available";
    const char DATE_NOT_AVAILABLE[] = "Date not available";
    const char TIME_NOT_AVAILABLE[] = "Time not available";
}

/* Temperature and Humidity Sensor */
namespace DHT
{
    const uint8_t SUCCESS = 0;
    const uint8_t PIN = 12;
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

    namespace BUTTON_PANEL
    {
        const uint8_t PIN = A2;
        const uint8_t DELAY = 200;

        const uint16_t BACKLIGHT_MIN = 1010;
        const uint16_t BACKLIGHT_MAX = 1020;

        const uint16_t LEFT_MIN = 970;
        const uint16_t LEFT_MAX = 980;

        const uint16_t RIGHT_MIN = 925;
        const uint16_t RIGHT_MAX = 935;

        namespace EVENTS
        {
            const uint8_t BACKLIGHT = 1;
            const uint8_t LEFT = 2;
            const uint8_t RIGHT = 3;
            const uint8_t BAD_EVENT = -1;
        }
    }

    namespace MESSAGE_QUEUE
    {
        const uint8_t MAX_MESSAGES = 10;
        const uint8_t MAX_MESSAGE_LENGTH = 50;

        namespace RESERVED_INDEXES
        {
            const uint8_t INSTRUCTION = 0;
            const uint8_t DATE = 1;
            const uint8_t TIME = 2;
            const uint8_t TEMPERATURE = 3;
            const uint8_t HUMIDITY = 4;
        }
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

    const uint8_t RELAY_PINS[RELAY::NUMBER_OF_CHANNELS] = {2, 3, 4, 5};
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

#endif /* CONSTANTS_H */