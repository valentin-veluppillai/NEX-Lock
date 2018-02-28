#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#define  UIDLEN 4


#define RST_PIN 9          // Configurable, see typical pin layout above
#define SS_PIN 10         // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 2
#define keyAvailablePin 2
#define servoPin 6
#define opos 180   // open servo position
#define cpos  150   //closed servo position
#define extButtonSupplyPin 4
#define extButtonPin 3

const int keyEncoderPin[4] = {A0, A1, A2, A3};
const int pin[] = {4529};
const int pinAmount = 1;
const byte uid[][UIDLEN] = {{62, 164, 176, 137}};
const int uidAmount = 1;

volatile int input[4];
volatile int inputIndex = 0;
int uidIndex;
bool uidCheck;
volatile int doorCounter;

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servo;

void setup() {
  Serial.begin(9600);
  //this and all following Serial.x() will be replaced by leds sometime, only useful for debuging
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();
  servo.attach(3);
  attachInterrupt(digitalPinToInterrupt(extButtonPin), isrToggleDoor, RISING);
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println("Crad detected");
  uidCheck = false;
  for (int k = 0; k < uidAmount; k++) {
    if(uidCompare(uid[k], mfrc522.uid.uidByte)){
      uidCheck = true;
      uidIndex = k;
      break;
    }
  }

  if(uidCheck){
    Serial.println("Enter PIN");
    attachInterrupt(digitalPinToInterrupt(keyAvailablePin), readInput, RISING);
    while(inputIndex != 4);
    detachInterrupt(digitalPinToInterrupt(keyAvailablePin));
    inputIndex = 0;
    if (pin[uidIndex] == (input[0] * 1000 + input[1] * 100 + input[2] * 10 + input[3])) {
      servo.write(opos);
      delay(5000);
      servo.write(cpos);
    }
    else{
      Serial.println(" WRONG");
    }
  }
  else
    Serial.println("UNKNOWN");

  mfrc522.PICC_HaltA();
}

bool uidCompare(byte* a, byte* b){    //compares 2 uids /w lenght UIDLEN
  for(int i = 0; i < UIDLEN; i++){
    if(a[i] != b[i])
      return false;
  }
 return true;
}

bool pinCompare(int* a, int* b){
  Serial.println(pin[uidIndex]);
  if(a[uidIndex] != *b)
    return false;
 return true;
}

void readInput(){
  int i = 0;
  int temp = 0;
  temp += digitalRead(keyEncoderPin[i++]);
  temp += digitalRead(keyEncoderPin[i++]) * 2;
  temp += digitalRead(keyEncoderPin[i++]) * 4;
  temp += digitalRead(keyEncoderPin[i++]) * 8;
  switch (temp) {
    case 0:  input[inputIndex++] = 1; break;
    case 1:  input[inputIndex++] = 2; break;
    case 2:  input[inputIndex++] = 3; break;
    case 3:  input[inputIndex++] = 'A'; break;
    case 4:  input[inputIndex++] = 4; break;
    case 5:  input[inputIndex++] = 5; break;
    case 6:  input[inputIndex++] = 6; break;
    case 7:  input[inputIndex++] = 'B'; break;
    case 8:  input[inputIndex++] = 7; break;
    case 9:  input[inputIndex++] = 8; break;
    case 10: input[inputIndex++] = 9; break;
    case 11: input[inputIndex++] = 'C'; break;
    case 12: input[inputIndex++] = '*'; break;
    case 13: input[inputIndex++] = 0; break;
    case 14: input[inputIndex++] = '#'; break;
    case 15: input[inputIndex++] = 'D'; break;
    default: break;
  }
}

void isrToggleDoor(){
  if(((doorCounter++)%2) == 0){
    servo.write(opos);
    digitalWirte(extButtonSupplyPin, HIGH);
  }
  else{
    servo.write(opos);
    digitalWrite(extButtonSupplyPin, LOW);
  }
}
