/*
 * UTFT.h
 *
 * Created: 02/03/2013 14:25:06
 *  Author: David Prentice
 */ 


#ifndef UTFT_H_
#define UTFT_H_

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define PORTRAIT 0
#define LANDSCAPE 1

//*********************************
// COLORS
//*********************************
// VGA color palette
#define VGA_BLACK       0x0000
#define VGA_WHITE       0xFFFF
#define VGA_RED         0xF800
#define VGA_GREEN       0x0400
#define VGA_BLUE        0x001F
#define VGA_SILVER      0xC618
#define VGA_GRAY        0x8410
#define VGA_MAROON      0x8000
#define VGA_YELLOW      0xFFE0
#define VGA_OLIVE       0x8400
#define VGA_LIME        0x07E0
#define VGA_AQUA        0x07FF
#define VGA_TEAL        0x0410
#define VGA_NAVY        0x0010
#define VGA_FUCHSIA     0xF81F
#define VGA_PURPLE      0x8010
#define VGA_TRANSPARENT 0xFFFFFFFF

#include <MCUFRIEND_kbv.h>

struct _current_font
{
	//uint8_t* font;
	uint8_t x_size;
	uint8_t y_size;
	//uint8_t offset;
	//uint8_t numchars;
};

class UTFT : public MCUFRIEND_kbv
{
	public:
//	UTFT() : MCUFRIEND_kbv() {}
	UTFT(byte model, int RS, int WR,int CS, int RST, int RD = A0) : MCUFRIEND_kbv(CS, RS, WR, RD, RST) {}
	void InitLCD(byte orientation=LANDSCAPE) {
	     MCUFRIEND_kbv::reset();
		 uint16_t ID = MCUFRIEND_kbv::readID();
		 if (ID == 0) ID = 0x9341;        //DealExtreme with EXTC=0
//		 if (ID == 0x0089 || ID == 0x8989) ID = 0x1289;
		 if (ID == 0x00D3 || ID == 0xD3D3) ID = 0x9481;   //write-only controller
//		 if (ID == 0x00D3 || ID == 0xD3D3) ID = 0x9486;   //write-only controller
//         if (ID == 0x9327 && orientation == LANDSCAPE) orientation = 3;
		 MCUFRIEND_kbv::begin(ID);
		 MCUFRIEND_kbv::setRotation(orient = orientation);
		 _radius = 4;
		 disp_x_size = MCUFRIEND_kbv::width() - 1;
		 disp_y_size = MCUFRIEND_kbv::height() - 1;
		 cfont.x_size = 6;
		 cfont.y_size = 8;
    }
	void clrScr() { MCUFRIEND_kbv::fillScreen(0x0000);}
	void drawPixel(int x, int y) { MCUFRIEND_kbv::drawPixel(x, y, _fcolor);}
	void drawLine(int x1, int y1, int x2, int y2) { MCUFRIEND_kbv::drawLine(x1, y1, x2, y2, _fcolor);}
	void drawHLine(int x, int y, int l) { MCUFRIEND_kbv::drawFastHLine(x, y, l, _fcolor);}
	void fillScr(byte r, byte g, byte b) { MCUFRIEND_kbv::fillScreen(setrgb(r, g, b));}
	void drawRect(int x1, int y1, int x2, int y2) {
		 int w = x2 - x1 + 1, h = y2 - y1 + 1;
	     if (w < 0) { x1 = x2; w = -w; }
         if (h < 0) { y1 = y2; h = -h; }
         MCUFRIEND_kbv::drawRect(x1, y1, w, h, _fcolor);
    }
	void drawRoundRect(int x1, int y1, int x2, int y2) {
		 int w = x2 - x1 + 1, h = y2 - y1 + 1;
	     if (w < 0) { x1 = x2; w = -w; }
         if (h < 0) { y1 = y2; h = -h; }
         MCUFRIEND_kbv::drawRoundRect(x1, y1, w, h, _radius, _fcolor);
    }
	void fillRect(int x1, int y1, int x2, int y2) {
		 int w = x2 - x1 + 1, h = y2 - y1 + 1;
    	 if (w < 0) { x1 = x2; w = -w; }
		 if (h < 0) { y1 = y2; h = -h; }
         MCUFRIEND_kbv::fillRect(x1, y1, w, h, _fcolor);
    }
	void fillRoundRect(int x1, int y1, int x2, int y2) {
		 int w = x2 - x1 + 1, h = y2 - y1 + 1;
	     if (w < 0) { x1 = x2; w = -w; }
         if (h < 0) { y1 = y2; h = -h; }
         MCUFRIEND_kbv::fillRoundRect(x1, y1, w, h, _radius, _fcolor);
    }
	void drawCircle(int x, int y, int radius) { MCUFRIEND_kbv::drawCircle(x, y, radius, _fcolor);}
	void fillCircle(int x, int y, int radius) { MCUFRIEND_kbv::fillCircle(x, y, radius, _fcolor);}
	void setColor(byte r, byte g, byte b)  { MCUFRIEND_kbv::setTextColor(_fcolor = setrgb(r, g, b), _bcolor);}
	void setBackColor(byte r, byte g, byte b)  { MCUFRIEND_kbv::setTextColor(_fcolor, _bcolor = setrgb(r, g, b));}


