#include "StripDisplay.h"

StripDisplay::StripDisplay(int w, int h, int wrap, int origin, CRGB *leds) {
	this->initPanel(GPIO_NONE, w, h, wrap, origin, leds);
}

StripDisplay::StripDisplay(int gpio, int w, int h, int wrap, int origin, CRGB *leds) {
	this->initPanel(gpio, w, h, wrap, origin, leds);
}

StripDisplay::StripDisplay(int w, int h, CRGB *leds, StripLEDPanel *panels, int nPanels) {
	this->init(GPIO_NONE, w, h, leds, panels, nPanels);
}

StripDisplay::StripDisplay(int gpio, int w, int h, CRGB *leds, StripLEDPanel *panels, int nPanels) {
	this->init(gpio, w, h, leds, panels, nPanels);
}

void StripDisplay::initPanel(int gpio, int w, int h, int wrap, int origin, CRGB *leds) {
	StripLEDPanel *panelP = (StripLEDPanel *) malloc(sizeof(StripLEDPanel));
	panelP->ledIndex = 0;
	panelP->bmpX = 0;
	panelP->bmpY = 0;
	panelP->w = w;
	panelP->h = h;
	panelP->wrap = wrap;
	panelP->origin = origin;
	this->init(gpio, w, h, leds, panelP, 1);
}

void StripDisplay::init(int gpio, int w, int h, CRGB *leds, StripLEDPanel *panels, int nPanels) {
	this->gpio = gpio;
	this->w = w;
	this->h = h; 
	this->leds = leds;
	this->panels = panels;
	this->nPanels = nPanels;
	bmp = NULL;
	fontP = NULL;
	align = ALIGN_LEFT;
	line = 0;
	bg = CRGB(0,0,0);
	fg = CRGB(1,1,1);
	newBitmap();
}

void StripDisplay::setup(XBMFont* fontP) {
	setFont(fontP);
        if (gpio != GPIO_NONE)
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
}

void StripDisplay::setText(String text) {
	this->text = text;
}

void StripDisplay::setAlignment(int align) {
	this->align = align;
}

void StripDisplay::setLine(int line) {
	this->line = line;
}

void StripDisplay::setBgColor(CRGB bg) {
	this->bg = bg;
}

void StripDisplay::setFgColor(CRGB fg) {
	this->fg = fg;
}



void StripDisplay::newBitmap() {
	if (bmp != NULL)
		BMP_Free(bmp);
	bmp = BMP_Create(w, h, 24);
	if (bmp == NULL)
		Serial.println("Display bitmap allocation failed");
}

void StripDisplay::fillBitmap(unsigned int x0, unsigned int y0, unsigned int dx, unsigned int dy, CRGB crgb) {
	for (unsigned int x=x0; x<x0+dx; x++)
		for (unsigned int y=y0; y<y0+dy; y++)
			BMP_SetPixelRGB(bmp, x, y, crgb.r, crgb.g, crgb.b);
}

void StripDisplay::blitBitmap(int i0, int ox, int oy, int dx, int dy, int wrap, int origin) {
	int i=i0, ix, iy, incx, incy;
	int width = min((int)BMP_GetWidth(bmp),ox+dx);
	int height = min((int)BMP_GetHeight(bmp),oy+dy);
	byte r,g,b;
	switch (origin) {
		case ORIGIN_TOP_RIGHT:
			incx = -1;
			incy = 1;
			ox += dx-1;
		break;
		case ORIGIN_BOTTOM_RIGHT:
			incx = incy = -1;
			ox += dx-1;
			oy += dy-1;
		break;
		case ORIGIN_BOTTOM_LEFT:
			incx = 1;
			incy = -1;
			oy += dy-1;
		break;
		case ORIGIN_TOP_LEFT:
		default:
			incx = incy = 1;
	}
	if (wrap == WRAP_LINES) {
		for (int y=0; y<dy; y++) {
			iy = y*incy+oy;
			for (int x=0; x<dx;x++) {
				ix = x*incx+ox;
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
			ix = x*incx+ox;
			for (int y=0; y<dy; y++) {
				iy = y*incy+oy;
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
		blitBitmap(panels[i].ledIndex, panels[i].bmpX, panels[i].bmpY, panels[i].w, panels[i].h, panels[i].wrap, panels[i].origin);
}


void StripDisplay::renderXpm(int x0, int y0, int w, int h, unsigned char * charBytes, CRGB crgb) {
	int byteWidth = w/8;
	for (int i=0; i<h; i++) {
		int y=y0+i;
		for (int j=0; j<byteWidth; j++) {
			unsigned char bits = charBytes[i*byteWidth+j];
			int byteX = x0+j*8;
			for (int k=0; k<8; k++) {
				if (bits & (1 << k))
					BMP_SetPixelRGB(bmp, byteX+k, y, crgb.r, crgb.g, crgb.b);
			}
		}
	}
}


void StripDisplay::renderText(int x0, int y0, CRGB crgb) {
	int x = x0;
	if (fontP == NULL)
		return;
	int fontW = (int) fontP->getWidth();
	int fontH = (int) fontP->getHeight();
	int textLength = text.length();
	for (int i=0; i<textLength && x<w; i++) {
		if (x > -fontW) {
			char c = text.charAt(i);
			// UTF-8 - ISO8859-1 mapping
			if (c == 195 && i+1<textLength && text.charAt(i+1) > 95 && text.charAt(i+1) < 192)
				c = text.charAt(++i) + 64;
			else if (c == 194 && i+1<textLength && text.charAt(i+1) > 160)
				c = text.charAt(++i);
			unsigned char * charBytes = fontP->getBitmap(c);
			for (int k=0; k<fontH; k++) { 
				unsigned char lineByte = charBytes[k];
				for (int j=0; j<fontW; j++)
					if (lineByte & (1 << j)) // fontP->getPixel(c,k,j)
						BMP_SetPixelRGB(bmp, x+j, y0+k, crgb.r, crgb.g, crgb.b);
			}
		}
		x += fontW;
	}
}

void StripDisplay::displayText(int offset, bool fillBg) {
	int x0 = 0;
	int textWidth = getTextWidth();
	if (textWidth <= w) {
		if (align == ALIGN_CENTER)
			x0 = (w-textWidth)/2;
		else if (align == ALIGN_RIGHT)
			x0 = (w-textWidth);
	}
	if (fillBg) {
		fillBitmap(0, 0, w, h, bg);
		displayBitmap();
	}
	renderText(x0 - offset, line, fg);
	displayBitmap();
}



int StripDisplay::getTextWidth() {
	if (fontP == NULL)
		return 0;
	return text.length() * fontP->getWidth();
}

int StripDisplay::getTextHeight() {
	if (fontP == NULL)
		return 0;
	return fontP->getHeight();
}

