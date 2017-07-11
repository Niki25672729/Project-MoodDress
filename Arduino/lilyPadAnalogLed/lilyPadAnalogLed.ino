/*
 * 測試類比LED燈
 */

int ledPin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ledPin, 0);
  Serial.println(analogRead(ledPin));
  delay(1000);
  analogWrite(ledPin, 50);
  Serial.println(analogRead(ledPin));
  delay(1000);
  analogWrite(ledPin, 100);
  Serial.println(analogRead(ledPin));
  delay(1000);
  analogWrite(ledPin, 150);
  Serial.println(analogRead(ledPin));
  delay(1000);
  analogWrite(ledPin, 200);
  Serial.println(analogRead(ledPin));
  delay(1000);
  analogWrite(ledPin, 255);
  Serial.println(analogRead(ledPin));
  delay(1000);
}
