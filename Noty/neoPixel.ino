#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define LED_PIN    14

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 7

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void neopixel_strip_setup() {
  // Initialize neo-pixel
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255) 
}

// Solid Color Fill
void solid(String cstr) {
  uint32_t color = hexToColor(cstr);
  Serial.println("Solid Called With Color: " + color);
  for (int i=0; i<LED_COUNT; i++) {
    strip.setPixelColor(i,color);
    strip.show();
    delay(30); // Make Light on Animated !
  }
}

// Chase Color Animation
void chase(String cstr) {
  uint32_t color = hexToColor(cstr);
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(50);  // Pause for a moment
    }
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void chaseRainbow(int repeat) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<repeat; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(50);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

uint32_t hexToColor(String color) {
  return strtoul(color.c_str(), NULL, 16);
}
