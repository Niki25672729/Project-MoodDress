#define LEDNUM 1
#define LEDPIN 5
#define SPEED 0.05
#define TOP 255
#define BOTTOM 10

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUM, LEDPIN, NEO_RGB + NEO_KHZ800);

int registerPin = A5;
int registerValue = 0;

float LedValue[LEDNUM][3] = {{}};  //{r, g, b}
int LedState[LEDNUM] = {}; //0: purple{255, 0, 255}, 1: red{255, 0, 0}, 2: yellow{255, 255, 0}, 3: green{0, 255, 0}, 4: clay{0, 255, 255}, 5: blue{0, 0, 255}
int change[LEDNUM] = {};
float lightSpeed[LEDNUM] = {};
int chState = 0;
bool changedLightComplite[LEDNUM] = {};
bool flag = false;

int loopCount = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  pinMode(registerPin, INPUT_PULLUP);

  //initial change
  for(int i = 0; i < LEDNUM; i++)
    change[i] = -1;

  //initial state
  for(int i = 0; i < LEDNUM; i++)
    LedState[i] = i%6;

  //initial speed
  for(int i = 0; i < LEDNUM; i++)
    lightSpeed[i] = SPEED;

  //initial changedLightComplite
  for(int i = 0; i < LEDNUM; i++)
    changedLightComplite[i] = true;

  strip.begin();
  strip.show();
  clear(LEDNUM);

}


void loop() {
  // put your main code here, to run repeatedly:
  // initial value
  for(int i = 0; i < LEDNUM; i++) {
    if(changedLightComplite[i])
      controlFlash(LedValue[i], LedState[i], &change[i], lightSpeed[i]);
    else
      changeLedLight(LedValue[i], LedState[i], lightSpeed[i], &changedLightComplite[i]);
  }

  registerValue = analogRead(registerPin);
  //Serial.println(registerValue);
  if(registerValue < 200) {
    for(int i = 0; i < LEDNUM; i++) {
      if(LedState[i] != 0) {
        LedState[i] = 0;
        changedLightComplite[i] = false;
      }
    }
  }
  else if(registerValue < 350) {
    for(int i = 0; i < LEDNUM; i++) {
      if(LedState[i] != 1) {
        LedState[i] = 1;
        changedLightComplite[i] = false;
      }
    }
  }
  else if(registerValue < 500) {
    for(int i = 0; i < LEDNUM; i++) {
      if(LedState[i] != 2) {
        LedState[i] = 2;
        changedLightComplite[i] = false;
      }
    }
  }
  else if(registerValue < 650) {
    for(int i = 0; i < LEDNUM; i++) {
      if(LedState[i] != 3) {
        LedState[i] = 3;
        changedLightComplite[i] = false;
      }
    }
  }
  else if(registerValue < 800) {
    for(int i = 0; i < LEDNUM; i++) {
      if(LedState[i] != 4) {
        LedState[i] = 4;
        changedLightComplite[i] = false;
      }
    }
  }
  else {
    for(int i = 0; i < LEDNUM; i++) {
      if(LedState[i] != 5) {
        LedState[i] = 5;
        changedLightComplite[i] = false;
      }
    }
  }
  
  show(LedValue);
}


void clear(int LedNum) {
  for (int i = 0; i < LedNum; i++) {
    strip.setPixelColor(i, 0, 0, 0);
    LedValue[i][0] = 0;
    LedValue[i][1] = 0;
    LedValue[i][2] = 0;
  }
  strip.show();
  
  return;
}


void show(float LedValue[LEDNUM][3]) {
  for(int i = 0; i < LEDNUM; i++)
    strip.setPixelColor(i, LedValue[i][0], LedValue[i][1], LedValue[i][2]);
  strip.show();
}


