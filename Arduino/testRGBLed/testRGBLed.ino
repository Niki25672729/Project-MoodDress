// Addressable RGB LED Demo Sketch
// Dain Unicorn August 25, 2014
// If this code is of use to you, please make use of it, and let me know what your doing with it.
// This code is original to me, with references from the Arduino Example for generating Tones.
// A Special Thank you to the folks at Adafruit for their fine NeoPixel library that makes this sketch possible.
// And show some love to the folks at SparkFun where I got these 8mm Addressable RGB LEDs.

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, 6, NEO_RGB + NEO_KHZ800);

// The three parameters passed here are: Number of LEDs, Arduino Pin, Config information.
// For more help on the Config details, see the Example sketch provided with the Adafruit NeoPixel library.

int wait = 500;
float reduct = .85;
int ending = 0;

void setup() {
  // When power is first applied to the LEDs they will show a color based on the voltage being sent to them.  For the 5VDC
  // power from an Arduino Uno, it is a moderate blue color.  This is a normal function of the WS2812 chip when it doesn't have 
  // data to use.
  
  strip.begin();
  strip.show();
  
  // We initalize the NeoPixel Library here, by starting it and then sending the first strip.show() command.
  // Next we will tell all of the LEDs to switch off before continuing.
  
  pcr(); // PixelColorsReset function, it turns all of the LEDs completely off.
         // This custom function can be found at the bottom of this Sketch.

  // We play the melody once during setup with all 5 LEDs lighting up in the color for the tone being played.
  
  strip.setPixelColor(0, 100, 0, 0);
  strip.setPixelColor(1, 100, 0, 0);
  strip.setPixelColor(2, 100, 0, 0);
  strip.setPixelColor(3, 100, 0, 0);
  strip.setPixelColor(4, 100, 0, 0);
  strip.show();
  delay(wait);
  pcr();
  delay(wait/10);
  
  strip.setPixelColor(0, 170, 80, 10);
  strip.setPixelColor(1, 170, 80, 10);
  strip.setPixelColor(2, 170, 80, 10);
  strip.setPixelColor(3, 170, 80, 10);
  strip.setPixelColor(4, 170, 80, 10);
  strip.show();
  delay(wait);
  pcr();
  delay(wait/10);
  
  strip.setPixelColor(0, 120, 0, 200);
  strip.setPixelColor(1, 120, 0, 200);
  strip.setPixelColor(2, 120, 0, 200);
  strip.setPixelColor(3, 120, 0, 200);
  strip.setPixelColor(4, 120, 0, 200);
  strip.show();
  delay(wait);
  pcr();
  delay(wait/10);
  
  strip.setPixelColor(0, 128, 120, 0);
  strip.setPixelColor(1, 128, 120, 0);
  strip.setPixelColor(2, 128, 120, 0);
  strip.setPixelColor(3, 128, 120, 0);
  strip.setPixelColor(4, 128, 120, 0);
  strip.show();
  delay(wait);
  pcr();
  delay(wait/10);
  
  strip.setPixelColor(0, 140, 180, 180);
  strip.setPixelColor(1, 140, 180, 180);
  strip.setPixelColor(2, 140, 180, 180);
  strip.setPixelColor(3, 140, 180, 180);
  strip.setPixelColor(4, 140, 180, 180);
  strip.show();
  delay(wait);
  pcr();
  // We don't need a delay at the end here, as the next iteration of the loop delays at the start.
  
}

