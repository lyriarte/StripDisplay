#include "XBMFont.h"


XBMFont::XBMFont(unsigned int width, unsigned int height, unsigned char ** chars) {
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


unsigned char * XBMFont::getBitmap(char c) {
	unsigned int i = (unsigned int) c;
	if (i >= 32 && i <= 127)
		return this->chars[i - 32]; // [0..95]
	if (i >= 224 && i <= 255)
		return this->chars[i - 128]; // [96..127]
	// Ad-hoc mappings for charcodes > 127
	if (i >= 192 && i <= 198) return this->chars[33]; // 'A' - 32
	if (i >= 200 && i <= 203) return this->chars[37]; // 'E' - 32
	if (i >= 204 && i <= 207) return this->chars[41]; // 'I' - 32
	if (i >= 210 && i <= 214) return this->chars[47]; // 'O' - 32
	if (i >= 217 && i <= 222) return this->chars[53]; // 'U' - 32
	if (i == 171 || i == 187) return this->chars[02]; // '"' - 32
	return this->chars[95]; // 127-32
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



