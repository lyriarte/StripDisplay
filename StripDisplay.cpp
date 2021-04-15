#include "StripDisplay.h"

StripDisplay::StripDisplay(int gpio, int w, int h, CRGB *leds, StripLEDPanel *panels, int nPanels) {
	this->gpio = gpio;
	this->w = w;
	this->h = h; 
	this->leds = leds;
	this->panels = panels;
	this->nPanels = nPanels;
	bmp = NULL;
	fontP = NULL;
	align = ALIGN_LEFT;
	bg = CRGB(0,0,0);
	fg = CRGB(1,1,1);
}

void StripDisplay::setup(XBMFont* fontP) {
	setFont(fontP);
	pinMode(gpio, OUTPUT);
	newTextBitmap();
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

CRGB * StripDisplay::getLeds() {
	return leds;
}

StripLEDPanel * StripDisplay::getPanels() {
	return panels;
}

int StripDisplay::getNPanels() {
	return nPanels;
}

BMP * StripDisplay::getBitmap() {
	return bmp;
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
	int textWidth = getTextWidth();
	int textHeight = getTextHeight();
	bmp = BMP_Create(max(w, textWidth), max(h, textHeight), 24);
	if (bmp == NULL)
		Serial.println("Bitmap allocation failed");
}

void StripDisplay::fillBitmap(unsigned int x0, unsigned int y0, unsigned int dx, unsigned int dy, CRGB crgb) {
	for (unsigned int x=x0; x<x0+dx; x++)
		for (unsigned int y=y0; y<y0+dy; y++)
			BMP_SetPixelRGB(bmp, x, y, crgb.r, crgb.g, crgb.b);
}

void StripDisplay::blitBitmap(int i0, int ox, int oy, int dx, int dy, int wrap) {
	int i=i0, ix, iy;
	int width = min((int)BMP_GetWidth(bmp),ox+dx);
	int height = min((int)BMP_GetHeight(bmp),oy+dy);
	byte r,g,b;
	if (wrap == WRAP_LINES) {
		for (int y=0; y<dy; y++) {
			iy = y+oy;
			for (int x=0; x<dx;x++) {
				ix = x+ox;
				if (ix>=0 && iy>=0 && ix<width && iy<height) {
					BMP_GetPixelRGB(bmp,ix,iy,&r,&g,&b);
					if (y%2 == 0) 
						leds[i] = CRGB(r, g, b);		   
					else 
						leds[dx*(int)(i/dx) + dx - ((i%dx) + 1)] = CRGB(r, g, b);		   
				}
				++i;
			}
		}
	}
	else {
		for (int x=0; x<dx;x++) {
			ix = x+ox;
			for (int y=0; y<dy; y++) {
				iy = y+oy;
				if (ix>=0 && iy>=0 && ix<width && iy<height) {
					BMP_GetPixelRGB(bmp,ix,iy,&r,&g,&b);
					if (x%2 == 0) 
						leds[i] = CRGB(r, g, b);		   
					else 
						leds[dy*(int)(i/dy) + dy - ((i%dy) + 1)] = CRGB(r, g, b);		   
				}
				++i;
			}
		}
	}
}

CRGB StripDisplay::getPixel(unsigned int x, unsigned int y) {
	CRGB crgb;
	BMP_GetPixelRGB(bmp, x, y, &crgb.r, &crgb.g, &crgb.b);
	return crgb;
}

void StripDisplay::setPixel(unsigned int x, unsigned int y, CRGB crgb) {
	BMP_SetPixelRGB(bmp, x, y, crgb.r, crgb.g, crgb.b);
}

void StripDisplay::displayBitmap() {
	for (int i=0; i<nPanels; i++)
		blitBitmap(panels[i].ledIndex, panels[i].bmpX, panels[i].bmpY, panels[i].w, panels[i].h, panels[i].wrap);
}


void StripDisplay::renderText(unsigned int x0, unsigned int y0, CRGB crgb) {
	unsigned int x = x0;
	for (int i=0; i<text.length(); i++) {
		char c = text.charAt(i);
		// UTF-8 - ISO8859-1 mapping
		if (c == 195 && i+1<text.length() && text.charAt(i+1) > 95 && text.charAt(i+1) < 192)
			c = text.charAt(++i) + 64;
		else if (c == 194 && i+1<text.length() && text.charAt(i+1) > 160)
			c = text.charAt(++i);
		for (int j=0; j<fontP->getWidth(); j++) { 
			for (int k=0; k<fontP->getHeight(); k++)
				if (fontP->getPixel(c,k,j))
					BMP_SetPixelRGB(bmp, x+j, y0+k, crgb.r, crgb.g, crgb.b);
		}
		x += fontP->getWidth();
	}
}

void StripDisplay::displayText(int offset) {
	int x0 = 0;
	int textWidth = getTextWidth();
	int textHeight = getTextHeight();
	int width = min(w, textWidth);
	int height = min(h, textHeight);
	if (textWidth <= w) {
		if (align == ALIGN_CENTER)
			x0 = (w-width)/2;
		else if (align == ALIGN_RIGHT)
			x0 = (w-width);
	}
	fillBitmap(0, 0, (int)BMP_GetWidth(bmp), (int)BMP_GetHeight(bmp), bg);
	displayBitmap();
	renderText(x0 - offset, 0, fg);
	displayBitmap();
}



int StripDisplay::getTextWidth() {
	return text.length() * fontP->getWidth();
}

int StripDisplay::getTextHeight() {
	return fontP->getHeight();
}

