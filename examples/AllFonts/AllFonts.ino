#define FONT_4x6_FIXED_MEDIUM
#define FONT_5x6_FIXED_MEDIUM
#define FONT_5x7_FIXED_MEDIUM
#define FONT_5x8_FIXED_MEDIUM
#define FONT_6x8_FIXED_MEDIUM
#define FONT_6x9_FIXED_MEDIUM
#define FONT_6x10_FIXED_MEDIUM
#define FONT_6x12_FIXED_MEDIUM
#define FONT_6x13_FIXED_MEDIUM
#define FONT_7x13_FIXED_BOLD
#define FONT_8x13_FIXED_MEDIUM
#define FONT_8x13_FIXED_BOLD

#include <StripDisplay.h>

#define N_FONT 12
XBMFont * fontPtrs[N_FONT] = {
	&fixedMedium_4x6,
	&fixedMedium_5x6,
	&fixedMedium_5x7,
	&fixedMedium_5x8,
	&fixedMedium_6x8,
	&fixedMedium_6x9,	
	&fixedMedium_6x10,	
	&fixedMedium_6x12,	
	&fixedMedium_6x13,	
	&fixedBold_7x13,	
	&fixedMedium_8x13,	
	&fixedBold_8x13	
};

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
	strip.setup();
	Serial.begin(9600);
	Serial.println(String(STRIPLED_W*STRIPLED_H*N_PANELS) + String(" leds on gpio ") + String(strip.getGpio()));
}

void loop() {
	// text display API setup
	strip.setFgColor(CRGB(4,2,0));
	strip.setBgColor(CRGB(0,0,1));
	strip.setAlignment(ALIGN_CENTER);
	strip.setText("Hey");
	// try all fonts
	for (int i=0; i<N_FONT; i++) {
		strip.setFont(fontPtrs[i]);
		// vertical alignment centered
		strip.setLine((BITMAP_H-fontPtrs[i]->getHeight())/2);
		strip.displayText();
		FastLED.delay(1000);
	}
}
