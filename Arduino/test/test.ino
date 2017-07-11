/*
 * change LED color
 */

int rLedPin = 9;
int gLedPin = 11;
int bLedPin = 10;
int LedValue[] = {0, 255, 0};  //{r, g, b}
int change = -1;
int state = 0; //0: purple, 1: red, 2: yellow, 3: green, 4: clay, 5: blue
int chState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(rLedPin, OUTPUT);
  pinMode(bLedPin, OUTPUT);
  pinMode(gLedPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Set Led to state 0
  analogWrite(rLedPin, LedValue[0]);
  analogWrite(gLedPin, LedValue[1]);
  analogWrite(bLedPin, LedValue[2]);

  while(true) {
    //Get the serial post messege
    chState = Serial.read();
    //No messege
    if (chState == -1) {
      //flash
      controlFlash(LedValue, state, &change);
    }
    else {
      state = chState - 48;
      changeLed(LedValue, state);
    }
    analogWrite(rLedPin, LedValue[0]);
    analogWrite(gLedPin, LedValue[1]);
    analogWrite(bLedPin, LedValue[2]);
    delay(10);
  }
}

void controlFlash(int LedValue[3], int state, int *change) {
  switch(state){
    case 0:
      flash(&LedValue[0], *change);
      *change = flash(&LedValue[2], *change);
      break;
    case 1:
      *change = flash(&LedValue[0], *change);
      break;
    case 2:
      flash(&LedValue[0], *change);
      *change = flash(&LedValue[1], *change);
      break;
    case 3:
      *change = flash(&LedValue[1], *change);
      break;
    case 4:
      flash(&LedValue[1], *change);
      *change = flash(&LedValue[2], *change);
      break;
    case 5:
      *change = flash(&LedValue[2], *change);
      break;
    default:
      break;
    }
}


int flash(int *value, int change) {
  if(*value == 0)
    change = 1;
  else if(*value == 255)
    change = -1;
  *value = *value + change;
  return change;
}

void changeLed(int LedValue[3], int state) {
  bool flag = true;
  switch(state){
    case 0:
      while(flag) {
        if(LedValue[0] > 0)
          LedValue[0] = LedValue[0] - 1;
        if(LedValue[1] < 255)
          LedValue[1] = LedValue[1] + 1;
        if(LedValue[2] > 0)
          LedValue[2] = LedValue[2] - 1;

        analogWrite(rLedPin, LedValue[0]);
        analogWrite(gLedPin, LedValue[1]);
        analogWrite(bLedPin, LedValue[2]);
        
        if(LedValue[0] == 0 && LedValue[1] == 255 && LedValue[2] == 0)
          flag = false;

        delay(10);
      }
      break;
    case 1:
      while(flag) {
        if(LedValue[0] > 0)
          LedValue[0] = LedValue[0] - 1;
        if(LedValue[1] < 255)
          LedValue[1] = LedValue[1] + 1;
        if(LedValue[2] < 255)
          LedValue[2] = LedValue[2] + 1;

        analogWrite(rLedPin, LedValue[0]);
        analogWrite(gLedPin, LedValue[1]);
        analogWrite(bLedPin, LedValue[2]);
        
        if(LedValue[0] == 0 && LedValue[1] == 255 && LedValue[2] == 255)
          flag = false;

        delay(10);
      }
      break;
    case 2:
      while(flag) {
        if(LedValue[0] > 0)
          LedValue[0] = LedValue[0] - 1;
        if(LedValue[1] > 0)
          LedValue[1] = LedValue[1] - 1;
        if(LedValue[2] < 255)
          LedValue[2] = LedValue[2] + 1;

        analogWrite(rLedPin, LedValue[0]);
        analogWrite(gLedPin, LedValue[1]);
        analogWrite(bLedPin, LedValue[2]);
        
        if(LedValue[0] == 0 && LedValue[1] == 0 && LedValue[2] == 255)
          flag = false;

        delay(10);
      }
      break;
    case 3:
      while(flag) {
        if(LedValue[0] < 255)
          LedValue[0] = LedValue[0] + 1;
        if(LedValue[1] > 0)
          LedValue[1] = LedValue[1] - 1;
        if(LedValue[2] < 255)
          LedValue[2] = LedValue[2] + 1;

        analogWrite(rLedPin, LedValue[0]);
        analogWrite(gLedPin, LedValue[1]);
        analogWrite(bLedPin, LedValue[2]);
        
        if(LedValue[0] == 255 && LedValue[1] == 0 && LedValue[2] == 255)
          flag = false;

        delay(10);
      }
      break;
    case 4:
      while(flag) {
        if(LedValue[0] < 255)
          LedValue[0] = LedValue[0] + 1;
        if(LedValue[1] > 0)
          LedValue[1] = LedValue[1] - 1;
        if(LedValue[2] > 0)
          LedValue[2] = LedValue[2] - 1;

        analogWrite(rLedPin, LedValue[0]);
        analogWrite(gLedPin, LedValue[1]);
        analogWrite(bLedPin, LedValue[2]);
        
        if(LedValue[0] == 255 && LedValue[1] == 0 && LedValue[2] == 0)
          flag = false;

        delay(10);
      }
      break;
    case 5:
      while(flag) {
        if(LedValue[0] < 255)
          LedValue[0] = LedValue[0] + 1;
        if(LedValue[1] < 255)
          LedValue[1] = LedValue[1] + 1;
        if(LedValue[2] > 0)
          LedValue[2] = LedValue[2] - 1;

        analogWrite(rLedPin, LedValue[0]);
        analogWrite(gLedPin, LedValue[1]);
        analogWrite(bLedPin, LedValue[2]);
        
        if(LedValue[0] == 255 && LedValue[1] == 255 && LedValue[2] == 0)
          flag = false;

        delay(10);
      }
      break;
    default:
      break;
    }
}
