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
#define FIREBASE_HOST "xxx"
#define FIREBASE_AUTH "xxx"
#define WIFI_SSID "xxx"
#define WIFI_PASSWORD "xxx"
#define MODULE_ID "00000000001"
#define UNIQUE_ID "00000000001"
#define UNIQUE_ID2 "00000000002"
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
int powerPins[] = {
D0,
D5,
}; 
int powerPinsCount=2;
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

void loop() {
  Serial.println("----------------------------");
  setValues(UNIQUE_ID,0,D7);
  delay(5000);
  Serial.println("----------------------------");
  setValues(UNIQUE_ID2,1,D8);
  
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

void setValues(String id, int index, int powerPin){
int pin=D0;
for(int i=0;i<powerPinsCount;i++){
  if(i==index){
    pin=powerPins[i];
  } else {
    Serial.print("INDEX INPUT");
    Serial.println(powerPins[i]);
 pinMode(powerPins[i],INPUT);
  }
} 

    Serial.print("PIN OUTPUT");
    Serial.println(pin
    );

  // get power
 bool power= Firebase.getBool("devices/"+id+"/power");
  // get charging
  bool charging=Firebase.getBool("devices/"+id+"/charging");
  Serial.println(power);
  Serial.println(charging);
    if(power==true){
          if(charging==true){
      
 pinMode(pin,OUTPUT);
    } else {
      
 pinMode(pin,INPUT);
    }
 pinMode(powerPin,OUTPUT);
    } else {
      
 pinMode(pin,INPUT);
 pinMode(powerPin,INPUT);
    }

    

  
  // set module id
  Firebase.setString("devices/"+id+"/module_id", MODULE_ID);
    int sensorValue=analogRead(A0);
  float voltage=(sensorValue*1.405)*(5.0/1023.0);
  // set voltage
  Firebase.setFloat("devices/"+id+"/voltage", voltage);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /voltage failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.println("pushed "+String(voltage));

  // set date
  String date=getTimeStampString();
  Firebase.setString("devices/"+id+"/date", date);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /date failed:");
      Serial.println(Firebase.error());  
      return;
  }

 Serial.println("run");
String test = Firebase.getString("devices/"+id+"/sceneList");
String tempSceneName="";
for(int i=0;i<test.length();i++){
  if(test[i]!=','){
    tempSceneName+=test[i];
  } else {
     String timestamp=Firebase.getString("devices/"+id+"/"+tempSceneName+"/timestamp");
 if(timestamp!=""){
     bool enable=Firebase.getBool("devices/"+id+"/"+tempSceneName+"/enable");
     Serial.print("enable= ");
     Serial.println(enable);
  if(enable==true){
    int CdayValue=getDayInt();
  int ChourValue=getHourInt()+3;
  int CminuteValue=getMinuteInt();
  int dayValue=Firebase.getInt("devices/"+id+"/"+tempSceneName+"/day");
  int hourValue=Firebase.getInt("devices/"+id+"/"+tempSceneName+"/hour");
  int minuteValue=Firebase.getInt("devices/"+id+"/"+tempSceneName+"/minute");
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
    
  int plan=Firebase.getInt("devices/"+id+"/"+tempSceneName+"/plan");
  if(plan==0){
    Firebase.setBool("devices/"+id+"/power", true);
  } else if(plan==1){
    Firebase.setBool("devices/"+id+"/power", false);
  }
    }
  }
 } else {
  
 Serial.println("break");
 }
 tempSceneName="";
  }
}

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
   String hoursStr = hours < 10 ? "0" + String(hours+3) : String(hours+3);

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
