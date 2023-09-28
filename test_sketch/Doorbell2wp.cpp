#include <HTTPClient.h>
#include "Doorbell2wp.h"


String apiKey = "9511115";       // Add your Token number that bot has sent you on WhatsApp messenger
String phone_number = "+4917657704802"; // Add your WhatsApp app registered phone number (same number that bot send you in url)
int incoming_signal = 0;

String messages[6] = {
    "Someone rang the doorbell.",
    "There's someone at the door.",
    "The doorbell just rang.",
    "You have a visitor at the door.",
    "Someone is waiting outside.",
    "A guest has arrived."};
const int pinDeEntrada = 4;

String url; // url String will be used to store the final generated URL
void doorbell2wp_setup()
{
  pinMode(pinDeEntrada, INPUT);
  randomSeed(analogRead(0)); // start random number generator
  // use message_to_whatsapp function to send your own message
  message_to_whatsapp("Doorbell Connected");
  delay(50);
  

}

// the modded doorbell uses polling to constantly check if the signal came
// I read the signal with a GPIO Touch pin from the ESP32
// this is also a polling and checks every 350ms if the signal came
// if the circuit reads 4 times in a row that signal came (This to avoid false positives)
// a Whatsapp message will be sent

void doorbell2wp_loop()
{
  int estadoPin = digitalRead(pinDeEntrada);

  if (estadoPin == LOW)
  {
    incoming_signal++;
  }
  if (estadoPin == HIGH)
  {
    incoming_signal = 0;
  }
  if (incoming_signal >= 4)
  {
    Serial.println("Signal Received");
    int random_index = random(6);
    message_to_whatsapp(messages[random_index]);
    incoming_signal = 0;
  }

}
void message_to_whatsapp(String message) // user define function to send meassage to WhatsApp app
{
  // adding all number, your api key, your message into one complete url
  url = "https://api.callmebot.com/whatsapp.php?phone=" + phone_number + "&apikey=" + apiKey + "&text=" + urlencode(message);

  postData(); // calling postData to run the above-generated url once so that you will receive a message.
}

void postData() // userDefine function used to call api(POST data)
{
  int httpCode;              // variable used to get the responce http code after calling api
  HTTPClient http;           // Declare object of class HTTPClient
  http.begin(url);           // begin the HTTPClient object with generated url
  httpCode = http.POST(url); // Finaly Post the URL with this function and it will store the http code
  if (httpCode == 200)       // Check if the responce http code is 200
  {
    Serial.println("Sent ok."); // print message sent ok message
  }
  else // if response HTTP code is not 200 it means there is some error.
  {
    Serial.println("Error."); // print error message.
  }
  http.end(); // After calling API end the HTTP client object.
}

String urlencode(String str) // Function used for encoding the url
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++)
  {
    c = str.charAt(i);
    if (c == ' ')
    {
      encodedString += '+';
    }
    else if (isalnum(c))
    {
      encodedString += c;
    }
    else
    {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9)
      {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9)
      {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      // encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}