
void setupMPU(){
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
}

float clearAccelDate(float *x,float alf){
  *(x+1)=*(x+2);
  *(x+2)=*(x+1)+(*(x)-*(x+1))*alf;
  return *(x+2);
  
}
float ComplementaryFilter(float F,float G,float A,float alf)
{
  return (G+F)*alf+(1-alf)*A;
}
