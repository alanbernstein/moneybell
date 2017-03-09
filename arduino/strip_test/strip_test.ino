// Simple NeoPixel test.  Lights just a few pixels at a time so a
// 1m strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip (the end wires, if
// any, are no indication -- look instead for the data direction
// arrows printed on the strip).

#include <Adafruit_NeoPixel.h>

#define PIN      0
#define N_LEDS 60
#define TRIGGER_PIN 10

Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(N_LEDS, 0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(N_LEDS, 1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(N_LEDS, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(N_LEDS, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(N_LEDS, 4, NEO_GRB + NEO_KHZ800);


void setup() {
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  
  strip0.begin();
  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip4.begin();
}

void loop() {
  while(1) {
    if(digitalRead(TRIGGER_PIN)) {
      // 28800 = 12 * 60 * 60 / (1.5), 1.5 = .025 * 60
      for(long int n=0; n<6; n++) {
        chase(strip0.Color(255, 0, 0)); // Red  
      }
    }
  }
  //  chase(strip.Color(0, 255, 0)); // Green
  //chase(strip.Color(0, 0, 255)); // Blue
}

static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip0.numPixels()+4; i++) {
      strip0.setPixelColor(i  , c); // Draw new pixel
      strip0.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip0.show();
      strip1.setPixelColor(i  , c); // Draw new pixel
      strip1.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip1.show();
      strip2.setPixelColor(i  , c); // Draw new pixel
      strip2.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip2.show();
      strip3.setPixelColor(i  , c); // Draw new pixel
      strip3.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip3.show();
      strip4.setPixelColor(i  , c); // Draw new pixel
      strip4.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip4.show();
      delay(25);
  }
}
