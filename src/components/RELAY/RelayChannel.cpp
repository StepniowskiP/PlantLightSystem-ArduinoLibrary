#include "RelayChannel.h"
#include <stdint.h>

RelayChannel::RelayChannel() {}
RelayChannel::~RelayChannel() {}

RelayChannel::RelayChannel(uint8_t relay_pin, uint8_t channel_state)
{
    this->relay_pin = relay_pin;
    this->channel_state = channel_state;
}

/**
 * @brief Get channel state value
 */
uint8_t RelayChannel::get_channel_state()
{
    return channel_state;
}

/**
 * @brief Get pin
 */
uint8_t RelayChannel::get_channel_pin()
{
    return relay_pin;
}

/**
 * @brief Set channel state value
 */
void RelayChannel::set_channel_state(uint8_t state)
{
    if (state != channel_state)
    {
        channel_state = state;
    }
}