#include <Wire.h>
#include <MQ2.h>

#define SMOKE_SENSOR A0
int lpg, co, smoke;
MQ2 mq2(SMOKE_SENSOR);

void setup() {
  Serial.begin(9600);
  mq2.begin();
  //Serial.println("Warming Up !!!");
  //delay(20000); // allow the MQ-sensor to warm up
}


void loop() {
  Serial.println(analogRead(SMOKE_SENSOR));
  //set it false if you don't want to print the values in the Serial

  float* values= mq2.read(true);
  //lpg = values[0];
  lpg = mq2.readLPG();
  //co = values[1];
  co = mq2.readCO();
  //smoke = values[2];
  smoke = mq2.readSmoke();

  delay(500);
}