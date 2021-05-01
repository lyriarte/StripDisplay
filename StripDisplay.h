#ifndef StripDisplay_H
#define StripDisplay_H

#include <Arduino.h>
#include <FastLED.h>

#include "XBMFont.h"
#include "qdbmp.h"


// text alignment
enum {
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};

// strip LED wrapping
enum {
	WRAP_LINES,
	WRAP_COLUMNS
};


// position info for chained panels
typedef struct {
	// index in the global strip of the panel's first LED
	int ledIndex;
	// top left LED coordinates in the global bitmap
	int bmpX;
	int bmpY;
	// panel extent
	int w;
	int h;
	// strip LED wrapping in panel
	int wrap;
} StripLEDPanel;


// text rendering / bitmap display on a set of panels 
class StripDisplay {

	public:

	// initialize with a single panel, or chained identical panels 
	StripDisplay(int gpio, int w, int h, int wrap, CRGB *leds);
	// initialize with chained panels 
	StripDisplay(int gpio, int w, int h, CRGB *leds, StripLEDPanel *panels, int nPanels);

	// initial bitmap allocation at setup
	void setup(XBMFont* fontP);

	int getGpio();
	
	// display extent
	int getWidth();
	int getHeight();
	
	// low level LED access with FastLED 
	CRGB * getLeds();
	
	// low level panels access
	StripLEDPanel * getPanels();
	int getNPanels();
	
	// low level bitmap access
	BMP * getBitmap();

	// text display API setup
	void setFont(XBMFont* fontP);
	void setText(String text);
	void setAlignment(int align);
	void setBgColor(CRGB bg);
	void setFgColor(CRGB fg);

	// allocate the bitmap for the screen size
	void newBitmap();
	// fill part of the bitmap with a single color
	void fillBitmap(unsigned int x0, unsigned int y0, unsigned int dx, unsigned int dy, CRGB crgb);
	// blit a bitmap region on a given panel 
	void blitBitmap(int i0, int ox, int oy, int dx, int dy, int wrap);
	
	// render text in the bitmap at specific coordinates
	void renderText(int x0, int y0, CRGB crgb);
	// render text scrolled at a given offset and display the bitmap
	void displayText(int offset=0, bool fillBg=true);

	// text dimensions in pixels
	int getTextWidth();
	int getTextHeight();

	// bitmap level APIs
	CRGB getPixel(unsigned int x, unsigned int y);
	void setPixel(unsigned int x, unsigned int y, CRGB crgb);
	void displayBitmap();

	private:

	void init(int gpio, int w, int h, CRGB *leds, StripLEDPanel *panels, int nPanels);

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
