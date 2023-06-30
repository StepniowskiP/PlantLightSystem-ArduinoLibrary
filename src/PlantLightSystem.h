/**
	PlantLightSystem class
*/

#ifndef PLANTLIGHTSYSTEM_h
#define PLANTLIGHTSYSTEM_h

#include <SimpleDHT.h>
#include "constants.h"

class PlantLightSystem{

    private:
        SimpleDHT11 _DHT_Sensor;
        uint32_t _DHT_delay;

        float _temperature;
        float _humidity;

    public:

        PlantLightSystem();
        ~PlantLightSystem();

        /* DHT */
        void initialize_DHT(SimpleDHT11 *DHT_sensor);
        int get_dht_data();
        float get_temperature();
        float get_humidity();
};


#endif /* PLANTLIGHTSYSTEM_h */