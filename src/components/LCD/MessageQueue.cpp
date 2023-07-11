#include "MessageQueue.h"

MessageQueue::MessageQueue() {}
MessageQueue::~MessageQueue() {}

void MessageQueue::_shift_queue()
{

    for (int8_t msg_iterator = 1; msg_iterator < LCD::MESSAGE_QUEUE::MAX_MESSAGES; msg_iterator++)
    {
        _messages[msg_iterator - 1] = _messages[msg_iterator];
    }
    message_counter--;
}

void MessageQueue::add_message(String message)
{
    // If messages overflows max capacity
    if (message_counter == LCD::MESSAGE_QUEUE::MAX_MESSAGES)
    {
        _shift_queue();
        _messages[LCD::MESSAGE_QUEUE::MAX_MESSAGES - 1] = message;
        return;
    }

    // Else populate next empty space
    _messages[message_counter] = message;
    message_counter++;
}

void MessageQueue::add_reserved_message(String message, uint8_t reserved_index){
    if(reserved_index < LCD::MESSAGE_QUEUE::MAX_MESSAGES){
        _messages[reserved_index] = message;
    }
}

void MessageQueue::clear_messages()
{
    for (int8_t msg_iterator = 0; msg_iterator < LCD::MESSAGE_QUEUE::MAX_MESSAGES; msg_iterator++)
    {
        _messages[msg_iterator] = (char *)'\0';
    }
    message_counter = 0;
}

String MessageQueue::get_message_at_index(uint8_t index){
    return _messages[index];
}