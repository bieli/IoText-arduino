#include "IoText.h"

IoText iot_ext;

void setup() {
  Serial.begin(57600);

  String device_name = "DEVICE_NAME";

  iot_ext.build(123123123, device_name);

  Serial.print("IoText build string: TODO!!!");
}

void loop() {
}