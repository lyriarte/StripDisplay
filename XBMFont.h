#ifndef XBMFont_H
#define XBMFont_H

class XBMFont {

	public:
	XBMFont(unsigned int width, unsigned int height, unsigned char ** chars);
	unsigned int getWidth();
	unsigned int getHeight();
	unsigned char * getBitmap(char c);
	unsigned char getLine(char c, unsigned int line);
	bool getPixel(char c, unsigned int line, unsigned int column);

	private:
	unsigned int width;
	unsigned int height;
	unsigned char ** chars; 
};


#endif
