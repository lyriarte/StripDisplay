## StripDisplay


Display text and bitmaps on strip led panels. 


### Acknowledgements

This programs uses the [QDBMP](http://qdbmp.sourceforge.net) library for bitmap management. 
The fonts used are the ISO8859 FixedMedium from the /usr/share/fonts/X11/misc/ folder on Linux.


### Code sample

```
#include <StripDisplay.h>


#define STRIPLED_GPIO 5
#define STRIPLED_W    32
#define STRIPLED_H    8

extern XBMFont fixedMedium_5x7;

CRGB leds[STRIPLED_W*STRIPLED_H];
StripDisplay strip(STRIPLED_GPIO, STRIPLED_W, STRIPLED_H, WRAP_COLUMNS, leds);

void setup() {
	FastLED.addLeds<NEOPIXEL,STRIPLED_GPIO>(leds, STRIPLED_W*STRIPLED_H);
	strip.setup(&fixedMedium_5x7);
	Serial.begin(9600);
	Serial.println(String(STRIPLED_W*STRIPLED_H) + String(" leds on gpio ") + String(strip.getGpio()));
}

void loop() {
	strip.setFgColor(CRGB(1,1,1));
	strip.setBgColor(CRGB(0,0,0));
	strip.setText("Hello");
	strip.setAlignment(ALIGN_LEFT);
	strip.displayText();
	FastLED.delay(1000);
	strip.setAlignment(ALIGN_CENTER);
	strip.displayText();
	FastLED.delay(1000);
	strip.setAlignment(ALIGN_RIGHT);
	strip.displayText();
	FastLED.delay(1000);
	strip.setAlignment(ALIGN_LEFT);
	strip.setFgColor(CRGB(4,2,0));
	strip.setBgColor(CRGB(0,0,1));
	strip.setText("Hello, world!");
	for (int i=0; i<50; i++) {
		strip.displayText(i);
		FastLED.delay(100);
	}
}
```
