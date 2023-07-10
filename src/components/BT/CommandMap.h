#ifndef COMMANDMAP_H
#define COMMANDMAP_H

#include <Arduino.h>
#include "constants.h"

class CommandMap
{
    private:
        const char* _cmd = "";
        int _cmd_value;

    public:
        CommandMap();
        ~CommandMap();

        CommandMap(const char* cmd, uint8_t cmd_value);
        int get_cmd_value();
        const char *get_cmd();

};

#endif /** COMMANDMAP_H */