#include <WiFi.h>
#include "Doorbell2wp.h"
#include "webserver.h"

TaskHandle_t Task1;
TaskHandle_t Task2;

const char *ssid = "";     // Add your WiFi ssid
const char *password = ""; // Add your WiFi password

const int BUILD_IN_LED = 2;

void setup()
{
  pinMode(BUILD_IN_LED, OUTPUT);

  Serial.begin(115200);
  // wifi connection
  connect_to_wifi();

  ////

  xTaskCreatePinnedToCore(
      Task1code, /* Task function. */
      "Task1",   /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      1,         /* priority of the task */
      &Task1,    /* Task handle to keep track of created task */
      0);        /* pin task to core 0 */
  delay(500);

  xTaskCreatePinnedToCore(
      Task2code, /* Task function. */
      "Task2",   /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      1,         /* priority of the task */
      &Task2,    /* Task handle to keep track of created task */
      1);        /* pin task to core 1 */
  delay(500);
}

// Task1code: blinks an LED every 1000 ms
void Task1code(void *pvParameters)
{
  // first programm setup
  doorbell2wp_setup();
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for (;;)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      connect_to_wifi();
    }
    doorbell2wp_loop();
    delay(300);
  }
}

void Task2code(void *pvParameters)
{
  webserver_setup();
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for (;;)
  {
    webserver_loop();
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
}

void connect_to_wifi()
{
  WiFi.begin(ssid, password); // Try to connect with the given SSID and PSS
  digitalWrite(BUILD_IN_LED, HIGH);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  { // Wait until WiFi is connected
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to the WiFi network");
  digitalWrite(BUILD_IN_LED, LOW);
}
