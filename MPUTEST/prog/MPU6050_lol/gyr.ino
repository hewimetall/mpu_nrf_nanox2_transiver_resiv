

void recordGyroRegisters() {
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

void processGyroData() {
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
