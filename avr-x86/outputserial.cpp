/*
    fake86 port on Arduino
    outputserial.c - From https://stackoverflow.com/questions/66632376/how-to-call-serial-print-from-c-file-in-arduino-ide
    Copyright (C) 2021 @raspiduino
*/

#include <Arduino.h>
extern "C" {
  #include "outputserial.h"
}

void my_log(char *msg) {
  Serial.println(msg);
}
