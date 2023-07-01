#include "RelayChannel.h"

RelayChannel::RelayChannel() {}
RelayChannel::~RelayChannel() {}

RelayChannel::RelayChannel(int relay_pin, int channel_state)
{
    this->relay_pin = relay_pin;
    this->channel_state = channel_state;
}

/**
 * @brief Get channel state value
 */
int RelayChannel::get_channel_state()
{
    return this->channel_state;
}

/**
 * @brief Get pin
 */
int RelayChannel::get_channel_pin()
{
    return this->relay_pin;
}

/**
 * @brief Set channel state value
 */
void RelayChannel::set_channel_state(int state)
{
    if (state == this->channel_state)
    {
        return;
    }
    this->channel_state = state;
}