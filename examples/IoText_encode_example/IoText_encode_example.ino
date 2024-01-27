#include "IoText.h"

IoText iot_ext;

void setup() {
  Serial.begin(57600);

  String output = iot_ext.encode_test();

  Serial.print("IoText build string:");
  Serial.println(output);
}

void loop() {
}