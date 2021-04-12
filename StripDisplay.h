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


typedef struct {
	int ledIndex;
	int bmpX;
	int bmpY;
	int w;
	int h;
	int wrap;
} StripLEDPanel;

class StripDisplay {

	public:

	StripDisplay(int gpio, int w, int h, CRGB *leds, StripLEDPanel *panels, int nPanels);

	void setup(XBMFont* fontP);

	int getGpio();
	int getWidth();
	int getHeight();
	CRGB * getLeds();
	StripLEDPanel * getPanels();
	int getNPanels();
	BMP * getBitmap();

	void setFont(XBMFont* fontP);
	void setText(String text);
	void setAlignment(int align);
	void setBgColor(CRGB bg);
	void setFgColor(CRGB fg);

	void newTextBitmap();
	void fillBitmap(unsigned int x0, unsigned int y0, unsigned int dx, unsigned int dy, CRGB crgb);
	void blitBitmap(int i0, int ox, int oy, int dx, int dy, int wrap);
	void renderText(unsigned int x0, unsigned int y0, CRGB crgb);
	void displayText(int offset=0);

	int getTextWidth();
	int getTextHeight();

	CRGB getPixel(unsigned int x, unsigned int y);
	void setPixel(unsigned int x, unsigned int y, CRGB crgb);
	void displayBitmap();

	private:

	int gpio;
	int w;
	int h;

	CRGB *leds;
	StripLEDPanel *panels;
	int nPanels;
	BMP* bmp;

	XBMFont* fontP;
	String text;
	int align;
	CRGB bg;
	CRGB fg;
};


#endif
