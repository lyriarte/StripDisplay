#include "StripDisplay.h"

StripDisplay::StripDisplay(int gpio, int w, int h, int wrap, CRGB *leds) {
	this->gpio = gpio;
	this->w = w;
	this->h = h; 
	this->wrap = wrap;
	this->leds = leds;
	bmp = NULL;
	fontP = NULL;
	align = ALIGN_LEFT;
	bg = CRGB(0,0,0);
	fg = CRGB(1,1,1);
}

void StripDisplay::setup(XBMFont* fontP) {
	setFont(fontP);
	pinMode(gpio, OUTPUT);
}

int StripDisplay::getGpio() {
	return gpio;
}

int StripDisplay::getWidth() {
	return w;
}

int StripDisplay::getHeight() {
	return h;
}

int StripDisplay::getWrap() {
	return wrap;
}

CRGB * StripDisplay::getLeds() {
	return leds;
}


void StripDisplay::setFont(XBMFont* fontP) {
	this->fontP = fontP;
	newTextBitmap();
}

void StripDisplay::setText(String text) {
	this->text = text;
	newTextBitmap();
}

void StripDisplay::setAlignment(int align) {
	this->align = align;
}

void StripDisplay::setBgColor(CRGB bg) {
	this->bg = bg;
}

void StripDisplay::setFgColor(CRGB fg) {
	this->fg = fg;
}



void StripDisplay::newTextBitmap() {
	if (bmp != NULL)
		BMP_Free(bmp);
	int textWidth = text.length() * fontP->getWidth();
	int textHeight = fontP->getHeight();
	bmp = BMP_Create(max(w, textWidth), max(h, textHeight), 24);
	if (bmp == NULL)
		Serial.println("Bitmap allocation failed");
}

void StripDisplay::fillBitmap(unsigned int x0, unsigned int y0, unsigned int dx, unsigned int dy, CRGB crgb) {
	for (unsigned int x=x0; x<x0+dx; x++)
		for (unsigned int y=y0; y<y0+dy; y++)
			BMP_SetPixelRGB(bmp, x, y, crgb.r, crgb.g, crgb.b);
}

void StripDisplay::blitBitmap(int i0, int ox, int oy, int dx, int dy) {
	int i=i0, ix, iy;
	int width = min((int)BMP_GetWidth(bmp),ox+dx);
	int height = min((int)BMP_GetHeight(bmp),oy+dy);
	byte r,g,b;
	if (wrap == WRAP_LINES) {
		for (int y=0; y<h; y++) {
			iy = y+oy;
			for (int x=0; x<w;x++) {
				ix = x+ox;
				if (ix>=0 && iy>=0 && ix<width && iy<height) {
					BMP_GetPixelRGB(bmp,ix,iy,&r,&g,&b);
					if (y%2 == 0) 
						leds[i] = CRGB(r, g, b);		   
					else 
						leds[w*(int)(i/w) + w - ((i%w) + 1)] = CRGB(r, g, b);		   
				}
				++i;
			}
		}
	}
	else {
		for (int x=0; x<w;x++) {
			ix = x+ox;
			for (int y=0; y<h; y++) {
				iy = y+oy;
				if (ix>=0 && iy>=0 && ix<width && iy<height) {
					BMP_GetPixelRGB(bmp,ix,iy,&r,&g,&b);
					if (x%2 == 0) 
						leds[i] = CRGB(r, g, b);		   
					else 
						leds[h*(int)(i/h) + h - ((i%h) + 1)] = CRGB(r, g, b);		   
				}
				++i;
			}
		}
	}
}

void StripDisplay::renderText(unsigned int x0, unsigned int y0, CRGB crgb) {
	unsigned int x = x0;
	for (int i=0; i<text.length(); i++) {
		char c = text.charAt(i);
		for (int j=0; j<fontP->getWidth(); j++) {
			for (int k=0; k<fontP->getHeight(); k++)
				if (fontP->getPixel(c,k,j))
					BMP_SetPixelRGB(bmp, x+j, y0+k, crgb.r, crgb.g, crgb.b);
		}
		x += fontP->getWidth();
	}
}

void StripDisplay::displayText(int offset) {
	int i0 = 0;
	int textWidth = text.length() * fontP->getWidth();
	int textHeight = fontP->getHeight();
	int width = min(w, textWidth);
	int height = min(h, textHeight);
	if (align == ALIGN_CENTER)
		i0 = (w-width)/2;
	else if (align == ALIGN_RIGHT)
		i0 = (w-width);
	// shift alignment on even columns
	if (align != ALIGN_LEFT && wrap == WRAP_COLUMNS)
		i0 = 2 * (int)(i0/2) * h;
	fillBitmap(0, 0, (int)BMP_GetWidth(bmp), (int)BMP_GetHeight(bmp), bg);
	blitBitmap(0, 0, 0, (int)BMP_GetWidth(bmp), (int)BMP_GetHeight(bmp));
	renderText(0, 0, fg);
	blitBitmap(i0, offset, 0, width, height);
}

