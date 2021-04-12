## StripDisplay


Display text and bitmaps on strip led panels. 


### Acknowledgements

This programs uses the [QDBMP](http://qdbmp.sourceforge.net) library for bitmap management. 
The fonts used are the ISO8859 FixedMedium from the /usr/share/fonts/X11/misc/ folder on Linux.


### Code sample

```
#define FONT_5x8_FIXED_MEDIUM
#include <StripDisplay.h>
XBMFont * fontP = &fixedMedium_5x8;

#define STRIPLED_GPIO 5
#define BITMAP_W	64
#define BITMAP_H	8
#define STRIPLED_W	32
#define STRIPLED_H	8

CRGB leds[STRIPLED_W*STRIPLED_H*2];
StripLEDPanel panels[] = {
{
	0,
	0,
	0,
	STRIPLED_W,
	STRIPLED_H,
	WRAP_COLUMNS
},
{
	STRIPLED_W*STRIPLED_H,
	STRIPLED_W,
	0,
	STRIPLED_W,
	STRIPLED_H,
	WRAP_COLUMNS
}
};

#define N_PANELS (sizeof(panels) / sizeof(StripLEDPanel))

StripDisplay strip(STRIPLED_GPIO, BITMAP_W, BITMAP_H, leds, panels, N_PANELS);

void setup() {
	FastLED.addLeds<NEOPIXEL,STRIPLED_GPIO>(leds, STRIPLED_W*STRIPLED_H*2);
	strip.setup(fontP);
	Serial.begin(9600);
	Serial.println(String(STRIPLED_W*STRIPLED_H) + String(" leds on gpio ") + String(strip.getGpio()));
}

void loop() {
	strip.setFgColor(CRGB(1,1,1));
	strip.setBgColor(CRGB(0,0,0));
	strip.setText("Hello");
	// text bitmap
	strip.setPixel(0,0,CRGB(16,0,0));
	strip.setPixel(BITMAP_W-1,0,CRGB(0,16,0));
	strip.setPixel(0,BITMAP_H-1,CRGB(0,0,16));
	strip.setPixel(BITMAP_W-1,BITMAP_H-1,CRGB(8,0,8));
	strip.renderText(2, 1, CRGB(4,2,0));
	strip.displayBitmap();
	FastLED.delay(2000);
	strip.setFgColor(CRGB(1,1,1));
	// text ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT
	for (int align=ALIGN_LEFT; align<=ALIGN_RIGHT; align++) {
		strip.setAlignment(align);
		strip.displayText();
		FastLED.delay(1000);
	}
	// scrolling offset
	strip.setAlignment(ALIGN_LEFT);
	strip.setFgColor(CRGB(4,2,0));
	strip.setBgColor(CRGB(0,0,1));
	strip.setText("Hello, world!");
	for (int offset=0; offset<strip.getTextWidth(); offset++) {
		strip.displayText(offset);
		FastLED.delay(100);
	}
}
```
