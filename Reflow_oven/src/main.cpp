#include <Arduino.h>
#include <constants.h>


void setup() {

  // put your setup code here, to run once:
  pinMode(HEAT_1, OUTPUT);
  pinMode(HEAT_2, OUTPUT);
  pinMode(HEAT_3, OUTPUT);
  pinMode(TEMP_SENSOR, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(3000);
  digitalWrite(HEAT_1, HIGH);
  delay(3000);
  digitalWrite(HEAT_1, LOW);

}