/**
 * GUI library for "mac/μac"
 * Author: Peter "Projectitis" Vullings <peter@projectitis.com>
 * Distributed under the MIT licence
 **/
 
#include "Bitmap.h"

/**
 * This file is part of the mac (or μac) "Microprocessor App Creator" library.
 * mac is a project that enables creating beautiful and useful apps on the
 * Teensy microprocessor, but hopefully is generic enough to be ported to other
 * microprocessor boards. The various libraries that make up mac might also
 * be useful in other projects.
 **/
namespace mac{


	/**
	 * Check whether a pixel format includes an alpha channel or not
	 * @param  pixelFormat The pixel format to check
	 * @return             Return true if the pixel format has an alpha channel, otherwise false
	 */
	boolean pixelFormatHasAlpha( PixelFormat pixelFormat ){
		switch (pixelFormat){
			case mac::PF_4444: return true;
			case mac::PF_6666: return true;
			case mac::PF_8565: return true;
			case mac::PF_8888: return true;
			default: return false;
		}
	}

	/**
	 * Return the width, in bytes, of a pixel stored in this format
	 * @param  pixelFormat The pixel format to check
	 * @return             The width in number of bytes
	 */
	uint8_t pixelFormatByteWidth( PixelFormat pixelFormat ){
		switch (pixelFormat){
			case mac::PF_565: return 2;
			case mac::PF_4444: return 2;
			case mac::PF_6666: return 3;
			case mac::PF_8565: return 3;
			case mac::PF_888: return 3;
			case mac::PF_8888: return 4;
			case mac::PF_GRAYSCALE: return 1;
			case mac::PF_MONO: return 0;
			case mac::PF_INDEXED: return 1;
			case mac::PF_UNKNOWN: return 0;
			default: return 0;
		}
	}
	
	/**
	 *  ######   #####  ######
	 *  ##      ##      ##
	 *  #####   #####   #####
	 *      ##  ##  ##      ##
	 *  #####    ####   #####
	 */
	
	/*
	 * ### BITMAP ACCESS
	 */

	/**
	 * The following functions get a pixel from a bitmap and convert to RGB565 and 5-bit alpha.
	 * Use these functions if you are using the fast alpha-blending function below that requires
	 * 5-bit alpha (0-31). If you are using libraries that require 8-bit alpha, use the ...as8565
	 * functions instead.
	 */
	void get565as5565( uint8_t* p, uint16_t& c, uint8_t& a ){
		c = (p[0] << 8) | p[1];
	}
	void get4444as5565( uint8_t* p, uint16_t& c, uint8_t& a ){
		a = ((p[0] >> 3) & 0b11110) | ((p[0] >> 7) & 0b1); // 5-bit alpha
		c = ((p[0] & 0b1111) << 12) | ((p[0] & 0b1000) << 8)
			| ((p[1] & 0b11110000) << 3) | ((p[1] & 0b11000000) >> 1)
			| ((p[1] & 0b1111) << 1) | ((p[1] & 0b1000) >> 3);
	}
	void get6666as5565( uint8_t* p, uint16_t& c, uint8_t& a ){
		a = (p[0] >> 3); // 5-bit alpha
		c = (p[0] << 14) | ((p[1] << 6) & 0b0011100000000000) | ((p[1] << 7) & 0b0000011110000000) | ((p[1] >> 1) & 0b0000000001111111);
	}
	void get8565as5565( uint8_t* p, uint16_t& c, uint8_t& a ){
		a = (p[0] >> 3); // 8-bit to 5-bit alpha
		c = (p[1] << 8) | p[2];
	}
	void get888as5565( uint8_t* p, uint16_t& c, uint8_t& a ){
		c = ((p[0] & 0b11111000) << 8) | ((p[1] & 0b11111100) << 3) | ((p[1] & 0b11111000) >> 3);
	}
	void get8888as5565( uint8_t* p, uint16_t& c, uint8_t& a ){
		a = (p[0] >> 3); // 8-bit to 5-bit alpha
		c = ((p[1] & 0b11111000) << 8) | ((p[2] & 0b11111100) << 3) | ((p[3] & 0b11111000) >> 3);
	}
	void get8as5565( uint8_t* p, uint16_t& c, uint8_t& a ){
		c = ((p[0] & 0xF8) << 8) | ((p[0] & 0xFC) << 3) | ((p[0] & 0xF8) >> 3);
	}
	void get1as5565( uint8_t* p, uint16_t& c, uint8_t& a ){
		// Hijack 'a' as bit index (0-7 from left to right)
		c = ((p[0] >> (7-a)) & 0b1)?RGB565_White:RGB565_Black;
	}

