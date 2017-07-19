#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <VL6180X.h>
#include <Servo.h>

VL6180X sensor;

#define TCAADDR 0x70

Servo FrontRight;
Servo FrontLeft;
Servo RearRight;
Servo RearLeft;

void tcaselect(uint8_t i) {
  if (i > 7) return;
 Wire.beginTransmission(TCAADDR);
 Wire.write(1 << i);
 Wire.endTransmission();  
}

int fr;
int fl;
int rr;
int rl;

void setup() {
  Serial.begin(9600);
  Wire.begin();

 FrontRight.attach(6);
 FrontLeft.attach(5);
 RearRight.attach(9);
 RearLeft.attach(10);
  
tcaselect(2);
  sensor.init();
  sensor.configureDefault();
  sensor.setTimeout(500);
  
  /* Initialise the 2nd sensor */
 tcaselect(3);  
  sensor.init();
  sensor.configureDefault();
  sensor.setTimeout(500);

   /* Initialise the 3th sensor */
 tcaselect(4);
  sensor.init();
  sensor.configureDefault();
  sensor.setTimeout(500);

  /* Initialise the 4th sensor */
 tcaselect(5);
  sensor.init();
  sensor.configureDefault();
  sensor.setTimeout(500);
}

void loop() {
  
 tcaselect(2);
Serial.print("Front Right Distance: ");
 Serial.println(sensor.readRangeSingle());
 int fr = sensor.readRangeSingle()-80;
 fr = map(fr, 0, 255, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
 Serial.print(fr);
FrontRight.write(fr);

 tcaselect(3);
Serial.print("Front Left Distance: ");
 Serial.println(sensor.readRangeSingle());
FrontLeft.write(sensor.readRangeSingle());
 
 tcaselect(4);
Serial.print("Rear Right Distance: ");
 Serial.println(sensor.readRangeSingle());
RearRight.write(sensor.readRangeSingle());
  
 tcaselect(5);
Serial.print("Rear Left Distance: ");
 Serial.println(sensor.readRangeSingle());
RearLeft.write(sensor.readRangeSingle());

}

