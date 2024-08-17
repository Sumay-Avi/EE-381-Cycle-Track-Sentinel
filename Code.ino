#include "thingProperties.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample code demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = D4, TXPin = D3;
// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(57600);

  ss.begin(9600);
  delay(1500); 
  
  pinMode(D0,OUTPUT);
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  if (ss.available() > 0)
  {
    gps.encode(ss.read()); //read gps data
    {
      speed=gps.speed.kmph();
      altitude=gps.altitude.meters();
      if (gps.location.isValid()) //check whether gps location is valid
      locloc=Location(gps.location.lat(), gps.location.lng());
    }
  }
  
}


/*
  Since Led is READ_WRITE variable, onLedChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLedChange()  {
  // Add your code here to act upon Led change
  if(led==1)
  {
    Serial.println("Buzzing");
    digitalWrite(D0,HIGH);
  }
  else
  {
    Serial.println("Not Buzzing");
    digitalWrite(D0,LOW);
  }
}
