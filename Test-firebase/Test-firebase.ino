#include <WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include "HttpClient.h"

// WiFi network credentials
const char* ssid = "DAE-WIRELESS";
const char* password = "WelcometoDAE";

// Firebase project configuration
/*const char* FIREBASE_HOST = "arduino-4fc81.firebaseio.com";
const char* FIREBASE_AUTH = "zjMFgycSNRkN5RwwHwQHBFBYjbvl2gBvz8GQWHjj";
FirebaseData data;*/
//ArduinoHttpClient_h http;
 
void setup() {
  HttpClient http;

  Serial.begin(9600);

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}


String url= "https://arduino-4fc81-default-rtdb.firebaseio.com/test.json";  
http.setTimeout(1000);
http.begin(url);
  // Issue the HTTP GET request.
int status = http.GET();
if (status <= 0) {
  Serial.print("HTTP error: %s\n", 
      http.errorToString(status).c_str());
  return;
}
}
}
// Read the response.
/*String payload = http.getString();
Serial.println("Got HTTP response:");
Serial.println(payload);test.json";  http.setTimeout(1000);
http.begin(url);
// Issue the HTTP GET request.
int status = http.GET();
if (status <= 0) {
  Serial.printf("HTTP error: %s\n", 
      http.errorToString(status).c_str());
  return;
}
// Read the response.
String payload = http.getString();
Serial.println("Got HTTP response:");
Serial.println(payload);
}
*/