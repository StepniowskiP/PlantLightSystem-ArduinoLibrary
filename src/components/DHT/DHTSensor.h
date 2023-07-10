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

        DHTSensor();
        ~DHTSensor();

        void initialize_DHT();

        uint8_t get_dht_data();

        float get_temperature();
        float get_humidity();

};


#endif /* DHT_SENSOR_H */