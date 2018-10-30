#include "../lib/CLASSMPU6050.h"
#include "Wire.h"
#include <Arduino.h>
MPU6050 mpu;
void setup() {
        Serial.begin(9600);
        Wire.begin();
        mpu.init();
}


void loop() {
        mpu.recordAccelRegisters();
        mpu.recordGyroRegisters();

        mpu.pacet(1);


}
