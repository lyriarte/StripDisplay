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

void StripDisplay::setup() {
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
}

void StripDisplay::setText(String text) {
	this->text = text;
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


