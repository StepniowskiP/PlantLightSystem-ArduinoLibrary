#ifndef LCDPANEL_H
#define LCDPANEL_H

#include <Arduino.h>
#include "constants.h"
#include <LiquidCrystal_I2C.h>

class LCDPanel{
    private:
        LiquidCrystal_I2C _lcd;
        bool _backlight_on_startup;

    public:

        LCDPanel();
        ~LCDPanel();

        void initialize_LCD();
        void show_message(int8_t type, const char *message);
        void show_welcome_message(char *welcome_msg);
        void backlight_on();
        void backlight_off();
};

#endif /* LCDPANEL_H */