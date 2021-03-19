#ifndef StripDisplay_H
#define StripDisplay_H

#include <Arduino.h>
#include <FastLED.h>

#include "XBMFont.h"
#include "qdbmp.h"


enum {
	WRAP_LINES,
	WRAP_COLUMNS
};


class StripDisplay {

	public:

	StripDisplay(int gpio, int w, int h, int wrap, CRGB *leds);

	void setup();

	int getGpio();
	int getWidth();
	int getHeight();
	int getWrap();
	CRGB * getLeds();

	void setFont(XBMFont* fontP);
	void setText(String text);
	void setAlignment(int align);
	void setBgColor(CRGB bg);
	void setFgColor(CRGB fg);

	private:

	int gpio;
	int w;
	int h;
	int wrap;
	CRGB *leds;

	BMP* bmp;
	XBMFont* fontP;
	String text;
	int align;
	CRGB bg;
	CRGB fg;
};


#endif
