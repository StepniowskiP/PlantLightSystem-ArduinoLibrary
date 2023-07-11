#ifndef LCDPANEL_H
#define LCDPANEL_H

#include <Arduino.h>
#include "constants.h"
#include <LiquidCrystal_I2C.h>

class LCDPanel{
    private:
        LiquidCrystal_I2C _lcd;

    public:

        bool backlight;

        LCDPanel();
        ~LCDPanel();

        void initialize_LCD();
        void show_message(int8_t type, String message);
        void backlight_on();
        void backlight_off();
};

#endif /* LCDPANEL_H */