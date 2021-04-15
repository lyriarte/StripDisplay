#include "XBMFont.h"


XBMFont::XBMFont(unsigned int width, unsigned int height, unsigned char * chars) {
	this->width = width;
	this->height = height;
	this->chars = chars; 
}


unsigned int XBMFont::getWidth() {
	return this->width;
}


unsigned int XBMFont::getHeight() {
	return this->height;
}

unsigned char * XBMFont::charAt(int index) {
	return this->chars + this->height * index;
}

unsigned char * XBMFont::getBitmap(char c) {
	unsigned int i = (unsigned int) c;
	if (i < 128)
		return this->charAt(i);
	if (i > 127 && i < 160)
		return this->charAt(127); // non printable
	return this->charAt(i-32);
}


unsigned char XBMFont::getLine(char c, unsigned int line) {
	if (line >= this->height)
		line = this->height -1;
	return this->getBitmap(c)[line];
}


bool XBMFont::getPixel(char c, unsigned int line, unsigned int column) {
	if (column >= this->width)
		column = 0;
	unsigned char bits = this->getLine(c,line);
	return bits & (1 << column);
}



