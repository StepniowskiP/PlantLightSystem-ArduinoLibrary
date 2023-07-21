#ifndef BUTTONPANEL_H
#define BUTTONPANEL_H

#include "../../constants.h"
#include "LCDPanel.h"

class ButtonPanel
{

private:
    uint16_t _button_input;
    bool _get_analog_input_value();

public:
    ButtonPanel();
    ~ButtonPanel();

    void initialize_button_panel();
    int8_t register_event();
};

#endif /* BUTTONPANEL_H */