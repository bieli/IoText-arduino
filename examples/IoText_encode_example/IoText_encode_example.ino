// Demostrates how build one record with the IoText data protocol library
// Author: Marcin Bielak

#include "IoText.h"

IoText iot_ext;

using namespace std;


void setup() {
  Serial.begin(115200);

  string output = iot_ext.encode_test();

  Serial.print("IoText build string:");
  Serial.println(output.c_str());
}

void loop() {
}