#include <Arduino.h>
#include "Wire.h"
#include "SPI.h"
#include "../lib/RF24-master/RF24.h"
#include "../lib/RF24-master/nRF24L01.h"

RF24 radio(9, 10);       // CE and CSN
const byte rxAddr[6] = "00001";       // адрес

int count = 0;

void setup()
{
        Serial.begin(115200);
        radio.begin();
        radio.setPALevel(RF24_PA_MAX);
        radio.setDataRate(RF24_1MBPS);
        radio.openReadingPipe(0, rxAddr);
        radio.startListening();
        delay(100);
}

void loop()
{
        if (radio.available())
        {
                char text[32] = {0};
                radio.read(&text, sizeof(text));
                Serial.print(text);
        }
}
