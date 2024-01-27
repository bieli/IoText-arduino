#include "IoText.h"

IoText iot_ext;

using namespace std;


void setup() {
  Serial.begin(57600);

  iot_ext.encode_test();
  // string output = IoText::encode_test();

  Serial.print("IoText build string:");
  // Serial.println(output.c_str());
}

void loop() {
}