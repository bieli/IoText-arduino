#include "IoText.h"

IoText iot_ext;

void setup() {
  Serial.begin(57600);

  String device_name = "DEVICE_NAME";

  char* output = iot_ext.build(123123123, (char*) device_name.c_str());

  Serial.print("IoText build string:");
  Serial.println(output);
}

void loop() {
}