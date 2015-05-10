// Robotics-0ver-Internet by Meng Yee (Michael) Chuah and Victor Carreno
#include "meArm.h"    // From Inverse kinematics control library for Phenoptix meArm http://github.com/yorkhackspace/meArm/blob/master/meArm.h
#include <Servo.h>

#include <String>
#include <iostream>
#include <SPI.h>
#include <WiFi.h>
#include <aREST.h>    // From A RESTful environment for Arduino http://github.com/marcoschwartz/aREST
                      // aREST.h needs to be edited to inclue itoa.h from https://github.com/pchickey/gcc-sam3u-build

char ssid[] = "MassChallenge Now"; //  your network SSID (name)
char pass[] = "hackster15";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// Create aREST instance
aREST rest = aREST();
// Initialize the WiFi server library
WiFiServer server(3000);

int basePin = 3;
int shoulderPin = 5;
int elbowPin = 6;
int gripperPin = 9;

int val;
/*
    // Full constructor uses calibration data, or can just give pins
    meArm(int sweepMinBase=145, int sweepMaxBase=49, float angleMinBase=-pi/4, float angleMaxBase=pi/4,
      int sweepMinShoulder=118, int sweepMaxShoulder=22, float angleMinShoulder=pi/4, float angleMaxShoulder=3*pi/4,
      int sweepMinElbow=144, int sweepMaxElbow=36, float angleMinElbow=pi/4, float angleMaxElbow=-pi/4,
      int sweepMinGripper=75, int sweepMaxGripper=115, float angleMinGripper=pi/2, float angleMaxGripper=0) arm;
*/
meArm arm(110, 9, -pi/4, pi/4,
      151, 47, pi/4, 3*pi/4,
      175, 95, pi/4, -pi/4,
      127, 151, pi/2, 0);
      
Servo gripper;  // create servo object to control a servo 

void setup() {
  Serial.begin(115200);
      
  arm.begin(basePin, shoulderPin, elbowPin, gripperPin);
  arm.openGripper();
  
  gripper.attach(9);

  // Give name and ID to device
  rest.set_id("008");
  rest.set_name("robot0internet_Edison");

  // Function to be exposed
  rest.function("message", printMessage);
  rest.function("gripper", gripperAction);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  // Attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

  Serial.println("Instructions: Connect to http://IP:3000/gripper?params=1 to open the gripper");
  Serial.println("Instructions: Connect to http://IP:3000/message?params=x,y,z to set the endpoint position, where x,y,z are integer values in mm");

    // Wait 10 seconds for connection
    delay(10000);
  }

  // Start the server
  server.begin();

  // Print out the status
  printWifiStatus();
}



void loop() { 
  // listen for incoming clients
  WiFiClient client = server.available();
  rest.handle(client);
}

int gripperAction(String command){
  if(command.toInt()==1){
    gripper.write(151);  
    Serial.println("Gripper open");
  }else{
    gripper.write(121);
    Serial.println("Gripper close");
  }
  return 1;
}

int printMessage(String command) {
  Serial.println(command);
  int pos, posAux;
  
  //Getting the first value
  String stringAux; 
  pos = command.indexOf(',');
  String string1 = command.substring(0,pos);
  stringAux = command.substring(pos+1);
  
  //Second Value
  pos = stringAux.indexOf(',');
  String string2 = stringAux.substring(0,pos);
  stringAux = stringAux.substring(pos+1);
  
  //Third Value  
  String string3 = stringAux;
  
  int x = string1.toInt();
  int y = string2.toInt();
  int z = string3.toInt();
  if(arm.isReachable(x,y,z)) {
    Serial.print("Going to point (");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.print(z);
    Serial.println(")");
    arm.gotoPoint(x,y,z);
  } else {
    Serial.print("Point (");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.print(z);
    Serial.println(") is not reachable");
  }  
  return 1;
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
