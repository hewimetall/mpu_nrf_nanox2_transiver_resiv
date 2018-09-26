
import processing.serial.*;


float pitch, roll,foll;

float position;

Serial myPort;

void setup() {

size(400, 400, P3D); 

position = width/2;

println(Serial.list());

myPort = new Serial(this, "/dev/ttyUSB0", 9600);

myPort.bufferUntil('\n');
}


void draw () {
background(#20542E);
fill(#79BF3D);

disk();
delay(1);
}

void disk() {
translate(position, position, position);
rotateX(roll+PI/2);
rotateY(pitch);
//rotateZ(foll);
fill(#79BF3D);

ellipse(0, 0, width/4, width/4);

fill(#20542E);

text(pitch*180/PI + "," + roll*180/PI, -40, 10, 1);
}
void serialEvent(Serial myPort) { 
// read the serial buffer:
String myString = myPort.readStringUntil('\n');
// if you got any bytes other than the linefeed:
if (myString != null) {
myString = trim(myString);
// split the string at the commas
String items[] = split(myString, ',');
  if (items.length > 1) {
    pitch = float(items[1]);
    roll = float(items[0]);
    foll=float(items[2]);
    }
  }
}
