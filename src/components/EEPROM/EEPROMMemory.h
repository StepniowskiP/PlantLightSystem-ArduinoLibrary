#ifndef EEPROMMEMORY_H
#define EEPROMMEMORY_H

#include "constants.h"
#include <uEEPROMLib.h>

class EEPROMMemory{

    private:
        uEEPROMLib _eeprom;

    public:
        EEPROMMemory();
        ~EEPROMMemory();

        void initialize_eeprom();
        bool write_to_eeprom(const uint8_t address, uint8_t data);
        uint8_t read_from_eeprom(const uint8_t address);
};

#endif /* EEPROMMEMORY_H */