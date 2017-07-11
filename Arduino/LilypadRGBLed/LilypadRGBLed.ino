#define LEDNUM 2
#define LEDPIN 5
#define SPEED 0.1
#define TOP 255
#define BOTTOM 10

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUM, LEDPIN, NEO_RGB + NEO_KHZ800);

float LedValue[LEDNUM][3] = {{}};  //{r, g, b}
int LedState[LEDNUM] = {}; //0: purple{255, 0, 255}, 1: red{255, 0, 0}, 2: yellow{255, 255, 0}, 3: green{0, 255, 0}, 4: clay{0, 255, 255}, 5: blue{0, 0, 255}
int change[LEDNUM] = {};
float lightSpeed[LEDNUM] = {};
int chState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);

  //initial change
  for(int i = 0; i < LEDNUM; i++)
    change[i] = -1;

  //initial state
  for(int i = 0; i < LEDNUM; i++)
    LedState[i] = i;

  //initial speed
  for(int i = 0; i < LEDNUM; i++)
    lightSpeed[i] = SPEED;

  strip.begin();
  strip.show();
  clear(1);
}

void loop() {
  // put your main code here, to run repeatedly:

  
  //initial light
  for(int i = 0; i < LEDNUM; i++) 
    strip.setPixelColor(i, LedValue[i][0], LedValue[i][1], LedValue[i][2]);
  strip.show();

  while(true) {
    //Get the serial post messege
    chState = Serial.read();
    //No messege
    if (chState < 49 || chState > 53) {
      //flash
      controlFlash(LedValue, LedState, change, lightSpeed);
    }
    else {
      for(int i = 0; i < LEDNUM; i++)
        LedState[i] = chState - 49 + i;

      changeLedState(LedValue, LedState, lightSpeed);
    }
    for(int i = 0; i < LEDNUM; i++) 
      strip.setPixelColor(i, LedValue[i][0], LedValue[i][1], LedValue[i][2]);
    strip.show();

/*       
    Serial.println("In loop");
    Serial.print("LED 1: ");
    Serial.print(LedValue[0][0]);
    Serial.print(' ');
    Serial.print(LedValue[0][1]);
    Serial.print(' ');
    Serial.println(LedValue[0][2]);
    Serial.print("LED 2: ");
    Serial.print(LedValue[1][0]);
    Serial.print(' ');
    Serial.print(LedValue[1][1]);
    Serial.print(' ');
    Serial.println(LedValue[1][2]);

    delay(1000);
*/
  }
}

void clear(int pinNum) {
  for (int i = 0; i < pinNum; i++)
    strip.setPixelColor(i, 0, 0, 0);
  strip.show();
  
  return;
}