	void setColor(word color)
	{
	    MCUFRIEND_kbv::setTextColor(_fcolor = color, _bcolor);
	}

	void setBackColor(uint32_t color)
	{
	    /*if (color==VGA_TRANSPARENT)
	        _transparent=true;
	    else
	    {*/
	    MCUFRIEND_kbv::setTextColor(_fcolor, _bcolor = color);
	       /* _transparent=false;
	    }*/
	}

	void print(const char *st, int x, int y, int deg=0)  {
		 settextcursor((char*)st, x, y); MCUFRIEND_kbv::print(st);}
	void print(char *st, int x, int y, int deg=0)  {
		 settextcursor(st, x, y); MCUFRIEND_kbv::print(st);}
	void print(String st, int x, int y, int deg=0) { settextcursorLen(st.length(), x, y);
		 MCUFRIEND_kbv::print(st);}
	void printChar(byte c, int x, int y) { settextcursorLen(1, x, y); MCUFRIEND_kbv::print(c); }
	void printNumI(long num, int x, int y, int length=0, char filler=' ') {
		 char buf[16]; ltoa(num, buf, 10); 
		 settextcursor(buf, x, y); MCUFRIEND_kbv::print(buf);}
	void printNumF(double num, byte dec, int x, int y, char divider='.', int length=0, char filler=' ') {
		 settextcursor((char*)"", x, y); MCUFRIEND_kbv::print(num, dec);}
	void setFont(uint8_t* font) {
	    uint8_t fontSize = pgm_read_byte(&font[0]);
	    MCUFRIEND_kbv::setTextSize(fontSize);
        cfont.x_size = 6*fontSize;
        cfont.y_size = 8*fontSize;
	}

	void drawBitmap(int x, int y, int sx, int sy, uint16_t *data, int scale=1) {
		 uint16_t color;
		 MCUFRIEND_kbv::setAddrWindow(x, y, x + sx*scale - 1, y + sy*scale - 1);
		 if (scale == 1) MCUFRIEND_kbv::pushColors((const uint8_t*)data, sx * sy, 1);
		 else {
		     for (int row = 0; row < sy; row++) {
			     for (int col = 0; col < sx; col++) {
                     color = pgm_read_word(data + (row*sx + col)*1);
					 MCUFRIEND_kbv::fillRect(x+col*scale, y+row*scale, scale, scale, color);
			     }
		     }
		 }
		 }
//	void drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy);
//	void lcdOff();
//	void lcdOn();
//	void setContrast(char c);

	int getDisplayXSize()
	{
	    if (orient==PORTRAIT)
	        return disp_x_size+1;
	    else
	        return disp_y_size+1;
	}

	int getDisplayYSize()
	{
	    if (orient==PORTRAIT)
	        return disp_y_size+1;
	    else
	        return disp_x_size+1;
	}

//	void LCD_Write_DATA(char VH,char VL);
	//		void dispBitmap(File inFile);

    uint8_t orient;
    int disp_x_size, disp_y_size;
    _current_font   cfont;

	protected:
	uint16_t _fcolor;
	uint16_t _bcolor;
	uint8_t _radius;


    void settextcursor(char *st, int x, int y) {
		int pos;
		if (x == CENTER || x == RIGHT) {
			pos = (MCUFRIEND_kbv::width() - strlen(st) * 6);
			if (x == CENTER) x = pos/2;
			else x = pos;
		}			
        MCUFRIEND_kbv::setCursor(x, y);
	}
    void settextcursorLen(unsigned int strLen, int x, int y) {
        int pos;
        if (x == CENTER || x == RIGHT) {
            pos = (MCUFRIEND_kbv::width() - strLen * 6);
            if (x == CENTER) x = pos/2;
            else x = pos;
        }
        MCUFRIEND_kbv::setCursor(x, y);
    }
    uint16_t setrgb(byte r, byte g, byte b)  { return ((r&0xF8) << 8) | ((g&0xFC) << 3) | (b>>3);}
};

#endif /* UTFT_H_ */
