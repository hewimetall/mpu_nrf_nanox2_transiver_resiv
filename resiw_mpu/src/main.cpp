#include "Wire.h"
#include "SPI.h"
#include "../lib/RF24-master/RF24.h"
#include "../lib/RF24-master/nRF24L01.h"
#include "../lib/CLASSMPU6050.h"
/// transiver
MPU6050 mpu;
RF24 radio(9, 10);       // CE and CSN

const byte rxAddr[6] = "00001";        // адрес

void setup()
{
        radio.begin();
        radio.setPALevel(RF24_PA_MAX);
        radio.setDataRate(RF24_1MBPS);
        radio.setRetries(15, 15);
        radio.openWritingPipe(rxAddr);
        radio.stopListening();
        mpu.init();
}

void loop()
{
        mpu.recordAccelRegisters();
        mpu.recordGyroRegisters();
        mpu.pacet(2);
        mpu.pacet(0);
        radio.write(mpu.pacetTrinssiverBuf,sizeof(mpu.pacetTrinssiverBuf));
}
