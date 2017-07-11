/*
 * 測試vide Board
 */

int videBoardPin = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(videBoardPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(videBoardPin, 0);
  delay(1000);
  analogWrite(videBoardPin, 50);
  delay(1000);
  analogWrite(videBoardPin, 100);
  delay(1000);
  analogWrite(videBoardPin, 150);
  delay(1000);
  analogWrite(videBoardPin, 200);
  delay(1000);
  analogWrite(videBoardPin, 255);
  delay(1000);
}
