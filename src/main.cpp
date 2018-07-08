//test
#include <Arduino.h>
//test Git+
int cc = 176; //controlChange on Channel 1
byte controlNum[8] = {102,104,100,106,101,105,103,107};
//pots
int potVal[8];
int potValOld[8];
byte controlVal[8];

//iterator
byte i = 0;
//tolarance for pot Movement
byte tolarance = 5;
int midiByte = 0 ;

void sendCC(byte cc,byte controlNum,byte value) {
  Serial.write(cc);
  Serial.write(controlNum);
  Serial.write(value);
}

void selectIcInput(byte pin) {
   digitalWrite(2, bitRead(pin, 2));
   digitalWrite(3, bitRead(pin, 1));
   digitalWrite(4, bitRead(pin, 0));
}

void checkMidiIn() {
  if (Serial.available() > 0) {
    midiByte = Serial.read() ;
    Serial.write(midiByte) ;
  }
}

void setup() {
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 Serial.begin(31250);
}

void loop () {
  for ( i = 0 ; i < 8; i++ ) {
    checkMidiIn();
    selectIcInput(i);
    potVal[i] = analogRead(A0);
    potVal[i] = 0.2 * potVal[i] + 0.8 * analogRead(A0);
    controlVal[i] = map(potVal[i],0,1023,0,127);

    if(potVal[i] <= potValOld[i] - tolarance || potVal[i] > potValOld[i] + tolarance ) {
      checkMidiIn();
      sendCC(cc,controlNum[i], controlVal[i]);
      potValOld[i] = potVal[i];
    }
  }
}
