#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <DHT_U.h>
extern "C" {
#include "user_interface.h"
}



/************************* Config Setup *********************************/

// changer deviceID
#define deviceID            "living1"
#define mqtt_server         "192.168.0.10"
#define mqtt_port           1883
#define deepsleeptime       300
#define PUB_PREFIX1         "sensors" 
#define PUB_PREFIX2         "tele" 
#define mqtt_user           "mqtt_user"
#define mqtt_password       "mqtt_password"
#define WIFI_SSID           "Wifi SSID"
#define WIFI_PWD            "Wifi Password"


/************************* declarations *********************************/
char HOST_ID[16] = {0};
String temperature;
String humidity;
float volt=0.0;


// Time
unsigned long startMillis;
unsigned long diff;

#define SECONDS_DS(seconds)  ((seconds)*1000000UL)


void setup() {  

  startMillis = millis();

  Serial.begin(115200);
  Serial.println();   
  Serial.print("resetReason:");
  Serial.println(ESP.getResetReason());
  Serial.println();  
  sprintf(HOST_ID, "ESP_%06X", ESP.getChipId());
  Serial.print("device: ");
  Serial.println(HOST_ID); 
  Serial.print("lieu: ");
  Serial.println(deviceID); 
    

  dht_init();  
  volt = read_vcc();

     
  setup_wifi();    
  mqtt_connect();
  dht_run();
  

  diff=millis()-startMillis;
  Serial.print("Cycle: ");
  Serial.print(diff);
  Serial.println(" ms");

  mqtt_publish();

  // Sleep
  Serial.print("ESP8266 in sleep mode : ");
  Serial.print(deepsleeptime);
  Serial.println(" secondes");
  Serial.println("-------------------------------------------");

  ESP.deepSleep(SECONDS_DS(deepsleeptime),WAKE_RF_DEFAULT);       
    
}



void loop() {
}
