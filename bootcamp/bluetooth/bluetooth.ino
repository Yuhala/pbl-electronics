
/**
 * Controlling lights via bluetooth.
 * Programming bootcamp
 * Peterson Yuhala & Daouda Rahimatou
 */
  
//#include <SoftwareSerial.h>

char received_value = 0;
int LED = 13;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    received_value = Serial.read();
    Serial.print(received_value);
    Serial.print("\n");
  }

}
