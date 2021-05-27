#define FONT_8x13_FIXED_BOLD
#include <StripDisplay.h>
XBMFont * fontP = &fixedBold_8x13;

#define STRIPLED_GPIO 5
#define BITMAP_W	32
#define BITMAP_H	16
#define STRIPLED_W	32
#define STRIPLED_H	8

// stack two 32x8 panels vertically, 2nd panel reversed
StripLEDPanel panels[] = {
{
	0,
	0,
	0,
	STRIPLED_W,
	STRIPLED_H,
	WRAP_COLUMNS,
	ORIGIN_TOP_LEFT
},
{
	STRIPLED_W*STRIPLED_H, // LED index 256
	0, // x0=0
	STRIPLED_H, // y0=8
	STRIPLED_W,
	STRIPLED_H,
	WRAP_COLUMNS,
	ORIGIN_BOTTOM_RIGHT
}
};
#define N_PANELS (sizeof(panels) / sizeof(StripLEDPanel))

CRGB leds[STRIPLED_W*STRIPLED_H*N_PANELS];
StripDisplay strip(STRIPLED_GPIO, BITMAP_W, BITMAP_H, leds, panels, N_PANELS);

void setup() {
	FastLED.addLeds<NEOPIXEL,STRIPLED_GPIO>(leds, STRIPLED_W*STRIPLED_H*N_PANELS);
	strip.setup(fontP);
	Serial.begin(9600);
	Serial.println(String(STRIPLED_W*STRIPLED_H*N_PANELS) + String(" leds on gpio ") + String(strip.getGpio()));
}

void loop() {
	// text display API setup
	strip.setFgColor(CRGB(1,1,1));
	strip.setBgColor(CRGB(0,0,0));
	strip.setText("Hey");
	// bitmap level APIs
	strip.setPixel(0,0,CRGB(16,0,0));
	strip.setPixel(BITMAP_W-1,0,CRGB(0,16,0));
	strip.setPixel(0,BITMAP_H-1,CRGB(0,0,16));
	strip.setPixel(BITMAP_W-1,BITMAP_H-1,CRGB(8,0,8));
	// render text on bitmap
	strip.renderText(fontP->getWidth()/2, (BITMAP_H-fontP->getHeight())/2, CRGB(4,2,0));
	// display bitmap
	strip.displayBitmap();
	FastLED.delay(2000);
	// text alignment example
	strip.setFgColor(CRGB(1,1,1));
	// text ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT
	for (int align=ALIGN_LEFT; align<=ALIGN_RIGHT; align++) {
		strip.setAlignment(align);
		strip.displayText();
		FastLED.delay(1000);
	}
	// text scrolling example
	strip.setAlignment(ALIGN_LEFT);
	strip.setFgColor(CRGB(4,2,0));
	strip.setBgColor(CRGB(0,0,1));
	strip.setText("Hello, world!");
	for (int offset=0; offset<strip.getTextWidth(); offset++) {
		strip.displayText(offset);
		FastLED.delay(100);
	}
}
