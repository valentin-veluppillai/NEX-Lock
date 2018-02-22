int keyEncoderPin[4] = {A0, A1, A2, A3};
int keyAvailablePin = 2;
volatile int input[4] = {0 ,0 ,0 ,0};
volatile int inputIndex = 0;

void setup() {
  Serial.begin(9600);
  pinMode(keyEncoderPin[0], INPUT);
  pinMode(keyEncoderPin[1], INPUT);
  pinMode(keyEncoderPin[2], INPUT);
  pinMode(keyEncoderPin[3], INPUT);
}

void loop() {
  attachInterrupt(digitalPinToInterrupt(keyAvailablePin), readInput, RISING);
  while(inputIndex != 4);
  detachInterrupt(digitalPinToInterrupt(keyAvailablePin));
  Serial.print("PIN: \"");
  for (int i = 0; i < 4; i++) {
    Serial.print(input[i]);
  }
  Serial.println("\"");
  inputIndex = 0;
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