	/**
	 * Use getAccessor5565 on a tilemap to choose the correct data access function.
	 */
	access5565 getAccessor5565( PixelFormat pixelFormat ){
		switch (pixelFormat){
			case mac::PF_565: return get565as5565;
			case mac::PF_4444: return get4444as5565;
			case mac::PF_6666: return get6666as5565;
			case mac::PF_8565: return get8565as5565;
			case mac::PF_888: return get888as5565;
			case mac::PF_8888: return get8888as5565;
			case mac::PF_GRAYSCALE: return get8as5565;
			case mac::PF_MONO: return get1as5565;
			case mac::PF_INDEXED: return 0;	// XXX: Handle indexed colors
			case mac::PF_UNKNOWN: return 0;	
		}
		return 0;
	}

	/**
	 * The following functions get a pixel from a bitmap and convert to RGB565 and 8-bit alpha.
	 */
	void get565as8565( uint8_t* p, uint16_t& c, uint8_t& a ){
		c = (p[0] << 8) | p[1];
	}
	void get4444as8565( uint8_t* p, uint16_t& c, uint8_t& a ){
		a = (p[0] & 0b11110000) | (p[0] >> 4); // 8-bit alpha
		c = ((p[0] & 0b1111) << 12) | ((p[0] & 0b1000) << 8)
			| ((p[1] & 0b11110000) << 3) | ((p[1] & 0b11000000) >> 1)
			| ((p[1] & 0b1111) << 1) | ((p[1] & 0b1000) >> 3);
	}
	void get6666as8565( uint8_t* p, uint16_t& c, uint8_t& a ){
		a = (p[0] & 0b11111100) | ((p[0] >> 6) & 0b11);
		c = (p[0] << 14) | ((p[1] << 6) & 0b0011100000000000) | ((p[1] << 7) & 0b0000011110000000) | ((p[1] >> 1) & 0b0000000001111111);
	}
	void get8565as8565( uint8_t* p, uint16_t& c, uint8_t& a ){
		a = p[0]; // Already 8-bit alpha
		c = (p[1] << 8) | p[2];
	}
	void get888as8565( uint8_t* p, uint16_t& c, uint8_t& a ){
		c = ((p[0] & 0b11111000) << 8) | ((p[1] & 0b11111100) << 3) | ((p[1] & 0b11111000) >> 3);
	}
	void get8888as8565( uint8_t* p, uint16_t& c, uint8_t& a ){
		a = p[0]; // Already 8-bit alpha
		c = ((p[1] & 0b11111000) << 8) | ((p[2] & 0b11111100) << 3) | ((p[3] & 0b11111000) >> 3);
	}
	void get8as8565( uint8_t* p, uint16_t& c, uint8_t& a ){
		c = ((p[0] & 0xF8) << 8) | ((p[0] & 0xFC) << 3) | ((p[0] & 0xF8) >> 3);
	}
	void get1as8565( uint8_t* p, uint16_t& c, uint8_t& a ){
		// Hijack 'a' as bit index (0-7 from left to right)
		c = ((p[0] >> (7-a)) & 0b1)?RGB565_White:RGB565_Black;
	}

