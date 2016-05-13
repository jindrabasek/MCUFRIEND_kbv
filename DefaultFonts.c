// DO NOT ADD YOUR OWN FONTS TO THIS FILE
// If you want to use your own/downloaded fonts you should just drop the font .c file into your sketch folder.
// -----------------------------------------------------------------------------------------------------------

#if defined(__AVR__)
	#include <avr/pgmspace.h>
	#define fontdatatype const uint8_t
#elif defined(__PIC32MX__)
	#define PROGMEM
	#define fontdatatype const unsigned char
#elif defined(__arm__)
	#define PROGMEM
	#define fontdatatype const unsigned char
#endif

// SmallFont.c 
// Font Size	: 8x12
// Memory usage	: 1144 bytes
// # characters	: 95

// FreeSansBold12pt7b

fontdatatype SmallFont[1] PROGMEM={1};

// BigFont.c (C)2010 by Henning Karlsen
// Font Size	: 16x16
// Memory usage	: 3044 bytes
// # characters	: 95

// FreeSansBold18pt7b

fontdatatype BigFont[1] PROGMEM={2};

// SevenSegNumFont.c
// Font Size	: 32x50
// Memory usage	: 2004 bytes
// # characters	: 10

//FreeMonoBoldOblique24pt7b

fontdatatype SevenSegNumFont[1] PROGMEM={4};
