#pragma once
#ifndef FLOAT_TYPES_H
#define FLOAT_TYPES_H



/*
Inspiring by: https://forum.arduino.cc/t/how-to-use-numbers-with-16-decimal-places-in-arduino/865483/12

FLoat64 library src: https://github.com/mmoller2k/Float64/tree/master

Check if it works well on Arduino AVR, STM32 and ESP32


// --------------------------- example code

#include <Float64.h>

f64 x[10] ;
int r =  4;

void setup()
{
  Serial.begin(115200);
  delay(200);
  Serial.println();
  Serial.println();

  // x[1] = f64(0x3fe944aa, 0xa234953c); // 0.789632145698 converted with https://gregstoll.com/~gregstoll/floattohex/
  x[1] = atof64("0.789632145698");
  
  x[1].setDecs(16);  // Set number of decimal places to display
  Serial.println(x[1]);

  for (int i = 2; i < 10 ; i++)
  {
//    Serial.println("Calculating...");
//    Serial.flush();
    x[i] = f64(r) * (x[i - 1] * (f64(1) - x[i - 1]));
//    Serial.println("Calculated.");
//    Serial.flush();
    x[i].setDecs(16);
    Serial.println(x[i]);
//    Serial.println("Printed.");
//    Serial.flush();
  }
}

void loop() {}
*/

#endif // FLOAT_TYPES_H