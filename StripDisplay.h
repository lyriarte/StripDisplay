#ifndef StripDisplay_H
#define StripDisplay_H

#include <Arduino.h>
#include <FastLED.h>


#ifdef FONT_CHARSET_MEDIUM
#define BMP_STRIP_MASK 0x05	// BMP_STRIP_FLAG_0 | BMP_STRIP_FLAG_160
#define BMP_STRIP_0
#define BMP_STRIP_160
#endif

#ifdef FONT_CHARSET_SMALL
#define BMP_STRIP_MASK 0x07	// BMP_STRIP_FLAG_0 | BMP_STRIP_FLAG_96 | BMP_STRIP_FLAG_160
#define BMP_STRIP_0
#define BMP_STRIP_96
#define BMP_STRIP_160
#endif


#include "XBMFont.h"
#include "qdbmp.h"

#define GPIO_NONE -1            // User-managed GPIO setup

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

// first led origin
enum {
	ORIGIN_TOP_LEFT,
	ORIGIN_TOP_RIGHT,
	ORIGIN_BOTTOM_LEFT,
	ORIGIN_BOTTOM_RIGHT
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
	// panel first led origin
	int origin;
} StripLEDPanel;


// text rendering / bitmap display on a set of panels 
class StripDisplay {

	public:

	// initialize with a single panel, or chained identical panels 
	StripDisplay(int w, int h, int wrap, int origin, CRGB *leds);
	StripDisplay(int gpio, int w, int h, int wrap, int origin, CRGB *leds);
	// initialize with chained panels 
	StripDisplay(int w, int h, CRGB *leds, StripLEDPanel *panels, int nPanels);
	StripDisplay(int gpio, int w, int h, CRGB *leds, StripLEDPanel *panels, int nPanels);

	// initial setup
	void setup(XBMFont* fontP = NULL);

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
	// text alignment: Left, Center or Right
	void setAlignment(int align);
	// vertical text alignment in pixel lines from the top
	void setLine(int line);
	// background text color
	void setBgColor(CRGB bg);
	// foreground text color
	void setFgColor(CRGB fg);

	// allocate the bitmap for the screen size
	void newBitmap();
	// fill part of the bitmap with a single color
	void fillBitmap(unsigned int x0, unsigned int y0, unsigned int dx, unsigned int dy, CRGB crgb);
	// blit a bitmap region on a given panel 
	void blitBitmap(int i0, int ox, int oy, int dx, int dy, int wrap, int origin);

	// render xpm bitmap sprite at specific coordinates
	void renderXpm(int x0, int y0, int w, int h, unsigned char * charBytes, CRGB crgb);

	// render text in the bitmap at specific coordinates
	void renderText(int x0, int y0, CRGB crgb);
	// render text with horizontal and vertical alignment, scrolled at a given offset and display the bitmap
	void displayText(int offset=0, bool fillBg=true);

	// text dimensions in pixels
	int getTextWidth();
	int getTextHeight();

	// bitmap level APIs
	CRGB getPixel(unsigned int x, unsigned int y);
	void setPixel(unsigned int x, unsigned int y, CRGB crgb);
	void displayBitmap();

	private:

	void initPanel(int gpio, int w, int h, int wrap, int origin, CRGB *leds);
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
	int line;
	CRGB bg;
	CRGB fg;
};


#endif
