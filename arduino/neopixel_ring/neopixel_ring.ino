#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NEOPIXEL_PIN 6
#define NUM_PIXELS 60
#define BRIGHTNESS 16

int mod(int x, int m) {
  // modulo operator doesn't work as expected for negative numbers
  int r = x%m;
  return r<0 ? r+m : r;
}

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_RGBW + NEO_KHZ800);

// G R B W
uint32_t K = strip.Color(0, 0, 0, 0);
uint32_t G = strip.Color(255, 0, 0, 0);
uint32_t R = strip.Color(0, 255, 0, 0);
uint32_t B = strip.Color(0, 0, 255, 0);
uint32_t M = strip.Color(0, 255, 255, 0);
uint32_t C = strip.Color(255, 0, 255, 0);
uint32_t Y = strip.Color(255, 255, 0, 0);
uint32_t W = strip.Color(255, 255, 255, 0);
uint32_t WK = strip.Color(0, 0, 0, 255);
uint32_t WG = strip.Color(255, 0, 0, 255);
uint32_t WR = strip.Color(0, 255, 0, 255);
uint32_t WB = strip.Color(0, 0, 255, 255);
uint32_t WM = strip.Color(0, 255, 255, 255);
uint32_t WC = strip.Color(255, 0, 255, 255);
uint32_t WY = strip.Color(255, 255, 0, 255);
uint32_t WW = strip.Color(255, 255, 255, 255);


uint32_t buffer[NUM_PIXELS];

/*
struct spinner {
  int length;      // in pixels
  uint32_t color;  // base color
  int delay;       // update time
  bool direction;  // 0=CW, 1=CCW
};

spinner spinner1 = {10, R, 10, 0};
spinner spinner2 = {5, G, 5, 1};
*/

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
  delay(500);
  Serial.println("start");
  //spinner_init(10, 0, R);
  strip.show();
}

void spinner_init(int len, int offset, uint32_t color) {
  for(uint16_t i=offset; i<len; i++) {
    strip.setPixelColor(i % NUM_PIXELS, color);
  }
}

uint32_t color, new_color;
int t=0;
unsigned long time;

int num_updates;

void loop() {
  //ring_test();

  // animate_arbitrary_time_space();
  /*  
  */
  /*
  update_spinner(t, 10, 1, R);
  delay(20);
  */
  
  time = millis();
  num_updates = update_spinners(time);
  if(num_updates > 0) {
    draw_spinners_to_buffer();
    strip.show();
  }
  t++;
}

// how do i struct
const int NUM_SPINNERS = 3;
int starts[NUM_SPINNERS] = {0, 30, 0};
int lengths[NUM_SPINNERS] = {8, 10, 12};
int dirs[NUM_SPINNERS] = {1, -1, 1};
uint32_t colors[NUM_SPINNERS] = {R, G, B};
int delays[NUM_SPINNERS] = {25, 90, 50};
int last_updates[NUM_SPINNERS] = {0, 0, 0};

int update_spinners(unsigned long time) {
  int num_updates = 0;
  for(int spinner_idx=0; spinner_idx<NUM_SPINNERS; spinner_idx++) {
    if(time - last_updates[spinner_idx] > delays[spinner_idx]) {
      starts[spinner_idx] = mod(starts[spinner_idx] + dirs[spinner_idx], NUM_PIXELS);
      last_updates[spinner_idx] = time;
      num_updates++;
    }
  }
  return num_updates;
}


void draw_spinners_to_buffer() {
  int pixel;
  clear_buffer();
  for(int spinner_idx=0; spinner_idx<NUM_SPINNERS; spinner_idx++) {
    for(int n=0; n<lengths[spinner_idx]; n++) {
      pixel = mod(starts[spinner_idx] + dirs[spinner_idx] * n, NUM_PIXELS);
      color = strip.getPixelColor(pixel);
      new_color = color | decay_color(colors[spinner_idx], lengths[spinner_idx] - 1 - n);
      strip.setPixelColor(pixel, new_color);
    }
  }
}

uint32_t decay_color(uint32_t color, int n) {
  int32_t blue = color & 0xFF;
  int32_t red = (color >> 8) & 0xFF;
  int32_t green = (color >> 16) & 0xFF;
  int32_t white = (color >> 24) & 0xFF;
  red = decay_kernel_exponential(red, n);
  green = decay_kernel_exponential(green, n);
  blue = decay_kernel_exponential(blue, n);
  white = decay_kernel_exponential(white, n);
  return white << 24 | green << 16 | red << 8 | blue; 
}

byte decay_kernel_exponential(byte channel, int n) {
  return channel * pow(0.75, n);
}

byte decay_kernel_linear(byte channel, int n) {
  return max(channel - 16 * n, 0);
}


void clear_buffer() {
  for(int i=0; i<NUM_PIXELS; i++) {
    strip.setPixelColor(i, 0);
  }
}

/////////////////////////////////////////


void update_spinner(int t, int len, int speed, uint32_t color) {
  int head_index = (speed*t+len) % NUM_PIXELS;
  int tail_index = speed*t % NUM_PIXELS;
  strip.setPixelColor(tail_index, K);
  strip.setPixelColor(head_index, color);
}


void animate_arbitrary_time_space() {
  for(uint16_t i=0; i<60; i++) {
    color = get_ring_color(t, i);
    strip.setPixelColor(i, color);
    delay(5);
  }
}

uint32_t c[10] = {R, G, B, C, M, Y, W, WR, WG, WB};
uint32_t get_ring_color(int t, int i) {
  return c[i/6];  
}

void ring_test() {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 69, 174, 177);
    strip.show();
    delay(32);
  }
}
