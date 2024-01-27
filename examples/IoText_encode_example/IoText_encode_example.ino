#include "IoText.h"

IoText iot_ext;

using namespace std;


void setup() {
  Serial.begin(57600);

  string output = iot_ext.encode_test();

  Serial.print("IoText build string:");
  Serial.println(output.c_str());
}

void loop() {
}