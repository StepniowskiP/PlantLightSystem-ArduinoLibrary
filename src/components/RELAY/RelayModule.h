#ifndef RELAYMODULE_H
#define RELAYMODULE_H

#include <Arduino.h>
#include "../../constants.h"
#include "RelayChannel.h"

class RelayModule
{

public:
    RelayChannel relay_channels[RELAY::NUMBER_OF_CHANNELS];

    RelayModule();
    ~RelayModule();

    void initialize_relay();
    void change_relay_state_on_pin(uint8_t relay_pin, const char *state);
};

#endif /* RELAYMODULE_H */