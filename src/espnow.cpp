#include <Arduino.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

#include "espnow.h"

enum message_type {
  MESSAGE_TYPE_JOIN = 1,
  MESSAGE_TYPE_WELCOME = 2
};

unsigned long lastSend = millis();
const int SEND_DELAY = 4000;

struct struct_message {
  uint8_t type;
  int payloadInt;
  char* mac_address;
};

struct_message outgoingMessage;
struct_message incomingMessage;

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

inline void onEspNowReceive(const uint8_t *incoming_mac_addr, const uint8_t *data, int data_len) {  
  memcpy(&incomingMessage, data, sizeof(incomingMessage));

  // Format our MAC address
  String my_mac_addr_str = WiFi.macAddress();

  if (String(incomingMessage.mac_address).equals(my_mac_addr_str)) {
    return;
  }

  Serial.println("Received: " + String(incomingMessage.payloadInt));
}

inline void broadcast(message_type type, int payload) {
  outgoingMessage.type = type;
  outgoingMessage.payloadInt = payload;

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &outgoingMessage, sizeof(outgoingMessage));
  if (result != ESP_OK) {
    Serial.print("Error broadcasting the data: ");
    Serial.println(result);
  }
}

int counter = 0;
inline void broadcastTestMessage() {
  counter++;
  Serial.println("Sending: " + String(counter));
  broadcast(MESSAGE_TYPE_JOIN, counter);
}

void ESPNOW::setup() {
  Serial.println("Initiate ESP-NOW");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  outgoingMessage.mac_address = const_cast<char*>(WiFi.macAddress().c_str());
  Serial.printf("My MAC address: %s \n", outgoingMessage.mac_address);

  Serial.println("Initiating ESP-NOW");
  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
  }

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  peerInfo.ifidx = wifi_interface_t::WIFI_IF_STA;

  if (esp_now_add_peer(&peerInfo) != 0) {
    Serial.println("Failed to add peer");
  }

  esp_now_register_recv_cb(onEspNowReceive);

  lastSend = millis();

  Serial.println("ESP-NOW initiated");
}

void ESPNOW::loop() {
    if ((lastSend + SEND_DELAY) > millis()) {
        return;
    }

    lastSend = millis();
    broadcastTestMessage();
}