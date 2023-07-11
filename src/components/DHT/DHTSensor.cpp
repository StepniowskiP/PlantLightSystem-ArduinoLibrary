#include "DHTSensor.h"

DHTSensor::DHTSensor()
{
}
DHTSensor::~DHTSensor() {}

/**
 * @brief DHT sensor initialization
 */
void DHTSensor::initialize_DHT()
{
    if (PLS::LOGGING)
    {
        Serial.println(F("Initializing DHT sensor..."));
        Serial.print(F("DHT version: "));
        Serial.println(DHT::TYPE);
    }

    if (DHT::TYPE == 11)
    {
        SimpleDHT11 dht(DHT::PIN);
        _DHT_Sensor11 = dht;
    }
    else if (DHT::TYPE == 22)
    {
        SimpleDHT22 dht(DHT::PIN);
        _DHT_Sensor22 = dht;
    }
    else
    {
        if (PLS::LOGGING)
        {
            Serial.println(F("Wrong DHT sensor type"));
        }
    }
}

/**
 * @brief Get data from DHT sensor and store it in class attributes
 */
uint8_t DHTSensor::get_dht_data()
{

    int8_t error_check = DHT::SUCCESS;
    if (DHT::TYPE == 11)
    {
        if ((error_check = _DHT_Sensor11.read2(&temperature, &humidity, NULL)) != DHT::SUCCESS)
        {
            // Bitwise AND error selection
            error_check = SimpleDHTErrCode(error_check);
            delay(2000);
        }
    }
    else if (DHT::TYPE == 22)
    {
        if ((error_check = _DHT_Sensor22.read2(&temperature, &humidity, NULL)) != DHT::SUCCESS)
        {
            // Bitwise AND error selection
            error_check = SimpleDHTErrCode(error_check);
            delay(2000);
        }
    }

    str_temperature[0] = '\0';
    dtostrf(temperature, 5, 2, str_temperature);

    str_humidity[0] = '\0';
    dtostrf(humidity, 5, 2, str_humidity);

    return error_check;
}
