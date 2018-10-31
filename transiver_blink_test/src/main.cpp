#include <Arduino.h>
#include "Wire.h"
#include "SPI.h"
#include "../lib/RF24-master/RF24.h"
#include "../lib/RF24-master/nRF24L01.h"

RF24 radio(9, 10);       // CE and CSN
const byte rxAddr[6] = "00001";       // адрес

int count = 0;
struct pacet {
 double e[3]={0,0,0};// rotX=e[0] rotY=e[0] rotZ=e[0]
 char text[32] = {0};

}Pac; //Тут стоит точка с запятой!

int split ()
{
char str[32];
strcpy(str,Pac.text);
 double *p = Pac.e;
 char * pch = strtok (str,",\n"); // во втором параметре указаны разделитель (пробел, запятая, точка, тире)

 while (pch != NULL)                         // пока есть лексемы
 {

		 *p=atof(pch);p++;
		 pch = strtok (NULL, " ,.-");


 }
 return 0;
}

void setup()
{
        Serial.begin(115200);
        radio.begin();
        radio.setPALevel(RF24_PA_MAX);
        radio.setDataRate(RF24_1MBPS);
        radio.openReadingPipe(0, rxAddr);
        radio.startListening();
        delay(100);
				pinMode(A0, OUTPUT);  // установка режима дискретного вывода для A3
digitalWrite(A0, 1000);   // установка низкого состояния на выходе A3

}

void loop()
{ int16_t ay_raw;
        if (radio.available())
        {
          radio.read(ay_raw, sizeof(ay_raw));
					digitalWrite(A0, int(500+ay_raw/20));   // установка низкого состояния на выходе A3
					Serial.print(ay_raw);Serial.print("\n");
        }
}
