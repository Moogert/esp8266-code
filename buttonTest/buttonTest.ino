#include <ESP8266WiFi.h>
int val = 0; 

void setup() {  
  Serial.begin(115200); 
  Serial.println("hello there");
  pinMode(0,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13, INPUT);
}


void loop() {
  // see if we have input to pin 13
  delay(500); 
  val = digitalRead(13); 
  if(val!=0){
    digitalWrite(0,HIGH); 
    Serial.println("button!!\n");
    delay(500); 
    digitalWrite(0,LOW); 
  }
 
} // DONE works 




