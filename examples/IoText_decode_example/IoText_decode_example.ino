// Demostrates how decode one record with the IoText data protocol library
// Author: Marcin Bielak

#include "IoText.h"

IoText iot_ext;

void setup() {
  Serial.begin(115200);

  String device_name = "DEVICE_NAME";

  //TODO: add decode example
  // char* output = iot_ext.build(millis(), (char*) device_name.c_str());

  Serial.print("IoText build string:");
  // Serial.println(output);
}

void loop() {
}