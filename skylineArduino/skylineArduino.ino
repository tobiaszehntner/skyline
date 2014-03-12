
#include "FastLED.h"      // LED library
#include <avr/pgmspace.h> // include library to enable saving to PROGMEM
#define DATA_PIN 6        // Data output to LED strip on Arduino



/////////// PASTE DATA OUTPUT FROM OPEN FRAMEWORKS ///////////



/////////// END OF OPEN FRAMEWORKS ///////////

CRGB leds[NUM_LEDS];    
byte currentKey;     
byte nextKey;           
unsigned long currentTime; 
unsigned long lastTime = 0;
byte red;
byte green;
byte blue;
unsigned long currentKeyMillis;
unsigned long nextKeyMillis;

byte brightness = 255;                        // Overall brightness of LED strip
unsigned long runTimeMillis = 24* 60000;      // current run time of loop: 24mins

void setup() {
      Serial.begin(9600);
      delay(2000);
      LEDS.setBrightness(brightness);
      FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);    // initiate LED library
     
     currentKey = 0;
     nextKey = 1;
     currentKeyMillis = map(TIMESTAMPS_ARRAY[currentKey], 0, 1440, 0, runTimeMillis);  // calculate millisecond position of keyframes
     nextKeyMillis = map(TIMESTAMPS_ARRAY[nextKey], 0, 1440, 0, runTimeMillis);
     
}


void loop() {

currentTime = millis() % runTimeMillis;     // update timer (running in milliseconds and loops every runTimeMillis)

if(currentTime < lastTime) {                // if timer has looped, set next keyframe to 0 (last and first keyframe have to be the same, no transition between)
  currentKey = NUM_KEYS - 1;
  nextKey = 0;
  currentKeyMillis = map(TIMESTAMPS_ARRAY[currentKey], 0, 1440, 0, runTimeMillis);
  nextKeyMillis = map(TIMESTAMPS_ARRAY[nextKey], 0, 1440, 0, runTimeMillis);
}


lastTime = currentTime;


for(int j = nextKey; j < NUM_KEYS; j++) {  
  
  if (currentTime >= nextKeyMillis) {    // is it time for the next keyframe?
    
     currentKey = j;                     
     nextKey = j + 1;                   // advance keyframe timer +1
  
    break;                              // break out of for-loop as soon as we found next keyframe
  }  
}

currentKeyMillis = map(TIMESTAMPS_ARRAY[currentKey], 0, 1440, 0, runTimeMillis);
nextKeyMillis = map(TIMESTAMPS_ARRAY[nextKey], 0, 1440, 0, runTimeMillis);
 ////// 
 
 
 for(int i = 0; i<NUM_LEDS; i++) {         // cycle through each pixel, calculate current position between keyframes and map color
   
     red = map(currentTime, currentKeyMillis, nextKeyMillis, pgm_read_byte_near(*RGB_ARRAY + currentKey * NUM_LEDS * 3 + i * 3), pgm_read_byte_near(*RGB_ARRAY + nextKey * NUM_LEDS * 3 + i * 3));
     green = map(currentTime, currentKeyMillis, nextKeyMillis, pgm_read_byte_near(*RGB_ARRAY + currentKey * NUM_LEDS * 3 + i * 3 + 1), pgm_read_byte_near(*RGB_ARRAY + nextKey * NUM_LEDS * 3 + i * 3 + 1));
     blue = map(currentTime, currentKeyMillis, nextKeyMillis, pgm_read_byte_near(*RGB_ARRAY + currentKey * NUM_LEDS * 3 + i * 3 + 2), pgm_read_byte_near(*RGB_ARRAY + nextKey * NUM_LEDS * 3 + i * 3 + 2));
   
     leds[i] = CRGB(red, green, blue);   // send color data to pixel

 }

//   
//Serial.print(currentTime);
//     Serial.print(",");
//     Serial.print(currentKey);
//     Serial.print(",");
//     Serial.print(nextKey);
//     Serial.print(",");
//     Serial.println();
     

    LEDS.show();      // turn on LEDs
    
    
//     delay(10);
}