	/**
	 * Use getAccessor8565 on a tilemap to choose the correct data access function.
	 */
	access8565 getAccessor8565( PixelFormat pixelFormat ){
		switch (pixelFormat){
			case mac::PF_565: return get565as8565;
			case mac::PF_4444: return get4444as8565;
			case mac::PF_6666: return get6666as8565;
			case mac::PF_8565: return get8565as8565;
			case mac::PF_888: return get888as8565;
			case mac::PF_8888: return get8888as8565;
			case mac::PF_GRAYSCALE: return get8as8565;
			case mac::PF_MONO: return get1as8565;
			case mac::PF_INDEXED: return 0;	// XXX: Handle indexed colors
			case mac::PF_UNKNOWN: return 0;
		}
		return 0;
	}

	/**
	 *  #####    #####   #####
	 *  ##  ##  ##       ##  ##
	 *  #####   ##  ###  #####
	 *  ##  ##  ##   ##  ##  ##
	 *  ##  ##   ######  #####
	 */
	
	/*
	 * ### BITMAP ACCESS
	 */

	/**
	 * The following functions get a pixel from the bitmap and convert to 8-bit per channel A,R,G,B components.
	 */
	void get565asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b ){
		r = (p[0] & 0b11111000) |  ((p[0] & 0b11100000) >> 5);
		g = ((p[0] & 0b111) << 5) | ((p[1] & 0b11100000) >> 3) | ((p[0] & 0b11) >> 6);
		b = ((p[1] & 0b11111) << 3) | ((p[1] & 0b11100) >> 2);
	}
	void get4444asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b ){
		a = (p[0] & 0b11110000) | (p[0] >> 4);
		r = (p[0] << 4) | (p[0] & 0b1111);
		g = (p[1] & 0b11110000) | (p[1] >> 4);
		b = (p[1] << 4) | (p[1] & 0b1111);
	}
	void get6666asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b ){
		a = (p[0] & 0b11111100 ) | ((p[0] >> 6) & 0b11);
		r = ((p[0] << 6) & 0b11000000) | (p[0] & 0b11) | ((p[1]>>2) & 0b111100);
		g = ((p[1] << 4) & 0b11110000) | ((p[1] >> 2) & 0b11) | ((p[2]>>4) & 0b1100);
		b = ((p[2] << 2) & 0b11111100) | ((p[2] >> 4) & 0b11);
	}
	void get8565asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b ){
		a = p[0];
		r = (p[1] & 0b11111000) | ((p[1] >> 5) & 0b111);
		g = ((p[1] << 5) & 0b11100000) | ((p[1] >> 1) & 0b11) | ((p[2] >> 3) & 0b11100);
		b = ((p[2] << 3) & 0b11111000) | ((p[2] >> 2) & 0b111);
	}
	void get888asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b ){
		r = p[0];
		g = p[1];
		b = p[2];
	}
	void get8888asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b ){
		a = p[0];
		r = p[1];
		g = p[2];
		b = p[3];
	}
	void get8asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b ){
		r = p[0];
		g = p[0];
		b = p[0];
	}
	void get1asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b ){
		// Hijack 'a' as bit index (0-7 from left to right)
		r = g = b = ((p[0] >> (7-a)) & 0b1)?255:0;
	}

	/**
	 * Use getAccessorARGB on a tilemap to choose the correct data access function.
	 */
	typedef void (*accessARGB)( uint8_t*, uint8_t&, uint8_t&, uint8_t&, uint8_t& );
	accessARGB getAccessorARGB( PixelFormat pixelFormat ){
		switch (pixelFormat){
			case mac::PF_565: return get565asARGB;
			case mac::PF_4444: return get4444asARGB;
			case mac::PF_6666: return get6666asARGB;
			case mac::PF_8565: return get8565asARGB;
			case mac::PF_888: return get888asARGB;
			case mac::PF_8888: return get8888asARGB;
			case mac::PF_GRAYSCALE: return get8asARGB;
			case mac::PF_MONO: return get1asARGB;
			case mac::PF_INDEXED: return 0;	// XXX: Handle indexed colors
			case mac::PF_UNKNOWN: return 0;
		}
		return 0;
	}

	/**
	 *   #####    #####    #####
	 *  ##   ##  ##   ##  ##   ##
	 *   #####    #####    #####
	 *  ##   ##  ##   ##  ##   ##
	 *   #####    #####    #####
	 */
	
	/*
	 * ### BITMAP ACCESS
	 */

	/**
	 * The following functions get a pixel from the bitmap and convert to 32-bit ARGB value
	 */
	void get565as8888( uint8_t* p, uint32_t& c ){
		c = (255 << 24)
			| ((p[0] & 0b11111000) << 16) |  ((p[0] & 0b11100000) << 11) // R
			| ((p[0] & 0b111) << 13) | ((p[1] & 0b11100000) << 5) | ((p[0] & 0b11) << 2) // G
			| ((p[1] & 0b11111) << 3) | ((p[1] & 0b11100) >> 2); // B
	}
	void get4444as8888( uint8_t* p, uint32_t& c ){
		c = ((p[0] & 0b11110000) << 24) | (p[0] << 20) | ((p[0] & 0b1111) << 16) | ((p[1] & 0b11110000) << 8) | (p[1] << 4) | (p[1] & 0b1111);
	}
	void get6666as8888( uint8_t* p, uint32_t& c ){
		c = ((p[0] & 0b11111100 ) << 24) | ((p[0] & 0b11000000) << 18) // A
			| ((p[0] & 0b11) << 22) | ((p[0] & 0b11) << 16) | ((p[1] & 0b11110000) << 14) // R
			| ((p[1] & 0b1111) << 12) | ((p[1] & 0b1100) << 6) | ((p[2] & 0b11000000) << 4) // G
			| ((p[2] & 0b111111) << 2) | ((p[2] & 0b110000) >> 4); // B
	}
	void get8565as8888( uint8_t* p, uint32_t& c ){
		c = (p[0] << 24) // A
			| ((p[1] & 0b11111000) << 16) | ((p[1] & 0b11100000) << 11) // R
			| ((p[1] & 0b111) << 13) | ((p[1] & 0b110) << 7) | ((p[2] & 0b11100000) << 5) // G
			| ((p[2] << 3) & 0b11111000) | ((p[2] >> 2) & 0b111); // B
	}
	void get888as8888( uint8_t* p, uint32_t& c ){
		c = (255 << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
	}
	void get8888as8888( uint8_t* p, uint32_t& c ){
		c = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
	}
	void get8as8888( uint8_t* p, uint32_t& c ){
		c = (255 << 24) | (p[0] << 16) | (p[0] << 8) | p[0];
	}
	void get1as8888( uint8_t* p, uint32_t& c ){
		// Hijack 'c' as bit index (0-7 from left to right)
		c = ((p[0] >> (7-c)) & 0b1)?RGB888_White:RGB888_Black;
	}

	/**
	 * Use getAccessor8888 on a tilemap to choose the correct data access function.
	 */
	typedef void (*access8888)( uint8_t*, uint32_t& );
	access8888 getAccessor8888( PixelFormat pixelFormat ){
		switch (pixelFormat){
			case mac::PF_565: return get565as8888;
			case mac::PF_4444: return get4444as8888;
			case mac::PF_6666: return get6666as8888;
			case mac::PF_8565: return get8565as8888;
			case mac::PF_888: return get888as8888;
			case mac::PF_8888: return get8888as8888;
			case mac::PF_GRAYSCALE: return get8as8888;
			case mac::PF_MONO: return get1as8888;
			case mac::PF_INDEXED: return 0;	// XXX: Handle indexed colors
			case mac::PF_UNKNOWN: return 0;
		}
		return 0;
	}
	
} // ns