void controlFlash(float LedValue[LEDNUM][3], int LedState[], int change[], float lightSpeed[]) {
  for(int i = 0; i < LEDNUM; i++) {
    switch(LedState[i]){
      case 0:
        flash(&LedValue[i][0], change[i], lightSpeed[i]);
        change[i] = flash(&LedValue[i][2], change[i], lightSpeed[i]);
        break;
      case 1:
        change[i] = flash(&LedValue[i][0], change[i], lightSpeed[i]);
        break;
      case 2:
        flash(&LedValue[i][0], change[i], lightSpeed[i]);
        change[i] = flash(&LedValue[i][1], change[i], lightSpeed[i]);
        break;
      case 3:
        change[i] = flash(&LedValue[i][1], change[i], lightSpeed[i]);
        break;
      case 4:
        flash(&LedValue[i][1], change[i], lightSpeed[i]);
        change[i] = flash(&LedValue[i][2], change[i], lightSpeed[i]);
        break;
      case 5:
        change[i] = flash(&LedValue[i][2], change[i], lightSpeed[i]);
        break;
      default:
        break;
      }
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


void changeLedState(float LedValue[LEDNUM][3], int LedState[], float lightSpeed[]) {
  bool flag = true;
  while(flag) {
    bool flags[LEDNUM] = {};
    for(int i = 0; i < LEDNUM; i++)
      flags[i] = true;
      
    //run for all led
    for(int i = 0; i < LEDNUM; i++) {
      //set the value
      switch(LedState[i]) {
          case 0:
            if(LedValue[i][0] < TOP)
              LedValue[i][0] = LedValue[i][0] + 1*lightSpeed[i];
            if(LedValue[i][1] > 0)
              LedValue[i][1] = LedValue[i][1] - 1*lightSpeed[i];
            if(LedValue[i][2] < TOP)
              LedValue[i][2] = LedValue[i][2] + 1*lightSpeed[i];
              
            if(LedValue[i][0] == TOP && LedValue[i][1] == 0 && LedValue[i][2] == TOP)
              flags[i] = false;
            break;
            
          case 1:
            if(LedValue[i][0] < TOP)
              LedValue[i][0] = LedValue[i][0] + 1*lightSpeed[i];
            if(LedValue[i][1] > 0)
              LedValue[i][1] = LedValue[i][1] - 1*lightSpeed[i];
            if(LedValue[i][2] > 0)
              LedValue[i][2] = LedValue[i][2] - 1*lightSpeed[i];
              
            if(LedValue[i][0] == TOP && LedValue[i][1] == 0 && LedValue[i][2] == 0)
              flags[i] = false;
            break;

          case 2:
            if(LedValue[i][0] < TOP)
              LedValue[i][0] = LedValue[i][0] + 1*lightSpeed[i];
            if(LedValue[i][1] < 255)
              LedValue[i][1] = LedValue[i][1] + 1*lightSpeed[i];
            if(LedValue[i][2] > 0)
              LedValue[i][2] = LedValue[i][2] - 1*lightSpeed[i];

            if(LedValue[i][0] == TOP && LedValue[i][1] == 255 && LedValue[i][2] == 0)
              flags[i] = false;
            break;

          case 3:
            if(LedValue[i][0] > 0)
              LedValue[i][0] = LedValue[i][0] - 1*lightSpeed[i];
            if(LedValue[i][1] < TOP)
              LedValue[i][1] = LedValue[i][1] + 1*lightSpeed[i];
            if(LedValue[i][2] > 0)
              LedValue[i][2] = LedValue[i][2] - 1*lightSpeed[i];

            if(LedValue[i][0] == 0 && LedValue[i][1] == TOP && LedValue[i][2] == 0)
              flags[i] = false;
            break;

          case 4:
            if(LedValue[i][0] > 0)
              LedValue[i][0] = LedValue[i][0] - 1*lightSpeed[i];
            if(LedValue[i][1] < TOP)
              LedValue[i][1] = LedValue[i][1] + 1*lightSpeed[i];
            if(LedValue[i][2] < TOP)
              LedValue[i][2] = LedValue[i][2] + 1*lightSpeed[i];

            if(LedValue[i][0] == 0 && LedValue[i][1] == TOP && LedValue[i][2] == TOP)
              flags[i] = false;
            break;

          case 5:
            if(LedValue[i][0] > 0)
              LedValue[i][0] = LedValue[i][0] - 1*lightSpeed[i];
            if(LedValue[i][1] > 0)
              LedValue[i][1] = LedValue[i][1] - 1*lightSpeed[i];
            if(LedValue[i][2] < TOP)
              LedValue[i][2] = LedValue[i][2] + 1*lightSpeed[i];

            if(LedValue[i][0] == 0 && LedValue[i][1] == 0 && LedValue[i][2] == TOP)
              flags[i] = false;
            break;

          default:
            for(int i = 0; i < LEDNUM; i++)
              flags[i] = false;
            break;
      } //end switch

      //test if break the range
      for(int j = 0; j < 3; j++) {
        if(LedValue[i][j] > TOP)
          LedValue[i][j] = TOP;
        else if(LedValue[i][j] < 0)
          LedValue[i][j] = 0;
      } //end for loop
    } //end for loop

    flag = false;
    for(int i = 0; i < LEDNUM; i++)
      flag = flag || flags[i];

    for(int i = 0; i < LEDNUM; i++) 
      strip.setPixelColor(i, LedValue[i][0], LedValue[i][1], LedValue[i][2]);
    strip.show();
/*
    Serial.println("In change");
    Serial.print("LED 1: ");
    Serial.print(LedValue[0][0]);
    Serial.print(' ');
    Serial.print(LedValue[0][1]);
    Serial.print(' ');
    Serial.print(LedValue[0][2]);
    Serial.print(' ');
    Serial.println(flags[0]);
    Serial.print("LED 2: ");
    Serial.print(LedValue[1][0]);
    Serial.print(' ');
    Serial.print(LedValue[1][1]);
    Serial.print(' ');
    Serial.print(LedValue[1][2]);
    Serial.print(' ');
    Serial.println(flags[1]);
    Serial.println(flag);
    Serial.println();
    delay(1000);
*/
  } //end while

  return;
}
