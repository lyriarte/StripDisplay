#ifndef XBMFont_H
#define XBMFont_H

class XBMFont {

	public:
	XBMFont(unsigned int width, unsigned int height, unsigned char * chars);
	unsigned int getWidth();
	unsigned int getHeight();
	unsigned char * getBitmap(char c);
	unsigned char getLine(char c, unsigned int line);
	bool getPixel(char c, unsigned int line, unsigned int column);

	private:
	unsigned char * charAt(int index);

	unsigned int width;
	unsigned int height;
	unsigned char * chars; 
};


#ifdef FONT_5x6_FIXED_MEDIUM
#undef FONT_5x6_FIXED_MEDIUM
#include "5x6-ISO8859-1.xbm"
XBMFont fixedMedium_5x6(5,6,font_FixedMedium_5x6);
#endif

#ifdef FONT_5x7_FIXED_MEDIUM
#undef FONT_5x7_FIXED_MEDIUM
#include "5x7-ISO8859-1.xbm"
XBMFont fixedMedium_5x7(5,7,font_FixedMedium_5x7);
#endif


#endif
