#include <Adafruit_NeoPixel.h>
#include <math.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


/*
ideally, want each pixel to have a known x, y, and be able to set color as a function of those.
also, don't want to define every single value by hand, so want to use vector math to generate it
but might not have enough space for that on the trinket

v/^ indicates 
                 
            v   _v     v  
|\/|     |\ |  |_   \ / 
|  |  o  | \|  |_    |
   ^
6*8   60  6*8   5*8  5*8
48    60  48    40   40
*/

#define BRIGHTNESS 24


int trigger_int_pin = 3;
uint16_t time = 0;
volatile int mode = 0;


int num_pixels[] = {48, 60, 48, 40, 40};
int letter_pins[] = {1, 4, 5, 6, 8};

// NOTE: the O might have a different RGB/GRB 
Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(num_pixels[0], letter_pins[0], NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(num_pixels[1], letter_pins[1], NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(num_pixels[2], letter_pins[2], NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(num_pixels[3], letter_pins[3], NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(num_pixels[4], letter_pins[4], NEO_GRBW + NEO_KHZ800);



void setup() {
  strip0.begin();
  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip4.begin();

  strip0.setBrightness(BRIGHTNESS);
  strip1.setBrightness(BRIGHTNESS);
  strip2.setBrightness(BRIGHTNESS);
  strip3.setBrightness(BRIGHTNESS);
  strip4.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
  delay(500);
  Serial.println("start");

  pinMode(trigger_int_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(trigger_int_pin), handle_rising_trigger, RISING);
  attachInterrupt(digitalPinToInterrupt(trigger_int_pin), handle_falling_trigger, FALLING);
}


void loop() {
  update0(time);
  update1(time);
  update2(time);
  update3(time);
  update4(time);
  delay(20);
  time++;
}

void handle_rising_trigger() {
    mode = 1;
    Serial.println("interrupt: mode=1");
}

void handle_falling_trigger() {
    mode = 0;
    Serial.println("interrupt: mode=0");
}


int get_period() {
  if(mode==0) {
      return 50;
    } else if(mode==1) {
      return 10;
    }
}

void update0(int time) {
  int period = get_period();
  int t_flag = time % period < period/2;
  for (int i = 0; i < num_pixels[1]; i++) {  
    uint8_t r = t_flag ? 0 : 255;
    uint8_t g = t_flag ? 255 : 0;
    strip0.setPixelColor(i, strip1.Color(r,g,0, 0));
  }
  strip0.show();
}

void update1(int time) {
  int period = get_period();
  int t_flag = time % period < period/2;
  for (int i = 0; i < num_pixels[1]; i++) {  
    uint8_t r = t_flag ? 0 : 255;
    uint8_t g = t_flag ? 255 : 0;
    strip1.setPixelColor(i, strip1.Color(r,g,0, 0));
  }
  strip1.show();
}

void update2(int time) {
  int period = get_period();
  int t_flag = time % period < period/2;
  for (int i = 0; i < num_pixels[2]; i++) {
    uint8_t r = t_flag ? 255 : 0;
    uint8_t g = t_flag ? 0 : 255;
    uint8_t b = t_flag ? 255 : 0;
    strip2.setPixelColor(i, strip1.Color(r,g,b, 0));
  }
  strip2.show();
}

void update3(int time) {
  int period = get_period();
  int t_flag = time % period < period/2;
  for (int i = 0; i < num_pixels[1]; i++) {  
    uint8_t r = t_flag ? 0 : 255;
    uint8_t g = t_flag ? 255 : 0;
    strip3.setPixelColor(i, strip1.Color(r,g,0, 0));
  }
  strip3.show();
}

void update4(int time) {
  int period = get_period();
  int t_flag = time % period < period/2;
  for (int i = 0; i < num_pixels[1]; i++) {  
    uint8_t r = t_flag ? 0 : 255;
    uint8_t g = t_flag ? 255 : 0;
    strip4.setPixelColor(i, strip1.Color(r,g,0, 0));
  }
  strip4.show();
}
