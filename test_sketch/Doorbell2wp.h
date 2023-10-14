#ifndef DOORBELL2WP_H
#define DOORBELL2WP_H

#include <Arduino.h>
#include <HTTPClient.h>

extern String apiKey;
extern String phone_number;
extern String apiKey2;
extern String phone_number2;
extern int incoming_signal;

extern String messages[6];
extern const int pinDeEntrada;
extern const int ledPin;
extern const int alertLED;
extern String url;

void doorbell2wp_setup();
void doorbell2wp_loop();
void message_to_whatsapp(String message, String apiKey, String phone_number);
void postData();
void ring_doorbell();
void send_message(String message);
String urlencode(String str);

#endif
