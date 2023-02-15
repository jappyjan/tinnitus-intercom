#include <Arduino.h>

#include "const.h"
#include "utils.h"

unsigned long nextFlash; // This will hold the millis() value of our next Flash
#define INTERVAL_FLASH  500 // This is our Flash Interval (500ms, 0.5 seconds)

void Utils::flashBlueLed() {
  if (millis() < nextFlash) { return; } // It isn't time yet, so nothing to do.
  digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN)); // Toggle the LED State
  nextFlash = millis() + INTERVAL_FLASH; // Sets the time it should toggle again.
};

void Utils::setRedLed(bool ledOn) {
    #ifdef ERROR_LED_PIN
        digitalWrite(ERROR_LED_PIN, HIGH);
    #endif
};