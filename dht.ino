/************************* DHT *********************************/

#define DHTTYPE DHT22
#define DHTPIN  12
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;


void dht_init(){
  dht.begin();
}


void dht_run(){

  Serial.println();

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;          
  diff=millis()-startMillis;  
  if (diff < delayMS){
    delay(delayMS-diff);  
  }
  
    
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
    Serial.println("Reset ESP");
    mqtt_publish_failed("dht");
    ESP.reset();
  }
  else {
    temperature=String(event.temperature);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
    Serial.println("Reset ESP");
    mqtt_publish_failed("dht");   
    ESP.reset();    
  }
  else {
    humidity = String(event.relative_humidity);
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }
}
