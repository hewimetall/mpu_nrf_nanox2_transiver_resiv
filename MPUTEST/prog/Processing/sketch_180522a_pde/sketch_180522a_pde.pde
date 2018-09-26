import processing.serial.*;
float pitch, roll,foll;
float position;
Serial myPort;
void setup() {
size(800, 800, P3D); 
position = width/2;
println(Serial.list());
myPort = new Serial(this, "/dev/ttyUSB1", 9600);
myPort.bufferUntil('\n');
}
void draw () {
background(0);
fill(#79BF3D);
pushMatrix ();
    translate(position, position, position);
    rectMode(CENTER);
    rotateX(roll+PI/2);
    rotateY(pitch);
    rect(0,0, width/4, width/4,5);
popMatrix ();
  fill(83, 175, 93);
  textSize(24);
  text("angles deg", 0, 20);
  text("pitch:",0,45); text(pitch*180/PI, 55,45);
  text("roll:",0,70); text(roll*180/PI, 55,70);
  delay(1);
}


void serialEvent(Serial myPort) {
String myString = myPort.readStringUntil('\n');
if (myString != null) {
myString = trim(myString);
String items[] = split(myString, ',');
  if (items.length > 1) {
    pitch = float(items[1]);
    roll = float(items[0]);
    foll=float(items[2]);
    }
  }
}
