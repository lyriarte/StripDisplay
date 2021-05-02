#define FONT_6x9_FIXED_MEDIUM
#include <StripDisplay.h>
XBMFont * fontP = &fixedMedium_6x9;

#define STRIPLED_GPIO 5
#define STRIPLED_W	32
#define STRIPLED_H	8

CRGB leds[STRIPLED_W*STRIPLED_H];

StripDisplay strip(STRIPLED_GPIO, STRIPLED_W, STRIPLED_H, WRAP_COLUMNS, leds);

void setup() {
	FastLED.addLeds<NEOPIXEL,STRIPLED_GPIO>(leds, STRIPLED_W*STRIPLED_H);
	strip.setup(fontP);
	Serial.begin(9600);
	Serial.println(String(STRIPLED_W*STRIPLED_H) + String(" leds on gpio ") + String(strip.getGpio()));
}

void loop() {
	strip.setFgColor(CRGB(1,1,1));
	strip.setBgColor(CRGB(0,0,0));
	strip.setText("Hello");
	strip.displayText();
	FastLED.delay(1000);
}
