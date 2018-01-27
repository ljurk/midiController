#include <Arduino.h>

//pots
int potVal[8];
byte controlVal[8];
byte controlValOld[8];
byte i = 0;
byte tolarance = 5;

void setup() {
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 Serial.begin(9600);
}

void selectIcInput(byte pin) {
   digitalWrite(2, bitRead(pin, 2));
   digitalWrite(3, bitRead(pin, 1));
   digitalWrite(4, bitRead(pin, 0));
 }

void loop () {
  for ( i = 0 ; i < 8; i++ ) {
    selectIcInput(i);
    potVal[i] = analogRead(A0);
    potVal[i] = 0.2 * potVal[i] + 0.8 * analogRead(A0);
    controlVal[i] = map(potVal[i],0,1023,0,127);

    if(controlVal[i] <= controlValOld[i] - tolarance || controlVal[i] > controlValOld[i] + tolarance ) {
      delay(200);
      Serial.print(i);
      Serial.print(":");
      Serial.print(controlVal[i]);
      Serial.println("");
      controlValOld[i] = controlVal[i];
    }
  }
}
