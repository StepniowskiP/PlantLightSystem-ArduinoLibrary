/**
    RelayChannel class
*/

#ifndef RELAYCHANNEL_h
#define RELAYCHANNEL_h

#include <stdint.h>

struct RelayChannel
{
    uint8_t relay_pin;
    uint8_t channel_state;

    RelayChannel();
    ~RelayChannel();
    RelayChannel(uint8_t relay_pin, uint8_t channel_state);

    uint8_t get_channel_state();
    uint8_t get_channel_pin();
    void set_channel_state(uint8_t state);
};

#endif /* RELAYCHANNEL_h */