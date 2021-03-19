#include "StripDisplay.h"

StripDisplay::StripDisplay(int gpio, int w, int h, int wrap, CRGB *leds) {
	this->gpio = gpio;
	this->w = w;
	this->h = h; 
	this->wrap = wrap;
	this->leds = leds;
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

