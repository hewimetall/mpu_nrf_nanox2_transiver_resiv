
#include <Wire.h>
long accelX, accelY, accelZ;
float angle_accX[3], angle_accY[3], angle_accZ[3];

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
//float RAD_TO_DEG=57.3;
float Alf=0.2,Fx[10],Fy[10]={0, };

 uint32_t old_time,new_time; 

void setup() {
  Serial.begin(115200);
  Wire.begin();
  setupMPU();
     old_time = micros(); 
}


void loop() {
  recordAccelRegisters();
  recordGyroRegisters();
  
  /*
 Serial.print(angle_accX[2]);Serial.print(",");
 Serial.print(angle_accY[2]);Serial.print(",");
 Serial.print(angle_accZ[2]);//Serial.print("\n");
 Serial.print(rotX[1]);Serial.print(",");
 Serial.print(rotY[1]);Serial.print(",");
 Serial.print(rotZ[1]);Serial.print("\n");
 */

 /*Fx[0]=ComplementaryFilter(Fx[0],rotX,angle_accX[2],0.98);
  Serial.print(angle_accX[2]);Serial.print(",");
    Serial.print(angle_accY[2]);Serial.print(",");
      Serial.print(angle_accZ[2]);Serial.print(",");*/
 Serial.print(rotX/angle_accY[2]);Serial.print(",");
    Serial.print(rotY/angle_accY[2]);Serial.print(",");
      Serial.print(rotZ/angle_accZ[2]);
//Serial.print("\n");
/* Serial.print(rotX);Serial.print(",");
    Serial.print(rotY);Serial.print(",");
      Serial.print(rotZ);*/

Serial.print("\n");
/**/
  delay(1);
}

