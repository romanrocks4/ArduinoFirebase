#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
HTTPClient http;
void setup() {
  // Fill in your SSID and password below
  wifiMulti.addAP(“DAE-WIRELESS”, “WelcometoDAE”);
}