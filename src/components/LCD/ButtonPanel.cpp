#include "ButtonPanel.h"

ButtonPanel::ButtonPanel() {}
ButtonPanel::~ButtonPanel() {}

void ButtonPanel::initialize_button_panel()
{
    if (PLS::LOGGING)
    {
        Serial.println(F("Initializing LCD Button panel..."));
    }
}

bool ButtonPanel::_get_analog_input_value()
{
    uint16_t analog_value = analogRead(LCD::BUTTON_PANEL::PIN);

    if (analog_value < LCD::BUTTON_PANEL::RIGHT_MIN)
    {
        return false;
    }

    _button_input = analog_value;
    return true;
}

int8_t ButtonPanel::register_event()
{

    if (!_get_analog_input_value())
    {
        Serial.println(F("Wrong input number detected"));
        return LCD::BUTTON_PANEL::EVENTS::BAD_EVENT;
    }

    if (_button_input > LCD::BUTTON_PANEL::BACKLIGHT_MIN && _button_input < LCD::BUTTON_PANEL::BACKLIGHT_MAX)
    {
        return LCD::BUTTON_PANEL::EVENTS::BACKLIGHT;
    }
    else if (_button_input > LCD::BUTTON_PANEL::LEFT_MIN && _button_input < LCD::BUTTON_PANEL::LEFT_MAX)
    {
        return LCD::BUTTON_PANEL::EVENTS::LEFT;
    }
    else if (_button_input > LCD::BUTTON_PANEL::RIGHT_MIN && _button_input < LCD::BUTTON_PANEL::RIGHT_MAX)
    {
        return LCD::BUTTON_PANEL::EVENTS::RIGHT;
    }
    return 0;
}