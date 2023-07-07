#include <Arduino.h>
#include <PlantLightSystem.h>
#include <SoftwareSerial.h>
#include "MemoryFree.h"

PlantLightSystem pls;

SoftwareSerial BluetoothSerial(HC05::RX_PIN, HC05::TX_PIN);


uint8_t relay_pins[RELAY::NUMBER_OF_CHANNELS] = {2, 3, 4, 6};

void setup()
{
    Serial.begin(PLS::BAUD_RATE);
    BluetoothSerial.begin(HC05::BAUD_RATE);

    pls.initialize_LCD();
    pls.initialize_DHT();
    pls.initialize_relay(relay_pins);
    pls.initialize_bluetooth();

    pls.show_welcome_message((char *)"All modules ready! Welcome!");
}

void loop()
{

    // read command
    char *message = new char[COMMAND::MAX_LENGTH];
    static unsigned int message_pos = 0;

    while (BluetoothSerial.available())
    {
        char inByte = BluetoothSerial.read();

        if (inByte != '\n' && (message_pos < COMMAND::MAX_LENGTH - 1))
        {
            message[message_pos] = inByte;
            message_pos++;
        }
        else
        {
            message[message_pos-1] = '\0';
            message_pos = 0;
        }
    }

    uint16_t cmd = pls.validate_command(message);
    uint8_t lamp_response = pls.execute_bluetooth_lamp_command(cmd);

    if ((String(lamp_response) == String(COMMAND::STATUS_SUCCESS))){
        BluetoothSerial.println((String(lamp_response)));
    }

    float dht_response = pls.execute_bluetooth_dht_command(cmd);
    if(dht_response > 1.00f){
        BluetoothSerial.println((String(dht_response)));
    }

}
