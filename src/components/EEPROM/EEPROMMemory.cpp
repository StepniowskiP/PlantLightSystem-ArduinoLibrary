
#include "EEPROMMemory.h"

EEPROMMemory::EEPROMMemory()
{
    _eeprom = uEEPROMLib(EEPROM_CONFIG::I2C_ADDRESS);
}
EEPROMMemory::~EEPROMMemory() {}

void EEPROMMemory::initialize_eeprom()
{
    if (PLS::LOGGING)
    {
        Serial.println(F("Initializing RTC EEPROM module..."));
    }
}

bool EEPROMMemory::write_to_eeprom(const uint8_t address, uint8_t data)
{

    if (!_eeprom.eeprom_write(address, data))
    {
        if (PLS::LOGGING)
        {
            Serial.println("Failed to store data");
        }
        return false;
    }
    else
    {
        if (PLS::LOGGING)
        {
            Serial.println("Data correctly stored");
        }
        return true;
    }
}

uint8_t EEPROMMemory::read_from_eeprom(const uint8_t address)
{
    uint8_t data = _eeprom.eeprom_read(address);

    if (PLS::LOGGING)
    {
        Serial.print(F("Collected data: "));
        Serial.print(data);
        Serial.print(F(" from address: "));
        Serial.println(address);
    }
    return data;
}