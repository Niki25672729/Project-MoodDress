#define LEDNUM 5
#define LEDPIN 5
#define SPEED 0.1
#define TOP 255
#define BOTTOM 10
#define FLASHDELAY 500

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUM, LEDPIN, NEO_RGB + NEO_KHZ800);

int switchPin = A5;
int switchValue = 0;  //0: on, 1: off
int buttonPin = A4;
int buttonValue = 0;

float LedValue[LEDNUM][3] = {{}};  //{r, g, b}
int LedState[LEDNUM] = {}; //0: purple{255, 0, 255}, 1: red{255, 0, 0}, 2: yellow{255, 255, 0}, 3: green{0, 255, 0}, 4: clay{0, 255, 255}, 5: blue{0, 0, 255}
int change[LEDNUM] = {};
float lightSpeed[LEDNUM] = {};
int chState = 0;
bool changedLightComplite[LEDNUM] = {};

int loopCount = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);

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
  switchValue = digitalRead(switchPin);
  if(switchValue == HIGH) {   // Auto Flash
    // initial
    clear(LEDNUM);
    for(int i = 0; i < LEDNUM; i++) {
      LedState[i] = 0;
      changedLightComplite[i] = false;
      lightSpeed[i] = SPEED;
    }
    loopCount = 0;

    while(switchValue == HIGH) {
      // how many leds to control
      int flag = 0;
      for(int i = LEDNUM-1; i > 0; i--) {
        if(loopCount > FLASHDELAY*i) {
          flag = i;
          break;
        }
      }
      // flash
      for(int i = 0; i <= flag; i++) {
        changeLedLight(LedValue[i], LedState[i], lightSpeed[i], &changedLightComplite[i]);
        if(changedLightComplite[i] == true) {
          LedState[i] = (LedState[i]+1)%6;
          changedLightComplite[i] = false;
        }
      }
  
      if(loopCount <= FLASHDELAY*(LEDNUM-1))
        loopCount++;
        
      show(LedValue);
      
      switchValue = digitalRead(switchPin);
/*
      Serial.print("0: State ");
      Serial.print(LedState[0]);
      Serial.print(", ");
      Serial.print(LedValue[0][0]);
      Serial.print(", ");
      Serial.print(LedValue[0][1]);
      Serial.print(", ");
      Serial.println(LedValue[0][2]);

      Serial.print("1: State ");
      Serial.print(LedState[1]);
      Serial.print(", ");
      Serial.print(LedValue[1][0]);
      Serial.print(", ");
      Serial.print(LedValue[1][1]);
      Serial.print(", ");
      Serial.println(LedValue[1][2]);

      Serial.print("2: State ");
      Serial.print(LedState[2]);
      Serial.print(", ");
      Serial.print(LedValue[2][0]);
      Serial.print(", ");
      Serial.print(LedValue[2][1]);
      Serial.print(", ");
      Serial.println(LedValue[2][2]);

      Serial.print("3: State ");
      Serial.print(LedState[3]);
      Serial.print(", ");
      Serial.print(LedValue[3][0]);
      Serial.print(", ");
      Serial.print(LedValue[3][1]);
      Serial.print(", ");
      Serial.println(LedValue[3][2]);

      Serial.print("4: State ");
      Serial.print(LedState[4]);
      Serial.print(", ");
      Serial.print(LedValue[4][0]);
      Serial.print(", ");
      Serial.print(LedValue[4][1]);
      Serial.print(", ");
      Serial.println(LedValue[4][2]);
*/
      //delay(1000);
      }    // end while
  }    // end if
  else {                             // Change Mode
    // initial value
    clear(LEDNUM);
    for(int i = 0; i < LEDNUM; i++) {
      randomSeed(analogRead(A2));
      LedState[i] = random(6);
      lightSpeed[i] = random(5, 10)*0.01;
      changedLightComplite[i] = false;
    }
    bool flag = false;
    for(int i = 0; i < LEDNUM; i++) {
      Serial.print("Index ");
      Serial.print(i);
      Serial.print(": speed ");
      Serial.print(lightSpeed[i]);
      Serial.print(", state ");
      Serial.println(LedState[i]);
    }
    Serial.println(" ");

    while(switchValue == LOW) {
      // flash or changelight
      for(int i = 0; i < LEDNUM; i++) {
        if(changedLightComplite[i])
          controlFlash(LedValue[i], LedState[i], &change[i], lightSpeed[i]);
        else
          changeLedLight(LedValue[i], LedState[i], lightSpeed[i], &changedLightComplite[i]);
      }
      

      buttonValue = digitalRead(buttonPin);
      if(buttonValue == 1) {
        if(flag) {
          randomSeed(analogRead(A2));
          int numOfChange = random(1, LEDNUM);
          int indices[numOfChange];
          for(int j = 0; j < numOfChange; j++)
            indices[j] = -1;
          for(int i = 0; i < numOfChange; i++) {
            randomSeed(analogRead(A3));
            
            int index;
            bool flag = true;    // test if the index is repeat
            while(flag) {
              index = random(LEDNUM);
              flag = false;
              for(int j = 0; j < i; j++) {
                if(index == indices[j]) {
                  flag = true;
                  break;
                }    // end if
              }    // end for
            }    // end while
            indices[i] = index;
            
            int cState = random(6);
            float cSpeed = random(5, 10)*0.01;
            while(cState == LedState[index])
              cState = random(6);
            
            Serial.print("Change index ");
            Serial.print(index);
            Serial.print(" from state ");
            Serial.print(LedState[index]);
            Serial.print(" to ");
            
            lightSpeed[index] = cSpeed;
            LedState[index] = cState;
            changedLightComplite[index] = false;
            
            Serial.println(LedState[index]);
          }    // end for
          Serial.println(" ");
          
          flag = false;
          for(int i = 0; i < LEDNUM; i++) {
            Serial.print("Index ");
            Serial.print(i);
            Serial.print(": speed ");
            Serial.print(lightSpeed[i]);
            Serial.print(", state ");
            Serial.println(LedState[i]);
          }    // end for
          Serial.println(" ");
        }    // end if
      }    // end if
      else {
        if(!flag)
          flag = true;
      }    // end else
      
      show(LedValue);
      switchValue = digitalRead(switchPin);
    }    // end while
  }    // end else
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
