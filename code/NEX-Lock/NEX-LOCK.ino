#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define  UIDLEN 4   //lenght of UID, in bytes
#define mfrcResetPin 9          //reset pin for the RFID reader
#define mfrcSlaveSelectPin 10         // slave select pin of the rfid reader
#define keyAvailablePin 2   //data available pin of keypad encoder
#define servoPin 6    //data pin of servo
#define opos 180   // open servo position
#define cpos  150   //closed servo position
#define extButtonPin 3  //button on the "inside"

const int keyEncoderPin[4] = {A0, A1, A2, A3};  //key encoder data pins

byte uid[][UIDLEN] = {{62, 164, 176, 137}}; //this contains the valid UIDs, will be read from file
int uidAmount = 1;  //how many valid uids were read, current value for testing
int pin[] = {4529};   //pins that correspond to the uids
int uidIndex;
bool uidCheck;

volatile int input[4];    //data from keypad is stored here
volatile int inputIndex = 0;
volatile bool interruptClear = true;  //for the override isr
volatile bool overrideDoor = false;   //override door flag

MFRC522 mfrc522(mfrcSlaveSelectPin, mfrcResetPin);
Servo servo;

void setup() {
  Serial.begin(9600);
  //this and all following Serial.x() will be replaced by leds sometime, only useful for debuging
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();
  servo.attach(servoPin);
  attachInterrupt(digitalPinToInterrupt(extButtonPin), isrOverride, RISING);
}

void loop() {
  if (overrideDoor) {
    overrideDoor = false;
    Serial.println("OVERRIDE");
    delay(10);
    interruptClear = false;   //while the door is being opened/closed, it cannot be overridden
    servo.write(opos);
    while((digitalRead(keyAvailablePin) == LOW));
    servo.write(cpos);
    interruptClear = true;
  }
  if ( ! mfrc522.PICC_IsNewCardPresent()) {   //re-run loop if there is no new card
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.println("Crad detected");
  uidCheck = false;
  for (int k = 0; k < uidAmount; k++) {   //run through all valid UIDds and check if one matches the read one
    if(uidCompare(uid[k], mfrc522.uid.uidByte)){
      uidCheck = true;
      uidIndex = k;   //if a match is found, save it and stop looking
      break;
    }
  }
  if(uidCheck){
    Serial.println("Enter PIN");
    attachInterrupt(digitalPinToInterrupt(keyAvailablePin), readInput, RISING);
    inputIndex = 0;
    while(inputIndex != 4);   //the pin is read using an interrupt
    detachInterrupt(digitalPinToInterrupt(keyAvailablePin));
    inputIndex = 0;
    if (pin[uidIndex] == (input[0] * 1000 + input[1] * 100 + input[2] * 10 + input[3])) { //lazy much?
      Serial.println("CORRECT");
      delay(10);
      interruptClear = false; //as above, no overrides during opening/closing
      servo.write(opos);
      while((digitalRead(extButtonPin) == LOW));
      servo.write(cpos);
      delay(1000);
      interruptClear = true;
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

bool pinCompare(int* a, int* b){  //compares entered pin with pin for corresponding user/uid
  Serial.println(pin[uidIndex]);
  if(a[uidIndex] != *b)
    return false;
 return true;
}

void isrOverride(){   //sets override flag when it is allowed to
  if(interruptClear)
    overrideDoor = true;
}

void readInput(){
  int i = 0;
  int temp = 0;
  temp += digitalRead(keyEncoderPin[i++]); //still lazy, for loop would be morge elegant, but who cares?
  temp += digitalRead(keyEncoderPin[i++]) * 2;
  temp += digitalRead(keyEncoderPin[i++]) * 4;
  temp += digitalRead(keyEncoderPin[i++]) * 8;
  switch (temp) { // there must be a better way to do this...
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
