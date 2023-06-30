#include "PlantLightSystem.h"


/**
	PlantLightSystem
*/

PlantLightSystem::PlantLightSystem(){}

PlantLightSystem::~PlantLightSystem(){}

/**
	DHT
*/

/**
 * @brief DHT sensor initialization
*/
void PlantLightSystem::initialize_DHT(SimpleDHT11 *DHT_sensor){
    Serial.print(F("Initializing DHT sensor..."));
    this->_DHT_Sensor = *DHT_sensor;
}

/**
 * @brief Get data from DHT sensor and store it in class attributes
*/
int PlantLightSystem::get_dht_data(){

    int8_t error_check = DHT_SUCCESS;

    if ((error_check = this->_DHT_Sensor.read2(&this->_temperature, &this->_humidity, NULL)) != DHT_SUCCESS) {
        // Bitwise AND error selection
        int dht_error = SimpleDHTErrCode(error_check);

        delay(2000);
        return dht_error;

    }
    return DHT_SUCCESS;
}

/**
 * @brief Get temperature
*/
float PlantLightSystem::get_temperature(){
    Serial.print(F("Temperature = "));
    Serial.print(this->_temperature);
    Serial.println(F(" *C"));

    return this->_temperature;
}

/**
 * @brief Get humidity
*/
float PlantLightSystem::get_humidity(){
    Serial.print(F("Humidity = "));
    Serial.print(this->_humidity);
    Serial.println(F(" %"));

    return this->_temperature;
}