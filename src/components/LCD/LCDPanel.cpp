#include "LCDPanel.h"


LCDPanel::LCDPanel(){}

LCDPanel::~LCDPanel() {}

/**
 * @brief LCD initialization
 */
void LCDPanel::initialize_LCD()
{
    if (PLS::LOGGING)
    {
        Serial.println(F("Initializing LCD..."));
    }

    LiquidCrystal_I2C lcd(LCD::ADDRESS, LCD::NUMBER_OF_COLUMNS, LCD::NUMBER_OF_ROWS);

    _lcd = lcd;
    _lcd.init();
}

/**
 * @brief Show message on LCD. First line is stationary, second one is scrolling if longer than 16 characters.
 */
void LCDPanel::show_message(int8_t type, const char *message)
{
    // Clear display
    _lcd.clear();
    const char *message_type = (type == PLS::MESSAGE_INFO) ? LCD::HEADER::INFO : LCD::HEADER::ERROR;

    if (PLS::LOGGING)
    {
        Serial.print(message_type);
        Serial.print(F("::"));
        Serial.println(message);
    }

    // Print header on first line
    _lcd.setCursor(0, 0);
    _lcd.print(message_type);

    // Print second line
    _lcd.setCursor(0, 1);

    // For messages shorter than 17 characters
    if (strlen(message) <= LCD::NUMBER_OF_COLUMNS)
    {
        _lcd.print(message);
    }

    // For messages longer than 17 characters
    if (strlen(message) > LCD::NUMBER_OF_COLUMNS)
    {
        for (unsigned int i = 0; i <= LCD::NUMBER_OF_COLUMNS; i++)
        {
            _lcd.write(message[i]);
        }
        delay(1500);
        for (unsigned int j = LCD::NUMBER_OF_COLUMNS + 1; j <= strlen(message); j++)
        {
            _lcd.write(message[j]);
            _lcd.scrollDisplayLeft();
            _lcd.setCursor(j - LCD::NUMBER_OF_COLUMNS, 0);
            _lcd.print(message_type);
            _lcd.setCursor(j + 1, 1);
            delay(300);
        }
        delay(1500);
    }
}



void LCDPanel::backlight_on(){
    if(PLS::LOGGING){
        Serial.println(F("LCD backlight ON"));
    }
    _lcd.backlight();
}

void LCDPanel::backlight_off(){
    if(PLS::LOGGING){
        Serial.println(F("LCD backlight OFF"));
    }
    _lcd.noBacklight();
}