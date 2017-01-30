/************************* Wifi  *********************************/

void setup_wifi(){

  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  
  int timeout = millis()+10000;
  while ( ( WiFi.status()  != WL_CONNECTED) && (timeout > millis())) {
   delay(10);    
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("* WiFi not connected");
    mqtt_publish_failed("wifi");   
    ESP.reset();
  }else{    
    Serial.print("* WiFi connected to ");
    Serial.println(WIFI_SSID);
    Serial.print("  IP address: ");
    Serial.println(WiFi.localIP());     
  }
  
}


int WIFI_getRSSIasQuality(int RSSI)
{
  int quality = 0;

  if (RSSI <= -100) {
    quality = 0;
  } else if (RSSI >= -50) {
    quality = 100;
  } else {
    quality = 2 * (RSSI + 100);
  }
  return quality;
}

