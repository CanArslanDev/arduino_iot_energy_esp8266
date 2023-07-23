//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>


// Set these to run example.
#define FIREBASE_HOST "energy-e67ed-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "OAW3t0pHNbNlBPXbPoLC6CUAdp8je3Yz971cbEwX"
#define WIFI_SSID "ultrasonik2"
#define WIFI_PASSWORD "yakisiklican2909"
#define UNIQUE_ID "00000000001"
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
void setup() {
  Serial.begin(9600);
timeClient.begin();
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  int sensorValue=analogRead(A0);
  float voltage=(sensorValue*1.405)*(5.0/1023.0);
  // set voltage
  Firebase.setFloat("devices/"+String(UNIQUE_ID)+"/voltage", voltage);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /voltage failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.println("pushed "+String(voltage));

  // set date
  String date=getTimeStampString();
  Firebase.setString("devices/"+String(UNIQUE_ID)+"/date", date);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /date failed:");
      Serial.println(Firebase.error());  
      return;
  }

 Serial.println("run");
  for(int i=1;i<100;i++){
     String timestamp=Firebase.getString("devices/"+String(UNIQUE_ID)+"/scene_"+i+"/timestamp");
 if(timestamp!=""){
     bool enable=Firebase.getBool("devices/"+String(UNIQUE_ID)+"/scene_"+i+"/enable");
     Serial.print("enable= ");
     Serial.println(enable);
  if(enable==true){
    int CdayValue=getDayInt();
  int ChourValue=getHourInt()+3;
  int CminuteValue=getMinuteInt();
  int dayValue=Firebase.getInt("devices/"+String(UNIQUE_ID)+"/scene_"+i+"/day");
  int hourValue=Firebase.getInt("devices/"+String(UNIQUE_ID)+"/scene_"+i+"/hour");
  int minuteValue=Firebase.getInt("devices/"+String(UNIQUE_ID)+"/scene_"+i+"/minute");
     Serial.print("day ");
     Serial.print(CdayValue);
     Serial.print(" = ");
     Serial.println(dayValue);
     Serial.print("hour ");
     Serial.print(ChourValue);
     Serial.print(" = ");
     Serial.println(hourValue);
     Serial.print("minute ");
     Serial.print(CminuteValue);
     Serial.print(" = ");
     Serial.println(minuteValue);
  if(CdayValue==dayValue && ChourValue==hourValue && CminuteValue==minuteValue){
    
  int plan=Firebase.getInt("devices/"+String(UNIQUE_ID)+"/scene_"+i+"/plan");
  if(plan==0){
    Firebase.setBool("devices/"+String(UNIQUE_ID)+"/power", true);
  } else if(plan==1){
    Firebase.setBool("devices/"+String(UNIQUE_ID)+"/power", false);
  }
    }
  }
 } else {
  
 Serial.println("break");
  break;
 }
  }
  delay(5000);
  
 /* // update value
  Firebase.setFloat("number", 43.0);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // get value 
  Serial.print("number: ");
  Serial.println(Firebase.getFloat("number"));
  delay(1000);

  // remove value
  Firebase.remove("number");
  delay(1000);

  // set string value
  Firebase.setString("message", "hello world");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set bool value
  Firebase.setBool("truth", false);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);*/
}

String getTimeStampString() {
  timeClient.update();
   time_t rawtime = timeClient.getEpochTime();
   struct tm * ti;
   ti = localtime (&rawtime);

   uint16_t year = ti->tm_year + 1900;
   String yearStr = String(year);

   uint8_t month = ti->tm_mon + 1;
   String monthStr = month < 10 ? "0" + String(month) : String(month);

   uint8_t day = ti->tm_mday;
   String dayStr = day < 10 ? "0" + String(day) : String(day);

   uint8_t hours = ti->tm_hour;
   String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);

   uint8_t minutes = ti->tm_min;
   String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);

   uint8_t seconds = ti->tm_sec;
   String secondStr = seconds < 10 ? "0" + String(seconds) : String(seconds);

   return yearStr + "-" + monthStr + "-" + dayStr + " " +
          hoursStr + ":" + minuteStr + ":" + secondStr;
}

int getHourInt() {
  timeClient.update();
   time_t rawtime = timeClient.getEpochTime();
   struct tm * ti;
   ti = localtime (&rawtime);

   uint8_t hours = ti->tm_hour;
   String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);
   return hoursStr.toInt();
}

int getMinuteInt() {
  timeClient.update();
   time_t rawtime = timeClient.getEpochTime();
   struct tm * ti;
   ti = localtime (&rawtime);
   uint8_t minutes = ti->tm_min;
   String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);

   return minuteStr.toInt();
}

int getDayInt(){
timeClient.update();
return timeClient.getDay();

}
