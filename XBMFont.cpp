#include "XBMFont.h"

#define BMP_STRIP_FLAG_0	0x01
#define BMP_STRIP_FLAG_96	0x02
#define BMP_STRIP_FLAG_160	0x04

XBMFont::XBMFont(unsigned int width, unsigned int height, unsigned char * chars, unsigned int bmp_strip_mask) {
	this->width = width;
	this->height = height;
	this->chars = chars; 
	this->bmp_strip_mask = bmp_strip_mask; 
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
	unsigned int j = i;
	// strip 0..31 ?
	if (bmp_strip_mask & BMP_STRIP_FLAG_0) {
		if (i < 32)
			return this->charAt(0);
		j -= 32;
	}
	if (i < 96)
		return this->charAt(j);
	// strip 96..127 ?
	if (bmp_strip_mask & BMP_STRIP_FLAG_96) {
		if (i < 128)
			return this->charAt(0);
		j -= 32;
	}
	if (i < 128)
		return this->charAt(j);
	// strip 128..159
	if (i < 160)
		return this->charAt(0);
	j -= 32;
	// strip 160..255 ?
	if (bmp_strip_mask & BMP_STRIP_FLAG_160)
		return this->charAt(0);
	return this->charAt(j);
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



