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
  Serial.print("\tRangeFR: ");
  Serial.print(sensor.readRangeSingle());
 
fr = (75-sensor.readRangeSingle())*10;
Serial.print("RangeFR: ");
  Serial.print(fr);
  FrontRight.write(fr);
    Serial.println();
  
 tcaselect(3);
  Serial.print("\tRangeFL: ");
  Serial.print(sensor.readRangeSingle());
   fl = (75-sensor.readRangeSingle())*10;
Serial.print("RangeFL: ");
  Serial.print(fl);
  FrontLeft.write(fl);
     Serial.println();

 tcaselect(4);
  Serial.print("\tRangeRR: ");
  Serial.print(sensor.readRangeSingle());
     rr = (80-sensor.readRangeSingle())*10;
Serial.print("RangeRR: ");
  Serial.print(rr);
  RearRight.write(rr);
  Serial.println();

  
 tcaselect(5);
  Serial.print("\tRangeRL: ");
  Serial.print(sensor.readRangeSingle());
     rl = (75-sensor.readRangeSingle())*10;
Serial.print("RangeRL: ");
  Serial.print(rl);
  RearLeft.write(rl);
    Serial.println();

}

