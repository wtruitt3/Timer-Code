#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
RF24 radio (7, 8);

const byte address[6]= "00001";
boolean buttonState = 0;
int GO = 0;

void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel (RF24_PA_MAX);
  radio.startListening();
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}
void loop () {
  if(radio.available()) { 
  radio.read(&buttonState, sizeof (buttonState));
  if (buttonState == HIGH and GO == 0) {
    tone(2, 554, 500);
    delay(random(1500, 3500));
    tone(2, 1108, 500);
    GO = 1;
  }
  if (GO = 1){
    radio.stopListening();
    radio.openWritingPipe(address);
    radio.write(&GO, sizeof (GO));
   
  }
  }
}