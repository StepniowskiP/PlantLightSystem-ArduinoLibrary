#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include "../../constants.h"

class MessageQueue
{
private:
    String _messages[LCD::MESSAGE_QUEUE::MAX_MESSAGES];
    uint8_t message_counter = 0;
    void _shift_queue();

public:
    MessageQueue();
    ~MessageQueue();

    uint8_t current_message = 0;

    void add_message(String message);
    void add_reserved_message(String message, uint8_t reserved_index);
    void clear_messages();

    String get_message_at_index(uint8_t index);
};

#endif /* MESSAGEQUEUE_H */