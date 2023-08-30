#include "IoText.h"

IoText iot_ext;

void setup() {
  Serial.begin(57600);
  iot_ext.build(123123123, "DEVICE_NAME");

  Serial.print("IoText build string: TODO!!!");
}

void loop() {
}