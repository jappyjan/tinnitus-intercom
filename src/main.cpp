#include <Arduino.h>

#include "const.h"
#include "espnow.h"

void setup() {
  Serial.println("Setup started...");
  Serial.begin(115200);

  ESPNOW::setup();
}

void loop() {
  ESPNOW::loop();
  delay(100);
}
