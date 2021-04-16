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


#ifdef FONT_4x6_FIXED_MEDIUM
#undef FONT_4x6_FIXED_MEDIUM
#include "4x6-ISO8859-1.xbm"
XBMFont fixedMedium_4x6(4,6,font_FixedMedium_4x6);
#endif

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

#ifdef FONT_5x8_FIXED_MEDIUM
#undef FONT_5x8_FIXED_MEDIUM
#include "5x8-ISO8859-1.xbm"
XBMFont fixedMedium_5x8(5,8,font_FixedMedium_5x8);
#endif

#ifdef FONT_6x8_FIXED_MEDIUM
#undef FONT_6x8_FIXED_MEDIUM
#include "6x8-ISO8859-1.xbm"
XBMFont fixedMedium_6x8(6,8,font_FixedMedium_6x8);
#endif

#ifdef FONT_6x9_FIXED_MEDIUM
#undef FONT_6x9_FIXED_MEDIUM
#include "6x9-ISO8859-1.xbm"
XBMFont fixedMedium_6x9(6,9,font_FixedMedium_6x9);
#endif

#ifdef FONT_6x10_FIXED_MEDIUM
#undef FONT_6x10_FIXED_MEDIUM
#include "6x10-ISO8859-1.xbm"
XBMFont fixedMedium_6x10(6,10,font_FixedMedium_6x10);
#endif

#ifdef FONT_6x12_FIXED_MEDIUM
#undef FONT_6x12_FIXED_MEDIUM
#include "6x12-ISO8859-1.xbm"
XBMFont fixedMedium_6x12(6,12,font_FixedMedium_6x12);
#endif

#ifdef FONT_6x13_FIXED_MEDIUM
#undef FONT_6x13_FIXED_MEDIUM
#include "6x13-ISO8859-1.xbm"
XBMFont fixedMedium_6x13(6,13,font_FixedMedium_6x13);
#endif

#ifdef FONT_7x13_FIXED_BOLD
#undef FONT_7x13_FIXED_BOLD
#include "7x13B-ISO8859-1.xbm"
XBMFont fixedBold_7x13(7,13,font_FixedBold_7x13);
#endif

#ifdef FONT_8x13_FIXED_MEDIUM
#undef FONT_8x13_FIXED_MEDIUM
#include "8x13-ISO8859-1.xbm"
XBMFont fixedMedium_8x13(8,13,font_FixedMedium_8x13);
#endif

#ifdef FONT_8x13_FIXED_BOLD
#undef FONT_8x13_FIXED_BOLD
#include "8x13B-ISO8859-1.xbm"
XBMFont fixedBold_8x13(8,13,font_FixedBold_8x13);
#endif


#endif
