#define TOP 255
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, 5, NEO_RGB + NEO_KHZ800);

float value[3] = {0, 0, 0};
int state = 0;
float ledspeed = 0.1;
int change = -1;
bool complite = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5, OUTPUT);

  strip.begin();
  strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  changeLedLight(value, state, ledspeed, &complite);
  if(complite == true) {
    state = (state+1)%6;
    complite = false;
  }
  strip.setPixelColor(4, value[0], value[1], value[2]);
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
  if(*value == 0)
    change = 1;
  else if(*value == 255)
    change = -1;
  float temp = *value + change*lightSpeed;
  if(temp > 255)
    temp = 255;
  else if(temp < 0)
    temp = 0;
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
