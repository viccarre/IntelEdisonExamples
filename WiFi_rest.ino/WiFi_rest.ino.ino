
#include <SPI.h>
#include <WiFi.h>
#include <aREST.h>
#include <iostream>
#include <String>

char ssid[] = "MassChallenge Now"; //  your network SSID (name)
char pass[] = "hackster15";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Create aREST instance
aREST rest = aREST();

// Initialize the WiFi server library
WiFiServer server(3000);

// Variables to be exposed to the API
int temperature;
int humidity;

void setup() {

  // Start Serial
  Serial.begin(115200);

  // Init variables and expose them to REST API
  temperature = 24;
  humidity = 40;
  rest.variable("temperature", &temperature);
  rest.variable("humidity", &humidity);

  rest.function("led", ledControl);

  // Give name and ID to device
  rest.set_id("008");
  rest.set_name("viccarre_Edison");

  // Function to be exposed
  rest.function("led", ledControl);
  rest.function("message", printMessage);

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

int printMessage(String command) {
  Serial.println(command);
  int pos, posAux;
  
  //Getting the first value
  String stringAux; 
  pos = command.indexOf(',');
  String string1 = command.substring(0,pos);
  stringAux = command.substring(pos+1);
  Serial.print("String 1: ");
  Serial.println(string1);
  
  //Second Value
  pos = stringAux.indexOf(',');
  string1= stringAux.substring(0,pos);
  stringAux = stringAux.substring(pos+1);
  Serial.print("String 2: ");
  Serial.println(string1);
  
  //Third Value
  Serial.print("String 3: ");
  Serial.println(stringAux);

  
  return 1;

}
// Custom function accessible by the API
int ledControl(String command) {

  // Get state from command
  int state = command.toInt();
  digitalWrite(13, state);
  Serial.println("LED function called");
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