void loop() {
  
  // The melody has played in the setup loop, so we will play it again and again getting faster every time until its too fast.
  
  if (wait > 40) {
    
    delay(wait);
    
    notes();  // this custom function plays the tones with only one LED lighting up per tone.
              // The function itself is at the bottom of this Sketch.
              
    wait *= reduct;  // after the function returns, we decrease the wait time for the next loop
    
  } else {
    
    if (ending == 0) {
      // Once the wait varible is less than 40 we will play the melody one last time, with all the LEDs lit and at a set duration.
      // Then increment the ending varible so that the Sketch goes dark and silent until reset.  
      delay(2500);
      strip.setPixelColor(0, 100, 0, 0);
      strip.setPixelColor(1, 100, 0, 0);
      strip.setPixelColor(2, 100, 0, 0);
      strip.setPixelColor(3, 100, 0, 0);
      strip.setPixelColor(4, 100, 0, 0);
      strip.show();
      delay(500);
      pcr();
      delay(50);
      
      strip.setPixelColor(0, 170, 80, 10);
      strip.setPixelColor(1, 170, 80, 10);
      strip.setPixelColor(2, 170, 80, 10);
      strip.setPixelColor(3, 170, 80, 10);
      strip.setPixelColor(4, 170, 80, 10);
      strip.show();
      delay(500);
      pcr();
      delay(50);
      
      strip.setPixelColor(0, 120, 0, 200);
      strip.setPixelColor(1, 120, 0, 200);
      strip.setPixelColor(2, 120, 0, 200);
      strip.setPixelColor(3, 120, 0, 200);
      strip.setPixelColor(4, 120, 0, 200);
      strip.show();
      delay(500);
      pcr();
      delay(50);
      
      strip.setPixelColor(0, 128, 120, 0);
      strip.setPixelColor(1, 128, 120, 0);
      strip.setPixelColor(2, 128, 120, 0);
      strip.setPixelColor(3, 128, 120, 0);
      strip.setPixelColor(4, 128, 120, 0);
      strip.show();
      delay(500);
      pcr();
      delay(50);
      
      strip.setPixelColor(0, 140, 180, 180);
      strip.setPixelColor(1, 140, 180, 180);
      strip.setPixelColor(2, 140, 180, 180);
      strip.setPixelColor(3, 140, 180, 180);
      strip.setPixelColor(4, 140, 180, 180);
      strip.show();
      delay(1500);
      pcr();
      ending++;
  
    }
  }
}
  
void pcr() {
  // This function turns all the LEDs off, reseting them.
  // I wrote this function to overcome the only real shortcomming I saw in the Adafruit Library, a reset command.
  strip.setPixelColor(0, 0, 0, 0);
  strip.setPixelColor(1, 0, 0, 0);
  strip.setPixelColor(2, 0, 0, 0);
  strip.setPixelColor(3, 0, 0, 0);
  strip.setPixelColor(4, 0, 0, 0);
  strip.show();
  return;
}

void notes() {
  
  // This function plays the melody, lighting up only the LED that corresponds to the tone played.
  pcr();
  strip.setPixelColor(0, 100, 0, 0);
  strip.setPixelColor(1, 0, 0, 0);
  strip.setPixelColor(2, 0, 0, 0);
  strip.setPixelColor(3, 0, 0, 0);
  strip.setPixelColor(4, 0, 0, 0);
  strip.show();
  delay(wait);
  pcr();
  delay(wait/10);
  
  strip.setPixelColor(0, 0, 0, 0);
  strip.setPixelColor(1, 170, 80, 10);
  strip.setPixelColor(2, 0, 0, 0);
  strip.setPixelColor(3, 0, 0, 0);
  strip.setPixelColor(4, 0, 0, 0);
  strip.show();
  delay(wait);
  pcr();
  delay(wait/10);
  
  strip.setPixelColor(0, 0, 0, 0);
  strip.setPixelColor(1, 0, 0, 0);
  strip.setPixelColor(2, 120, 0, 200);
  strip.setPixelColor(3, 0, 0, 0);
  strip.setPixelColor(4, 0, 0, 0);
  strip.show();
  delay(wait);
  pcr();
  delay(wait/10);
  
  strip.setPixelColor(0, 0, 0, 0);
  strip.setPixelColor(1, 0, 0, 0);
  strip.setPixelColor(2, 0, 0, 0);
  strip.setPixelColor(3, 128, 120, 0);
  strip.setPixelColor(4, 0, 0, 0);
  strip.show();
  delay(wait);
  pcr();
  delay(wait/10);
  
  strip.setPixelColor(0, 0, 0, 0);
  strip.setPixelColor(1, 0, 0, 0);
  strip.setPixelColor(2, 0, 0, 0);
  strip.setPixelColor(3, 0, 0, 0);
  strip.setPixelColor(4, 140, 180, 180);
  strip.show();
  delay(wait);
  pcr();
  return;

}
