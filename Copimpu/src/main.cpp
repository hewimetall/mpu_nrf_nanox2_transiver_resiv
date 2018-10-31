#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "SPI.h"
#include "../lib/RF24-master/RF24.h"
#include "../lib/RF24-master/nRF24L01.h"
#define T_OUT 20

RF24 radio(9, 10);       // CE and CSN

const byte rxAddr[6] = "00001";        // адрес

MPU6050 accel;

unsigned long int t_next;

void setup() {
    Serial.begin(9600);
    accel.initialize();
    Serial.println(accel.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

            radio.begin();
            radio.setPALevel(RF24_PA_MAX);
            radio.setDataRate(RF24_1MBPS);
            radio.setRetries(15, 15);
            radio.openWritingPipe(rxAddr);
            radio.stopListening();
}

void loop() {
    long int t = millis();
    if( t_next < t ){
        int16_t ax_raw, ay_raw, az_raw, gx_raw, gy_raw, gz_raw;

        t_next = t + T_OUT;
        accel.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);

        Serial.println(ay_raw); // вывод в порт проекции ускорения на ось Y
        radio.write(ay_raw,sizeof(ay_raw));
    }
}
