#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>
#include <WiFi.h>

extern String header;
extern String output26State;
extern String output27State;
extern const int output26;
extern const int output27;

void webserver_setup();
void webserver_loop();

#endif
