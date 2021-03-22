#ifndef StripDisplay_H
#define StripDisplay_H

#include <Arduino.h>
#include <FastLED.h>

#include "XBMFont.h"
#include "qdbmp.h"


enum {
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};

enum {
	WRAP_LINES,
	WRAP_COLUMNS
};


class StripDisplay {

	public:

	StripDisplay(int gpio, int w, int h, int wrap, CRGB *leds);

	void setup(XBMFont* fontP);

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

	void newTextBitmap();
	void fillBitmap(unsigned int x0, unsigned int y0, unsigned int dx, unsigned int dy, CRGB crgb);
	void blitBitmap(int i0, int ox, int oy, int dx, int dy);
	void renderText(unsigned int x0, unsigned int y0, CRGB crgb);
	void displayText(int offset=0);

	int getTextWidth();
	int getTextHeight();

	CRGB getPixel(unsigned int x, unsigned int y);
	void setPixel(unsigned int x, unsigned int y, CRGB crgb);
	void displayBitmap(int i0=0);

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
