//including necessary libraries (pitches.h code below) 
#include <WiFiNINA.h>/Users/student/Documents/Arduino/Firebase1/arduino-secrets/arduino_secrets.h
#include "arduino_secrets.h"       //contains wifi cred/Users/student/Documents/Arduino/Firebase1/arduino-secrets/arduino-secrets.inoentials
#include "Firebase_Arduino_WiFiNINA.h"  //Firebase Arduino based on WiFiNINA-install from manage libraries
#include "pitches.h"  //add note library

//notes in the melody
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

//digital pin 5 has a button attached to it, instantiated here
int buttonPin = 5;
//LED_BUILTIN is used as the LED pin of instantiation 
const int ledPin = LED_BUILTIN ;

//note durations. 4=quarter note / 8=eighth note
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

#define FIREBASE_HOST "arduino-4fc81.firebaseio.com"  //Firebase Realtime database URL
#define FIREBASE_AUTH "zjMFgycSNRkN5RwwHwQHBFBYjbvl2gBvz8GQWHjj" //from Firebase Database secrets

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the Wifi radio's status

//Define Firebase data object
FirebaseData firebaseData;
String path = "/NEW";



void setup() {

  //make the button's pin input
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial);  // comment this line if not connected to computer and Serial Monitor


  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 1 seconds for connection:
    delay(1000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network!");
  Serial.println("----------------------------------------");
  printData();
  Serial.println("----------------------------------------");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, SECRET_SSID, SECRET_PASS);
  Firebase.reconnectWiFi(true); //Let's say that if the connection is down, try to reconnect automatically


}

void loop() {
  // wait for 1 second
  delay(1000); //600000ms data every 10min
  printData();
  Serial.println("----------------------------------------");
  //read the input pin
  int buttonState = digitalRead(buttonPin);



// Arduino MKR module sending inputted data to Firebase 
  if (Firebase.setInt(firebaseData, path + "/button", buttonState))
  {
    Serial.println("Insert");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.print("VALUE: ");
    if (firebaseData.dataType() == "int")
      Serial.println(firebaseData.intData());
  }
  else
  {
    Serial.println("ERROR : " + firebaseData.errorReason());
    Serial.println();
  }



// Arduino MKR module receiving inputted data from firebase
  Serial.println("Read a value");
  if (Firebase.getInt(firebaseData, path + "/button"))
  {
    Serial.println("Result of read");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.print("VALUE: ");
    if (firebaseData.dataType() == "int")
      Serial.println(firebaseData.intData());
  }
  else
  {
    Serial.println("ERROR: " + firebaseData.errorReason());
    Serial.println();
  }
  Serial.println("------------------------------------------------------------------------------------");



  //if the button is pressed, sends data to firebase that turns on LED 
  if (firebaseData.intData() == 1) {
    digitalWrite(ledPin, HIGH);
    //iterate over the notes of the melody
    for (int thisNote = 0; thisNote < 8; thisNote++) {

      //to calculate the note duration, take one second. Divided by the note type
      int noteDuration = 1000 / noteDurations [thisNote];
      tone(2, melody [thisNote], noteDuration);

      //to distinguish the notes, set a minimum time between them
      //the note's duration +30% seems to work well
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);


  //if button is pressed, displays RGB LED light 
      // display RGB colours
      WiFiDrv::analogWrite(25, 255);
      WiFiDrv::analogWrite(26, 0);
      WiFiDrv::analogWrite(27, 0);

      delay(50);

      WiFiDrv::analogWrite(25, 0);
      WiFiDrv::analogWrite(26, 255);
      WiFiDrv::analogWrite(27, 0);

      delay(50);

      WiFiDrv::analogWrite(25, 0);
      WiFiDrv::analogWrite(26, 0);
      WiFiDrv::analogWrite(27, 255);

      delay(50);

      WiFiDrv::analogWrite(25, 0);
      WiFiDrv::analogWrite(26, 0);
      WiFiDrv::analogWrite(27, 0);

      delay(50);

  //stop the tone playing after all LED codes have been displayed
      noTone(2);
    }
  }



// if button not pressed, sends int 0 to firebase to turn off LED 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

}





void printData() {
  Serial.println("Board Information:");
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.println("Network Information:");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}
