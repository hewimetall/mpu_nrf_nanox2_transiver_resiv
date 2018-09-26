

void recordAccelRegisters() {
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


void processAccelData(){  
  angle_accX[0]= atan2(-accelX, sqrt(accelY*accelY + accelZ*accelZ));
  angle_accY[0]= atan2(accelY, accelZ);
  angle_accZ[0]=(atan2(accelZ , sqrt(accelX * accelX +accelY*accelY)));
  clearAccelDate(angle_accX,Alf);
  clearAccelDate(angle_accY,Alf);
  clearAccelDate(angle_accZ,Alf);
}

