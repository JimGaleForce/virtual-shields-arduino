/*
    Copyright(c) Microsoft Open Technologies, Inc. All rights reserved.

    The MIT License(MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#include <ArduinoJson.h>
#include <SPI.h>
#include <WiFi.h>
#include "WiFiStream.h"

#include <VirtualShield.h>
#include <Text.h>

char ssid[] = "SSID";             // your network SSID (name) 
char pass[] = "password";         // your network password
int port = 1235;                  // 1235 is the default port
int status = WL_IDLE_STATUS;      // the Wifi radio's status
WiFiStream wifi;

VirtualShield shield;	          // identify the shield
Text screen = Text(shield);	  // connect the screen

void connectToWifi() 
{
    // Serial is only used to see output and debugging from the Serial Monitor
    Serial.begin(9600);
    Serial.println("starting");
    
    // wifi WITH password (WPA, WPA2, etc)
    status = wifi.begin(ssid, pass, 1235); 

    // wifi WITHOUT password (open)
    //status = WiFi.begin(ssid, pass); 

    // set broadcast name of connection (this is not SSID broadcast, but a custom Virtual Shields broadcast)
    wifi.setName("MyArduino", 9); // number is length of string
  
    // if you're not connected, stop here:
    if ( status != WL_CONNECTED) { 
      Serial.println("Couldn't get a wifi connection");
      while(true);
    } 
    // if you are connected, print out info about the connection:
    else {
      Serial.println("Connected to network");
      IPAddress ip = WiFi.localIP();
      Serial.println(ip);
    }
}

void refresh(ShieldEvent* event) 
{
    // clears the screen
    screen.clear();
    Serial.print("refreshed");
}

int y = 0;

void sendBeacon() {
  wifi.broadcastBeacon(1235);
}

void screens(ShieldEvent* event) {
}

void connected1(ShieldEvent* event) {
  Serial.print("connected");
}

void setup()
{
    // connect to wifi
    connectToWifi();  
  
    // set the data stream of wifi for Virtual Shields  
    shield.setStream( &wifi ); 
    
    screen.setOnEvent(screens);
    shield.setOnConnect(connected1);
    shield.setOnRefresh(refresh);
  
    shield.begin();
}

void loop()
{
    shield.checkSensors();
    
    // send a (wifi) beacon (UDP) with name for connection from Virtual Shields app
    sendBeacon();
    
    screen.printAt(y, "Hello Virtual Shields123");	 
    y++;
    if (y > 10)
    {
      y = 0;
    }
    delay(1000);
}								
