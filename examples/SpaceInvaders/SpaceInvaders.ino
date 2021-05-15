#include <StripDisplay.h>

#include "space_invader_01.h"
#include "space_invader_02.h"
#include "space_invader_03.h"
#include "space_invader_04.h"
#include "space_invader_05.h"
#include "space_invader_06.h"
#include "space_invader_07.h"

#define STRIPLED_GPIO 5
#define BITMAP_W  64
#define BITMAP_H  8
#define STRIPLED_W  64
#define STRIPLED_H  8

// stack two 32x8 panels horizontally
StripLEDPanel panels[] = {
{
  0,
  0,
  0,
  STRIPLED_W,
  STRIPLED_H,
  WRAP_COLUMNS
}
};
#define N_PANELS (sizeof(panels) / sizeof(StripLEDPanel))

CRGB leds[STRIPLED_W*STRIPLED_H*N_PANELS];
StripDisplay strip(STRIPLED_GPIO, BITMAP_W, BITMAP_H, leds, panels, N_PANELS);

void setup() {
  FastLED.addLeds<NEOPIXEL,STRIPLED_GPIO>(leds, STRIPLED_W*STRIPLED_H*N_PANELS);
  strip.setup();
  Serial.begin(9600);
  Serial.println(String(STRIPLED_W*STRIPLED_H*N_PANELS) + String(" leds on gpio ") + String(strip.getGpio()));
}


void loop() {
  // clear bitmap
  strip.fillBitmap(0,0,BITMAP_W,BITMAP_H,CRGB(0,0,0));
  // render sprites
  strip.renderXpm(00,-1,space_invader_01_width,space_invader_01_height,(unsigned char *)space_invader_01_bits,CRGB(4,2,0));
  strip.renderXpm(16,-1,space_invader_03_width,space_invader_03_height,(unsigned char *)space_invader_03_bits,CRGB(2,0,4));
  strip.renderXpm(32,-1,space_invader_05_width,space_invader_05_height,(unsigned char *)space_invader_05_bits,CRGB(0,2,4));
  strip.renderXpm(48,-1,space_invader_05_width,space_invader_07_height,(unsigned char *)space_invader_07_bits,CRGB(2,4,0));
  
  // display bitmap
  strip.displayBitmap();
  FastLED.delay(500);
  
  // clear bitmap
  strip.fillBitmap(0,0,BITMAP_W,BITMAP_H,CRGB(0,0,0));
  // render sprites
  strip.renderXpm(00,-1,space_invader_02_width,space_invader_02_height,(unsigned char *)space_invader_02_bits,CRGB(4,2,0));  
  strip.renderXpm(16,-1,space_invader_04_width,space_invader_04_height,(unsigned char *)space_invader_04_bits,CRGB(2,0,4));
  strip.renderXpm(32,-1,space_invader_06_width,space_invader_06_height,(unsigned char *)space_invader_06_bits,CRGB(0,2,4));
  strip.renderXpm(48,-1,space_invader_05_width,space_invader_07_height,(unsigned char *)space_invader_07_bits,CRGB(0,4,2));
  
  // display bitmap
  strip.displayBitmap();
  FastLED.delay(500);
  
}
