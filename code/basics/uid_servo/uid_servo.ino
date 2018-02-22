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
    servo.write(opos);
    delay(5000);
    servo.write(cpos);
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
