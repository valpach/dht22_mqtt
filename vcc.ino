/************************* VCC  *********************************/


float read_vcc(){
  
  unsigned int raw=0;
  pinMode(A0, INPUT);
  raw = analogRead(A0);
  volt=raw/1023.0;
  volt=volt*4.2;
  Serial.print("VOLT :");
  Serial.println(String(volt));
  return volt;    
}

