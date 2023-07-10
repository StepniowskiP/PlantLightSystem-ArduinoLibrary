#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "CommandMap.h"
#include "../../constants.h"

class Bluetooth{

    private:
        CommandMap _cmd_map[COMMAND::NUMBER_OF_COMMANDS];

    public:

        Bluetooth();
        ~Bluetooth();

        void initialize_bluetooth();
        void populate_cmd_map();
        uint16_t validate_command(char *command);
};


#endif /* BLUETOOTH_H */