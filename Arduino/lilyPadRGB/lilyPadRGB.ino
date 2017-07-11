/*
 * 測試RGB Led
 */

int swtichPin = 2;
int switchValue = 0;
int rLedPin = 9;
int bLedPin = 10;
int gLedPin = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(swtichPin, INPUT_PULLUP);
  pinMode(rLedPin, OUTPUT);
  pinMode(bLedPin, OUTPUT);
  pinMode(gLedPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  switchValue = digitalRead(swtichPin);

  if(switchValue == LOW){
    analogWrite(rLedPin, 0);
    analogWrite(bLedPin, 255);
    analogWrite(gLedPin, 255);
    delay(1000);
    analogWrite(rLedPin, 255);
    analogWrite(bLedPin, 0);
    analogWrite(gLedPin, 255);
    delay(1000);
    analogWrite(rLedPin, 255);
    analogWrite(bLedPin, 255);
    analogWrite(gLedPin, 0);
    delay(1000);
  }
}
