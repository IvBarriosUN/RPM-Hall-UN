#include "SevSeg.h"
SevSeg sevseg;
float lectura = 0.0;
float valor = 0.0;
void setup() {
  byte numDigits = 4;  
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    bool resistorsOnSegments = 0; 
    // variable above indicates that 4 resistors were placed on the digit pins.
    // set variable to 1 if you want to use 8 resistors on the segment pins.
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments, false, false, false);
    sevseg.setBrightness(80);
    pinMode(A0, INPUT);
}

void loop() {
  lectura = analogRead(A0);
  valor = lectura*5/102.3;
  if (valor<=0.9){
    valor = 0;
  }
  sevseg.setNumber(valor, 1);
  sevseg.refreshDisplay(); // Must run repeatedly

}
