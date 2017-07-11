/*
 * 用按鈕決定LED燈
 */

int buttonPin = A5;
int buttonValue = 0;
int preButtonValue = 0;
int ledPin = 5;
int ledValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonValue = digitalRead(buttonPin);
  
  if(buttonValue != preButtonValue && buttonValue == 0){
    ledValue = digitalRead(ledPin);
    if(ledValue == HIGH)
      digitalWrite(ledPin, LOW);
    else
      digitalWrite(ledPin, HIGH);
  }
  
  preButtonValue = buttonValue;
}
