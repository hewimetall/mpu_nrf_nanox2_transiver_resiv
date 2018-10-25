#include <Wire.h>
#include <Arduino.h>

class MPU6050
{
private:
/* data */
long accelX, accelY, accelZ;// input processAccelData -> gyro_angle_acc{x,y,z}
float angle_accX[3], angle_accY[3], angle_accZ[3];// input pacet local petly in clearAccelDate(it filters)

long gyroX, gyroY, gyroZ;// input processGyroData -> gyro_angle_{x,y,z} and rot{x,y,z}
float rotX, rotY, rotZ; // input pacet no filters
//float RAD_TO_DEG=57.3;
float Alf=0.2; //input clearAccelDate
//,Fx[10],Fy[10]={0, };-!
uint32_t old_time,new_time; // this time start and restart loop
String pacetTrinssiver;   // this pacet transiver in func pacet

public:
char pacetTrinssiverBuf[19];   // this buff pacet transiver in func pacet


void init(){ // this func setup on start use to one !!!!

        Wire.setClock(400000);
        Wire.beginTransmission(0b1101000);
        Wire.write(0x6B);
        Wire.write(0b00000000);
        Wire.endTransmission();
        Wire.beginTransmission(0b1101000);
        Wire.write(0x1B);
        Wire.write(0x00000000); // Установка чивствительности герископа 1000 deg./s
        Wire.endTransmission();
        Wire.beginTransmission(0b1101000);
        Wire.write(0x1C);
        Wire.write(0b00000000); //Установка чувствительности акцелерометра +/- 2g
        Wire.endTransmission();
        old_time = micros();
}

void recordAccelRegisters() { // this func read register (3B - 40)
        Wire.beginTransmission(0b1101000);
        Wire.write(0x3B);
        Wire.endTransmission();
        Wire.requestFrom(0b1101000,6); //отправка чтения регистров (3B - 40)
        while(Wire.available() < 6);
        accelX = Wire.read()<<8|Wire.read();
        accelY = Wire.read()<<8|Wire.read();
        accelZ = Wire.read()<<8|Wire.read();
        processAccelData();

}


void processAccelData(){ // this func input angel date
        angle_accX[0]= atan2(-accelX, sqrt(accelY*accelY + accelZ*accelZ));
        angle_accY[0]= atan2(accelY, accelZ);
        angle_accZ[0]=(atan2(accelZ, sqrt(accelX * accelX +accelY*accelY)));
        clearAccelDate(angle_accX,Alf);
        clearAccelDate(angle_accY,Alf);
        clearAccelDate(angle_accZ,Alf);
}

float clearAccelDate(float *x,float alf){ // this filters
        *(x+1)=*(x+2);
        *(x+2)=*(x+1)+(*(x)-*(x+1))*alf;
        return *(x+2);

}

void recordGyroRegisters() {// this func read gyro register
        Wire.beginTransmission(0b1101000);
        Wire.write(0x43);
        Wire.endTransmission();
        Wire.requestFrom(0b1101000,6);
        while(Wire.available() < 6);
        gyroX = Wire.read()<<8|Wire.read();
        gyroY = Wire.read()<<8|Wire.read();
        gyroZ = Wire.read()<<8|Wire.read();
        processGyroData();
}

void processGyroData() { // this func input rotate date
        rotX =(double)gyroX / (131.0);
        rotY =(double)gyroY / (131.0);
        rotZ =(double)gyroZ / (131.0);
        //  timer=micros();

        // Compute the (filtered) gyro angles
        /*  float dt =(t_now - get_last_time())/1000.0;
           float gyro_angle_x = gyro_x*dt + get_last_x_angle();
           float gyro_angle_y = gyro_y*dt + get_last_y_angle();
           float gyro_angle_z = gyro_z*dt + get_last_z_angle();*/

}
void pacet(int16_t t){// this func transmission the date on uars
        if(t==1) {
                Serial.print("\n");
                Serial.print(rotX); Serial.print(",");
                Serial.print(rotY); Serial.print(",");
                Serial.print(rotZ);
        }
        else{
                pacetTrinssiver = String(rotX/angle_accY[2]) +"," +String(rotY/angle_accY[2]) + "," +String(rotZ/angle_accZ[2]) + "\n";
                pacetTrinssiver.toCharArray(pacetTrinssiverBuf, 19 );
        }
        /**/
        delay(1);
};
};
