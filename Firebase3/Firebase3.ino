#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "DAE-WIRELESS";          // Your WiFi SSID
char pass[] = "WelcometoDAE";      // Your WiFi password

char server[] = "https://arduino-4fc81-default-rtdb.firebaseio.com";  // Your Firebase project URL
WiFiClient client;

void setup() {
  Serial.begin(9600);
  
  // Attempt to connect to WiFi network
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    delay(5000);   // Adjust the delay time as needed
  }

  Serial.println("Connected to WiFi");

  // Read data from Firebase
  readFirebaseData();
}

void loop() {
  // You can add your main program logic here
}

/*void readFirebaseData() {
  if (client.connect(server, 443)) {
    Serial.println("Connected to Firebase"); 
  
    // Make a GET request to Firebase to read data
    client.print("GET /test HTTP/1.1\r\n");
    client.print("Content-Type: application/json\r\n");

    client.print("Host: ");
    client.print(server);
    client.print("\r\n");
    client.print("Connection: close\r\n");
    client.print("\r\n");

    delay(500);
    */
   void readFirebaseData() {
  if (client.connect(server, 443)) {
    Serial.println("Connected to Firebase");

    // Make a POST request to Firebase
    client.print("POST /test HTTP/1.1\r\n");
    client.print("Content-Type: application/json\r\n");

    // Replace this with your actual JSON data
    String jsonData = "{"/test":"hello"}";
    Serial.print(jsonData);
    client.print("Content-Length: ");
    client.print(jsonData.length());
    client.print("\r\n");

    client.print(jsonData);

    delay(500);


    // Read and print the response from Firebase
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }

    Serial.println("\nClosing connection");
    client.stop();
  } else {
    Serial.println("Connection to Firebase failed");
  }
}

