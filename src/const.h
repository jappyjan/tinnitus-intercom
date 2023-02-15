#define BLE_UUID_SERVICE          "d91fdc86-46f8-478f-8dec-ebdc0a1188b2"
#define BLE_UUID_CHARACTERISTIC   "56100987-749a-4014-bc22-0be2f5af59d0"

#ifndef LED_BUILTIN
    #define LED_BUILTIN 22
#endif

#define STATUS_LED_PIN LED_BUILTIN
// #define ERROR_LED_PIN 4

#define DISCOVERY_BUTTON_PIN 21
#define DISCOVERY_BUTTON_PRESSED_STATE HIGH
#define DISCOVERY_BUTTON_HOLD_TIME 3000 // The number of millis for which we must hold the button
#define DISCOVERY_TIMEOUT 30000 // 30 seconds in milliseconds for Timeout
#define BLE_DEVICE_NAME "INCOM"