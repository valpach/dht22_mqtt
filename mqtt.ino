#define TOPSZ                  60           // Max number of characters in topic string

/************************* MQTT *********************************/
void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}
WiFiClient wifiClient;

PubSubClient client(mqtt_server, mqtt_port, callback, wifiClient);

void mqtt_publish_failed(char* type){
  
  char stopic[TOPSZ];
  
  snprintf_P(stopic, sizeof(stopic), PSTR("%s/%s/error"), PUB_PREFIX1, deviceID); 
  client.publish(stopic, type, true);   
}

void mqtt_publish(){
  
  char stopic[TOPSZ];
  char svalue[TOPSZ];

  snprintf_P(stopic, sizeof(stopic), PSTR("%s/%s/SSID"), PUB_PREFIX2, deviceID);
  snprintf_P(svalue, sizeof(svalue), PSTR("%s"),WIFI_SSID);    
  client.publish(stopic, svalue, true);   
          
  snprintf_P(stopic, sizeof(stopic), PSTR("%s/%s/RSSI"), PUB_PREFIX2, deviceID);
  snprintf_P(svalue, sizeof(svalue), PSTR("%d"), WIFI_getRSSIasQuality(WiFi.RSSI()));    
  client.publish(stopic, svalue, true);   

  snprintf_P(stopic, sizeof(stopic), PSTR("%s/%s/IP"), PUB_PREFIX2, deviceID);
  snprintf_P(svalue, sizeof(svalue), PSTR("%s"), WiFi.localIP().toString().c_str());    
  client.publish(stopic, svalue, true); 
  
  snprintf_P(stopic, sizeof(stopic), PSTR("%s/%s/VOLT"), PUB_PREFIX1, deviceID);
  snprintf_P(svalue, sizeof(svalue), PSTR("%s"), String(volt).c_str());    
  client.publish(stopic, svalue, true);  

  snprintf_P(stopic, sizeof(stopic), PSTR("%s/%s/dht22/temperature"), PUB_PREFIX1, deviceID);
  snprintf_P(svalue, sizeof(svalue), PSTR("%s"), temperature.c_str());    
  client.publish(stopic, svalue, true); 
  
  snprintf_P(stopic, sizeof(stopic), PSTR("%s/%s/dht22/humidity"), PUB_PREFIX1, deviceID);
  snprintf_P(svalue, sizeof(svalue), PSTR("%s"), humidity.c_str());    
  client.publish(stopic, svalue, true); 

  snprintf_P(stopic, sizeof(stopic), PSTR("%s/%s/cycle"), PUB_PREFIX1, deviceID);
  snprintf_P(svalue, sizeof(svalue), PSTR("%s"), String(diff).c_str());    
  client.publish(stopic, svalue, true); 

}

void mqtt_connect(){
 client.connect(HOST_ID, mqtt_user, mqtt_password);

  if (!client.connected()) {
    Serial.println("* MQTT connect failed");
    Serial.println("  Will reset and try again...");
    abort();
  }
  Serial.println("* MQTT connected"); 
}
  
