#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <SimpleDHT.h>

#include "../../constants.h"

class DHTSensor{

    private:
        SimpleDHT11 _DHT_Sensor11;
        SimpleDHT22 _DHT_Sensor22;

    public:

        float temperature;
        float humidity;
        char str_temperature[8];
        char str_humidity[8];

        DHTSensor();
        ~DHTSensor();

        void initialize_DHT();
        uint8_t get_dht_data();

};


#endif /* DHT_SENSOR_H */