void controlFlash(float LedValue[], int LedState, int *change, float lightSpeed) {
  switch(LedState) {
    case 0:
      flash(&LedValue[0], *change, lightSpeed);
      *change = flash(&LedValue[2], *change, lightSpeed);
      break;
    case 1:
      *change = flash(&LedValue[0], *change, lightSpeed);
      break;
    case 2:
      flash(&LedValue[0], *change, lightSpeed);
      *change = flash(&LedValue[1], *change, lightSpeed);
      break;
    case 3:
      *change = flash(&LedValue[1], *change, lightSpeed);
      break;
    case 4:
      flash(&LedValue[1], *change, lightSpeed);
      *change = flash(&LedValue[2], *change, lightSpeed);
      break;
    case 5:
      *change = flash(&LedValue[2], *change, lightSpeed);
      break;
    default:
      break;
    }
}


int flash(float *value, int change, float lightSpeed) {
  if(*value == BOTTOM)
    change = 1;
  else if(*value == TOP)
    change = -1;
  float temp = *value + change*lightSpeed;
  if(temp > TOP)
    temp = TOP;
  else if(temp < BOTTOM)
    temp = BOTTOM;
  *value = temp;
  
  return change;
}


void changeLedLight(float LedValue[], int state, float lightSpeed, bool *complite) {
  switch(state) {
    case 0:
      if(LedValue[0] < TOP)
        LedValue[0] += 1*lightSpeed;
      if(LedValue[1] > 0)
        LedValue[1] -= 1*lightSpeed;
      if(LedValue[2] < TOP)
        LedValue[2] += 1*lightSpeed;

      if(LedValue[0] >= TOP && LedValue[1] <= 0 && LedValue[2] >= TOP)
        *complite = true;
      break;

    case 1:
      if(LedValue[0] < TOP)
        LedValue[0] += 1*lightSpeed;
      if(LedValue[1] > 0)
        LedValue[1] -= 1*lightSpeed;
      if(LedValue[2] > 0)
        LedValue[2] -= 1*lightSpeed;

      if(LedValue[0] >= TOP && LedValue[1] <= 0 && LedValue[2] <= 0)
        *complite = true;
      break;

    case 2:
      if(LedValue[0] < TOP)
        LedValue[0] += 1*lightSpeed;
      if(LedValue[1] < TOP)
        LedValue[1] += 1*lightSpeed;
      if(LedValue[2] > 0)
        LedValue[2] -= 1*lightSpeed;

      if(LedValue[0] >= TOP && LedValue[1] >= TOP && LedValue[2] <= 0)
        *complite = true;
      break;

    case 3:
      if(LedValue[0] > 0)
        LedValue[0] -= 1*lightSpeed;
      if(LedValue[1] < TOP)
        LedValue[1] += 1*lightSpeed;
      if(LedValue[2] > 0)
        LedValue[2] -= 1*lightSpeed;

      if(LedValue[0] <= 0 && LedValue[1] >= TOP && LedValue[2] <= 0)
        *complite = true;
      break;

    case 4:
      if(LedValue[0] > 0)
        LedValue[0] -= 1*lightSpeed;
      if(LedValue[1] < TOP)
        LedValue[1] += 1*lightSpeed;
      if(LedValue[2] < TOP)
        LedValue[2] += 1*lightSpeed;

      if(LedValue[0] <= 0 && LedValue[1] >= TOP && LedValue[2] >= TOP)
        *complite = true;
      break;

    case 5:
      if(LedValue[0] > 0)
        LedValue[0] -= 1*lightSpeed;
      if(LedValue[1] > 0)
        LedValue[1] -= 1*lightSpeed;
      if(LedValue[2] < TOP)
        LedValue[2] += 1*lightSpeed;

      if(LedValue[0] <= 0 && LedValue[1] <= 0 && LedValue[2] >= TOP)
        *complite = true;
      break;

    default:
      break;
  }

  //test if break the range
  for(int j = 0; j < 3; j++) {
    if(LedValue[j] > TOP)
      LedValue[j] = TOP;
    else if(LedValue[j] < 0)
      LedValue[j] = 0;
  } //end for loop
}
