/*
 * 測試speaker
 */

int speakerPin = 7;
int melody[] = {523, 587, 659, 698, 784, 880, 988, 1047};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    tone(speakerPin, melody[thisNote], 500);
    delay(1000);
  }
  
  delay(2000);

}
