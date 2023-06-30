#include <Arduino.h>
#include <PlantLightSystem.h>

PlantLightSystem pls;

void setup()
{
    Serial.begin(9600);
    pls.initialize_DHT();
}

void loop()
{
    // Check DHT sensor for errors
    if (int check_code = pls.get_dht_data() != DHT_SUCCESS)
    {
        Serial.print(F("Read DHT11 failed, error="));
        Serial.println(check_code);
    }

    // Get humidity ("Humidity = <float> %")
    pls.get_humidity();

    // Get temperature ("Temperature = <float> *C")
    pls.get_temperature();

    delay(2500);
}
