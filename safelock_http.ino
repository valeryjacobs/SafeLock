#include <Servo.h>

// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// Use Arduino IDE 1.6.8 or later.

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <EventManager.h>

#include <AzureIoTHub.h>
#include <AzureIoTUtility.h>
#include <AzureIoTProtocol_HTTP.h>

#include "safelock_http.h"

static char ssid[] ="SiliconValley";// "Ziggo66148";     // your network SSID (name)
static char pass[] = "zrhy-lbrv-7cud";// "tfCqJjQHrUAR";    // your network password (use for WPA, or use as key for WEP)


static AzureIoTHubClient iotHubClient;

Servo lockServo;

void setup() {
    initSerial();
    initWifi();
    initTime();

    lockServo.attach(15);
    lockServo.write(0);

}

void loop() {
    safelock_run();
}

void myListener( int eventCode, int eventParam )
    {
        // Do something with the event
        Serial.println("EVENT HANDLE");
    }


void initSerial() {
    // Start serial and initialize stdout
    Serial.begin(115200);
    Serial.setDebugOutput(true);
}

void initWifi() {
    // Attempt to connect to Wifi network:
    Serial.print("\r\n\r\nAttempting to connect to SSID: ");
    Serial.println(ssid);
    
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    
    Serial.println("\r\nConnected to wifi");
    
}

void initTime() {  
   time_t epochTime;

   configTime(0, 0, "pool.ntp.org", "time.nist.gov");

   while (true) {
       epochTime = time(NULL);

       if (epochTime == 0) {
           Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
           delay(2000);
       } else {
           Serial.print("Fetched NTP epoch time is: ");
           Serial.println(epochTime);
           break;
       }
   }
}
