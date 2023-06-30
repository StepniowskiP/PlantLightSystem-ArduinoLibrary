#include <Arduino.h>
#include <PlantLightSystem.h>

PlantLightSystem pls;

void setup()
{
    Serial.begin(9600);
    pls.initialize_DHT();
    pls.initialize_LCD();
}

void loop()
{
    // Check DHT sensor for errors
    if (int check_code = pls.get_dht_data() != DHT_SUCCESS)
    {
        Serial.print(F("Read DHT11 failed, error="));
        Serial.println(check_code);
    }

    // Temporarily holds data
    char floatVal[5];
    char message[50];

    // Print humidity to LCD ("Humidity = <float> %")
    float humidity = pls.get_humidity();
    dtostrf(humidity, 4, 1, floatVal);
    strcpy(message, "Humidity = ");
    strcat(message, floatVal);
    strcat(message, " %");
    pls.show_message(MESSAGE_INFO, message);

    delay(2000);

    // Clear for second message
    floatVal[0] = (char)0;
    message[0] = (char)0;

    // Print temperature to LCD ("Temperature = <float> *C")
    float temperature = pls.get_temperature();
    dtostrf(temperature, 4, 1, floatVal);
    strcpy(message, "Temperature = ");
    strcat(message, floatVal);
    strcat(message, " *C");
    pls.show_message(MESSAGE_INFO, message);

    delay(2000);
}
