#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9          // Configurable, see typical pin layout above
#define SS_PIN 10         // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 2

int opos = 180;
int cpos = 150;
int keyEncoderPin[4] = {A0, A1, A2, A3};
int keyAvailablePin = 2;
volatile int input[4] = {0 ,0 ,0 ,0};
volatile int inputIndex = 0;

byte uid[] = {62, 164, 176, 137};
int pin[] = {4 ,5 ,2 ,9};

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servo;

void setup() {
  Serial.begin(9600);
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  servo.attach(3);
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

  if(arrayCompareByte(uid, mfrc522.uid.uidByte)){
    attachInterrupt(digitalPinToInterrupt(keyAvailablePin), readInput, RISING);
    while(inputIndex != 4);
    detachInterrupt(digitalPinToInterrupt(keyAvailablePin));
    inputIndex = 0;
    if (arrayCompareInt(input, pin, 4)) {
      servo.write(opos);
      delay(5000);
      servo.write(cpos);
    }
    else{
      Serial.println("WRONG");
    }
  }
  else
    Serial.println("UNKNOWN");

  mfrc522.PICC_HaltA();
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i]);
  }
}

bool arrayCompareByte(byte* a, byte* b){
  for(int i = 0; i < 8; i++){
    if(a[i] != b[i])
      return false;
  }
 return true;
}

bool arrayCompareInt(int* a, int* b, int len){
  for(int i = 0; i < len; i++){
    if(a[i] != b[i])
      return false;
  }
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
