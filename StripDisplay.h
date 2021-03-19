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

	private:
	int gpio;
	int w;
	int h;
	int wrap;
	CRGB *leds;
};


#endif
