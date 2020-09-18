RF24 radio(7, 8);
const byte address[6] = "00001" ;
      
unsigned long totalTime;
unsigned long timeStop;
unsigned long startMs;
unsigned long timeEnd;  
float seconds;
float secondsStop;

boolean buttonState = 0;  
int lightLevel = 0;
int lightLevelInit = 0;
int lightLevelFinal = 0;
int start = 0;
int x = 0;
int GO = 0;
int distance = 100;
int MPS = 0;
void setup()   {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
   
  Serial.begin(9600);
  
  pinMode(2, INPUT);
  delay(250);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("Reset Complete");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
}
 
 
void loop() {
  lightLevel = analogRead(0);
  buttonState = digitalRead(2);
 
 if (buttonState == HIGH and start == 0  ){
  radio.write(&buttonState, sizeof(buttonState)); 
    lightLevelInit = analogRead(0);
    lightLevelFinal = lightLevelInit * 0.9;
    delay(355);  
    start = 1;
  }
  if(start == 1 and x == 0){
    radio.openReadingPipe(0, address);
    radio.startListening();
    radio.read(&GO, sizeof(GO));
    startMs = millis();
  }
  if (timeEnd == 0 and GO == 1 and x == 0) {
    x=1;
  }
  if (timeEnd == 0 and x == 1) {
    totalTime = millis() - startMs;
    seconds = (float) totalTime / 1000;
    Serial.println(seconds);
  }
  if (lightLevel < lightLevelFinal and timeEnd == 0 and x == 1) {    
      lightLevel = analogRead(0); 
    timeStop = millis() - startMs;
    secondsStop = (float) timeStop / 1000;
    Serial.println(secondsStop);
    timeEnd = 1;
  }
  if (timeEnd == 1){
  MPS = (distance/secondsStop);
  Serial.print(secondsStop);
  Serial.println("---FINAL TIME");
  Serial.print(MPS);
  Serial.println("---AVG SPEED MPS");
  Serial.print(MPS*2.23693);
  Serial.println("---AVG SPEED MPH");
  Serial.end();
  }
}