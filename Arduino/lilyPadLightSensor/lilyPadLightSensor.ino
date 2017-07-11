/*
 * 用光感測器決定LED燈
 */

int lightSensorValue = 0;
int lightSensorPin = A6;
int ledPin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(lightSensorPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  lightSensorValue = analogRead(lightSensorPin);
  
  if(lightSensorValue > 30)
    digitalWrite(ledPin, LOW);
  else
    digitalWrite(ledPin, HIGH);
}
