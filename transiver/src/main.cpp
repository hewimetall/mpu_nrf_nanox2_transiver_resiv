#include <Arduino.h>
#include "Wire.h"
#include "SPI.h"
#include "../lib/RF24-master/RF24.h"
#include "../lib/RF24-master/nRF24L01.h"

RF24 radio(33,34);        // указать номера пинов, куда подключаются CE и CSN
const byte rxAddr[6] = "00001";       // адрес

int count = 0;

void setup()
{
        Serial.begin(9600);
        radio.begin();
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
                Serial.print("START");
                Serial.print(text);
        }
}
