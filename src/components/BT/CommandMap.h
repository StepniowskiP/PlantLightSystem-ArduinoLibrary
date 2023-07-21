#ifndef COMMANDMAP_H
#define COMMANDMAP_H

#include <Arduino.h>
#include "constants.h"

class CommandMap
{
private:
    const char *_cmd = "";
    uint8_t _cmd_value;

public:
    CommandMap();
    ~CommandMap();

    CommandMap(const char *cmd, uint8_t cmd_value);
    uint8_t get_cmd_value();
    const char *get_cmd();
};

#endif /** COMMANDMAP_H */