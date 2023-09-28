#ifndef DOORBELL2WP_H
#define DOORBELL2WP_H

#include <Arduino.h>
#include <HTTPClient.h>

extern String apiKey;
extern String phone_number;
extern int incoming_signal;

extern String messages[6];
extern const int pinDeEntrada;
extern String url;

void doorbell2wp_setup();
void doorbell2wp_loop();
void message_to_whatsapp(String message);
void postData();
String urlencode(String str);

#endif
