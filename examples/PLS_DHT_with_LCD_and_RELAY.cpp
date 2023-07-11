#include <Arduino.h>
#include <PlantLightSystem.h>

PlantLightSystem pls;

void setup()
{
    Serial.begin(9600);

    pls.initialize_LCD();
    pls.initialize_DHT();

    int relay_pins[RELAY::NUMBER_OF_CHANNELS] = {2, 3, 4, 6};
    // pls.initialize_relay(relay_pins);
}

void loop()
{

    pls.change_relay_state_on_pin(2, "ON");
    pls.change_relay_state_on_pin(6, "ON");

    // Check DHT sensor for errors
    if (int check_code = pls.get_dht_data() != DHT::SUCCESS)
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
    pls.show_message(PLS::MESSAGE_INFO, message);

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
    pls.show_message(PLS::MESSAGE_INFO, message);

    delay(2500);
}
