/**
    RelayChannel class
*/

#ifndef RELAYCHANNEL_h
#define RELAYCHANNEL_h

struct RelayChannel
{
    int relay_pin;
    int channel_state;

    RelayChannel();
    ~RelayChannel();
    RelayChannel(int relay_pin, int channel_state);

    int get_channel_state();
    int get_channel_pin();
    void set_channel_state(int state);
};

#endif /* RELAYCHANNEL_h */