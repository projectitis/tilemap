/**
 * Bitmap, Tilemap and general color helper functions
 * Author: Peter "Projectitis" Vullings <peter@projectitis.com>
 * Distributed under the MIT licence
 *
 * MIT LICENCE
 * -----------
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */	

#pragma once
#ifndef _MAC_BITMAPH_
#define _MAC_BITMAPH_ 1

#include <Arduino.h>

/**
 * This file is part of the mac (or μac) "Microprocessor App Creator" library.
 * mac is a project that enables creating beautiful and useful apps on the
 * Teensy microprocessor, but hopefully is generic enough to be ported to other
 * microprocessor boards. The various libraries that make up mac might also
 * be useful in other projects.
 **/
namespace mac{
	/**
	 * Defines a color as a RGB565 16bit unsigned int
	 * RRRRRGGGGGGBBBBB
	 **/
	typedef uint16_t color565;

	/**
	 * Defines a color as a RGBA4444 16bit unsigned int
	 * aaaaRRRRGGGGBBBB
	 **/
	typedef uint16_t color4444;

	/**
	 * Defines a color as ARGB8565 24bit total, with 8-bit alpha and packed 16-bit RGB565
	 * ........aaaaaaaaRRRRRGGGGGGBBBBB
	 **/
	typedef uint32_t color8565;

	/**
	 * Defines a color as ARGB6666 24bit total, with 6-bit alpha and 6-bits per color
	 * ........aaaaaaRRRRRRGGGGGGBBBBBB
	 **/
	typedef uint32_t color6666;

	/**
	 * Defines a color as standard 24-bit RGB
	 * ........RRRRRRRRGGGGGGGGBBBBBBBB
	 **/
	typedef uint32_t color888;
	
	/**
	 * Defines a color as packed ARGB components
	 * aaaaaaaaRRRRRRRRGGGGGGGGBBBBBBBB
	 **/
	typedef uint32_t color8888;

	/**
	 * Defines a color as 8-bit grayscale
	 **/
	typedef uint8_t colorGray;
	
	/**
	 * Defines alpha as a float (0.0 to 1.0)
	 **/
	typedef float alpha;

	/*
	* RGB888 colors
	*/
	enum {
		RGB888_Transparent = 0xff00ff,
		RGB888_Pink = 0xffc0cb,
		RGB888_LightPink = 0xffb6c1,
		RGB888_HotPink = 0xff69b4,
		RGB888_DeepPink = 0xff1493,
		RGB888_PaleVioletRed = 0xdb7093,
		RGB888_MediumVioletRed = 0xc71585,
		RGB888_LightSalmon = 0xffa07a,
		RGB888_Salmon = 0xfa8072,
		RGB888_DarkSalmon = 0xe9967a,
		RGB888_LightCoral = 0xf08080,
		RGB888_IndianRed = 0xcd5c5c,
		RGB888_Crimson = 0xdc143c,
		RGB888_Firebrick = 0xb22222,
		RGB888_DarkRed = 0x8b0000,
		RGB888_Red = 0xff0000,
		RGB888_OrangeRed = 0xff4500,
		RGB888_Tomato = 0xff6347,
		RGB888_Coral = 0xff7f50,
		RGB888_DarkOrange = 0xff8c00,
		RGB888_Orange = 0xffa500,
		RGB888_Yellow = 0xffff00,
		RGB888_LightYellow = 0xffffe0,
		RGB888_LemonChiffon = 0xfffacd,
		RGB888_LightGoldenrodYellow = 0xfafad2,
		RGB888_PapayaWhip = 0xffefd5,
		RGB888_Moccasin = 0xffe4b5,
		RGB888_PeachPuff = 0xffdab9,
		RGB888_PaleGoldenrod = 0xeee8aa,
		RGB888_Khaki = 0xf0e68c,
		RGB888_DarkKhaki = 0xbdb76b,
		RGB888_Gold = 0xffd700,
		RGB888_Cornsilk = 0xfff8dc,
		RGB888_BlanchedAlmond = 0xffebcd,
		RGB888_Bisque = 0xffe4c4,
		RGB888_NavajoWhite = 0xffdead,
		RGB888_Wheat = 0xf5deb3,
		RGB888_Burlywood = 0xdeb887,
		RGB888_Tan = 0xd2b48c,
		RGB888_RosyBrown = 0xbc8f8f,
		RGB888_SandyBrown = 0xf4a460,
		RGB888_Goldenrod = 0xdaa520,
		RGB888_DarkGoldenrod = 0xb8860b,
		RGB888_Peru = 0xcd853f,
		RGB888_Chocolate = 0xd2691e,
		RGB888_SaddleBrown = 0x8b4513,
		RGB888_Sienna = 0xa0522d,
		RGB888_Brown = 0xa52a2a,
		RGB888_Maroon = 0x800000,
		RGB888_DarkOliveGreen = 0x556b2f,
		RGB888_Olive = 0x808000,
		RGB888_OliveDrab = 0x6b8e23,
		RGB888_YellowGreen = 0x9acd32,
		RGB888_LimeGreen = 0x32cd32,
		RGB888_Lime = 0x00ff00,
		RGB888_LawnGreen = 0x7cfc00,
		RGB888_Chartreuse = 0x7fff00,
		RGB888_GreenYellow = 0xadff2f,
		RGB888_SpringGreen = 0x00ff7f,
		RGB888_MediumSpringGreen = 0x00fa9a,
		RGB888_LightGreen = 0x90ee90,
		RGB888_PaleGreen = 0x98fb98,
		RGB888_DarkSeaGreen = 0x8fbc8f,
		RGB888_MediumAquamarine = 0x66cdaa,
		RGB888_MediumSeaGreen = 0x3cb371,
		RGB888_SeaGreen = 0x2e8b57,
		RGB888_ForestGreen = 0x228b22,
		RGB888_Green = 0x008000,
		RGB888_DarkGreen = 0x006400,
		RGB888_Aqua = 0x00ffff,
		RGB888_Cyan = 0x00ffff,
		RGB888_LightCyan = 0xe0ffff,
		RGB888_PaleTurquoise = 0xafeeee,
		RGB888_Aquamarine = 0x7fffd4,
		RGB888_Turquoise = 0x40e0d0,
		RGB888_MediumTurquoise = 0x48d1cc,
		RGB888_DarkTurquoise = 0x00ced1,
		RGB888_LightSeaGreen = 0x20b2aa,
		RGB888_CadetBlue = 0x5f9ea0,
		RGB888_DarkCyan = 0x008b8b,
		RGB888_Teal = 0x008080,
		RGB888_LightSteelBlue = 0xb0c4de,
		RGB888_PowderBlue = 0xb0e0e6,
		RGB888_LightBlue = 0xadd8e6,
		RGB888_SkyBlue = 0x87ceeb,
		RGB888_LightSkyBlue = 0x87cefa,
		RGB888_DeepSkyBlue = 0x00bfff,
		RGB888_DodgerBlue = 0x1e90ff,
		RGB888_CornflowerBlue = 0x6495ed,
		RGB888_SteelBlue = 0x4682b4,
		RGB888_RoyalBlue = 0x4169e1,
		RGB888_Blue = 0x0000ff,
		RGB888_MediumBlue = 0x0000cd,
		RGB888_DarkBlue = 0x00008b,
		RGB888_Navy = 0x000080,
		RGB888_MidnightBlue = 0x191970,
		RGB888_Lavender = 0xe6e6fa,
		RGB888_Thistle = 0xd8bfd8,
		RGB888_Plum = 0xdda0dd,
		RGB888_Violet = 0xee82ee,
		RGB888_Orchid = 0xda70d6,
		RGB888_Fuchsia = 0xff00ff,
		RGB888_Magenta = 0xff00ff,
		RGB888_MediumOrchid = 0xba55d3,
		RGB888_MediumPurple = 0x9370db,
		RGB888_BlueViolet = 0x8a2be2,
		RGB888_DarkViolet = 0x9400d3,
		RGB888_DarkOrchid = 0x9932cc,
		RGB888_DarkMagenta = 0x8b008b,
		RGB888_Purple = 0x800080,
		RGB888_Indigo = 0x4b0082,
		RGB888_DarkSlateBlue = 0x483d8b,
		RGB888_SlateBlue = 0x6a5acd,
		RGB888_MediumSlateBlue = 0x7b68ee,
		RGB888_White = 0xffffff,
		RGB888_Snow = 0xfffafa,
		RGB888_Honeydew = 0xf0fff0,
		RGB888_MintCream = 0xf5fffa,
		RGB888_Azure = 0xf0ffff,
		RGB888_AliceBlue = 0xf0f8ff,
		RGB888_GhostWhite = 0xf8f8ff,
		RGB888_WhiteSmoke = 0xf5f5f5,
		RGB888_Seashell = 0xfff5ee,
		RGB888_Beige = 0xf5f5dc,
		RGB888_OldLace = 0xfdf5e6,
		RGB888_FloralWhite = 0xfffaf0,
		RGB888_Ivory = 0xfffff0,
		RGB888_AntiqueWhite = 0xfaebd7,
		RGB888_Linen = 0xfaf0e6,
		RGB888_LavenderBlush = 0xfff0f5,
		RGB888_MistyRose = 0xffe4e1,
		RGB888_Gainsboro = 0xdcdcdc,
		RGB888_LightGray = 0xd3d3d3,
		RGB888_Silver = 0xc0c0c0,
		RGB888_DarkGray = 0xa9a9a9,
		RGB888_Gray = 0x808080,
		RGB888_DimGray = 0x696969,
		RGB888_LightSlateGray = 0x778899,
		RGB888_SlateGray = 0x708090,
		RGB888_DarkSlateGray = 0x2f4f4f,
		RGB888_Black = 0x000000
	};

	/*
	* RGB565 colors
	*/
	enum {
		RGB565_Transparent = 0xf81f,
		RGB565_Pink = 0xfe19,
		RGB565_LightPink = 0xfdb8,
		RGB565_HotPink = 0xfb56,
		RGB565_DeepPink = 0xf8b2,
		RGB565_PaleVioletRed = 0xdb92,
		RGB565_MediumVioletRed = 0xc0b0,
		RGB565_LightSalmon = 0xfd0f,
		RGB565_Salmon = 0xfc0e,
		RGB565_DarkSalmon = 0xecaf,
		RGB565_LightCoral = 0xf410,
		RGB565_IndianRed = 0xcaeb,
		RGB565_Crimson = 0xd8a7,
		RGB565_Firebrick = 0xb104,
		RGB565_DarkRed = 0x8800,
		RGB565_Red = 0xf800,
		RGB565_OrangeRed = 0xfa20,
		RGB565_Tomato = 0xfb08,
		RGB565_Coral = 0xfbea,
		RGB565_DarkOrange = 0xfc60,
		RGB565_Orange = 0xfd20,
		RGB565_Yellow = 0xffe0,
		RGB565_LightYellow = 0xfffc,
		RGB565_LemonChiffon = 0xffd9,
		RGB565_LightGoldenrodYellow = 0xffda,
		RGB565_PapayaWhip = 0xff7a,
		RGB565_Moccasin = 0xff36,
		RGB565_PeachPuff = 0xfed7,
		RGB565_PaleGoldenrod = 0xef55,
		RGB565_Khaki = 0xf731,
		RGB565_DarkKhaki = 0xbdad,
		RGB565_Gold = 0xfea0,
		RGB565_Cornsilk = 0xffdb,
		RGB565_BlanchedAlmond = 0xff59,
		RGB565_Bisque = 0xff38,
		RGB565_NavajoWhite = 0xfef5,
		RGB565_Wheat = 0xf6f6,
		RGB565_Burlywood = 0xddd0,
		RGB565_Tan = 0xd5b1,
		RGB565_RosyBrown = 0xbc71,
		RGB565_SandyBrown = 0xf52c,
		RGB565_Goldenrod = 0xdd24,
		RGB565_DarkGoldenrod = 0xbc21,
		RGB565_Peru = 0xcc27,
		RGB565_Chocolate = 0xd343,
		RGB565_SaddleBrown = 0x8a22,
		RGB565_Sienna = 0xa285,
		RGB565_Brown = 0xa145,
		RGB565_Maroon = 0x8000,
		RGB565_DarkOliveGreen = 0x5345,
		RGB565_Olive = 0x8400,
		RGB565_OliveDrab = 0x6c64,
		RGB565_YellowGreen = 0x9e66,
		RGB565_LimeGreen = 0x3666,
		RGB565_Lime = 0x07e0,
		RGB565_LawnGreen = 0x7fe0,
		RGB565_Chartreuse = 0x7fe0,
		RGB565_GreenYellow = 0xafe5,
		RGB565_SpringGreen = 0x07ef,
		RGB565_MediumSpringGreen = 0x07d3,
		RGB565_LightGreen = 0x9772,
		RGB565_PaleGreen = 0x9fd3,
		RGB565_DarkSeaGreen = 0x8df1,
		RGB565_MediumAquamarine = 0x6675,
		RGB565_MediumSeaGreen = 0x3d8e,
		RGB565_SeaGreen = 0x2c4a,
		RGB565_ForestGreen = 0x2444,
		RGB565_Green = 0x0400,
		RGB565_DarkGreen = 0x0320,
		RGB565_Aqua = 0x07ff,
		RGB565_Cyan = 0x07ff,
		RGB565_LightCyan = 0xe7ff,
		RGB565_PaleTurquoise = 0xaf7d,
		RGB565_Aquamarine = 0x7ffa,
		RGB565_Turquoise = 0x471a,
		RGB565_MediumTurquoise = 0x4e99,
		RGB565_DarkTurquoise = 0x067a,
		RGB565_LightSeaGreen = 0x2595,
		RGB565_CadetBlue = 0x5cf4,
		RGB565_DarkCyan = 0x0451,
		RGB565_Teal = 0x0410,
		RGB565_LightSteelBlue = 0xb63b,
		RGB565_PowderBlue = 0xb71c,
		RGB565_LightBlue = 0xaedc,
		RGB565_SkyBlue = 0x867d,
		RGB565_LightSkyBlue = 0x867f,
		RGB565_DeepSkyBlue = 0x05ff,
		RGB565_DodgerBlue = 0x1c9f,
		RGB565_CornflowerBlue = 0x64bd,
		RGB565_SteelBlue = 0x4416,
		RGB565_RoyalBlue = 0x435c,
		RGB565_Blue = 0x001f,
		RGB565_MediumBlue = 0x0019,
		RGB565_DarkBlue = 0x0011,
		RGB565_Navy = 0x0010,
		RGB565_MidnightBlue = 0x18ce,
		RGB565_Lavender = 0xe73f,
		RGB565_Thistle = 0xddfb,
		RGB565_Plum = 0xdd1b,
		RGB565_Violet = 0xec1d,
		RGB565_Orchid = 0xdb9a,
		RGB565_Fuchsia = 0xf81f,
		RGB565_Magenta = 0xf81f,
		RGB565_MediumOrchid = 0xbaba,
		RGB565_MediumPurple = 0x939b,
		RGB565_BlueViolet = 0x895c,
		RGB565_DarkViolet = 0x901a,
		RGB565_DarkOrchid = 0x9999,
		RGB565_DarkMagenta = 0x8811,
		RGB565_Purple = 0x8010,
		RGB565_Indigo = 0x4810,
		RGB565_DarkSlateBlue = 0x49f1,
		RGB565_SlateBlue = 0x6ad9,
		RGB565_MediumSlateBlue = 0x7b5d,
		RGB565_White = 0xffff,
		RGB565_Snow = 0xffdf,
		RGB565_Honeydew = 0xf7fe,
		RGB565_MintCream = 0xf7ff,
		RGB565_Azure = 0xf7ff,
		RGB565_AliceBlue = 0xf7df,
		RGB565_GhostWhite = 0xffdf,
		RGB565_WhiteSmoke = 0xf7be,
		RGB565_Seashell = 0xffbd,
		RGB565_Beige = 0xf7bb,
		RGB565_OldLace = 0xffbc,
		RGB565_FloralWhite = 0xffde,
		RGB565_Ivory = 0xfffe,
		RGB565_AntiqueWhite = 0xff5a,
		RGB565_Linen = 0xff9c,
		RGB565_LavenderBlush = 0xff9e,
		RGB565_MistyRose = 0xff3c,
		RGB565_Gainsboro = 0xdefb,
		RGB565_LightGray = 0xd69a,
		RGB565_Silver = 0xc618,
		RGB565_DarkGray = 0xad55,
		RGB565_Gray = 0x8410,
		RGB565_DimGray = 0x6b4d,
		RGB565_LightSlateGray = 0x7453,
		RGB565_SlateGray = 0x7412,
		RGB565_DarkSlateGray = 0x2a69,
		RGB565_Black = 0x0000
	};
	
	/**
	 * Pixel formats
	 **/
	typedef enum {
		PF_UNKNOWN 			= 0,
		PF_565 				= 1,	//  RGB 565		5 bits red, 6 bits green, 5 bits blue
		PF_4444 			= 2,	// ARGB 4444	4 bits alpha, 4 bits each color channel (16 bits total)
		PF_6666 			= 3,	// ARGB 6666	6 bits alpha, 6 bits each color channel (24 bits total)
		PF_8565 			= 4,	// ARGB 8565	565 with leading 8-bit alpha (24 bits total)
		PF_888				= 5,	//  RGB 888		24-bit color, no alpha
		PF_8888				= 6,	// ARGB 8888	32-bit color with leading b-bit alpha
		PF_INDEXED			= 7,	// 				Indexed color (0-255)
		PF_MONO				= 8,	// 				Mono (on/off) color
		PF_GRAYSCALE		= 9		// 				256 levels of gray (intensity)
	} PixelFormat;

	/**
	 * Check whether a pixel format includes an alpha channel or not
	 * @param  pixelFormat The pixel format to check
	 * @return             Return true if the pixel format has an alpha channel, otherwise false
	 */
	boolean pixelFormatHasAlpha( PixelFormat pixelFormat );


	/**
	 * Return the width, in bytes, of a pixel stored in this format
	 * @param  pixelFormat The pixel format to check
	 * @return             The width in number of bytes
	 */
	uint8_t pixelFormatByteWidth( PixelFormat pixelFormat );

	/**
	 * Holds details of a bitmap in flash memory
	 **/
	typedef struct BitmapS {
		PixelFormat pixelFormat;			// The format of each pixel
		uint32_t transparentColor;			// For non-alpha pixel formats, the color to treat as fully transparent. Usually fuchsia.
		uint32_t dataSize;					// The total number of bytes in the data
		uint32_t width;						// Width of bitmap
		uint32_t height;					// height of bitmap
		const uint8_t* data __attribute__ ((aligned (4))); // Data, aligned to 4-byte boundary
	} Bitmap;
	
	/**
	 * Holds details of a tile map in flash memory
	 **/
	typedef struct TilemapS {
		PixelFormat pixelFormat;			// The format of each pixel
		uint32_t transparentColor;			// For non-alpha pixel formats, the color to treat as fully transparent. Usually fuchsia.
		uint32_t dataSize;					// The total number of bytes in the data
		const uint8_t* data __attribute__ ((aligned (4))); // Data, aligned to 4-byte boundary
		uint32_t tileWidth;					// Width of each tile in the map
		uint32_t tileHeight;				// height of each tile in the map
		uint32_t tileCount;					// Number of tiles in the map
		uint32_t tileStride;				// Stride of each tile in bytes
	} Tilemap;

	/**
	 * Clamp alpha to range 0.0 - 1.0
	 * @param  alpha 		The value to clamp
	 * @return       The clamped value in the range 0.0 - 1.0
	 */
	inline alpha alphaClamp( alpha a ){
		return (a<0)?0:(a>1)?1:a;
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
	void get565as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get4444as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get6666as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get8565as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get888as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get8888as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get8as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get1as5565( uint8_t* p, uint16_t& c, uint8_t& a );

	/**
	 * Accessor function type to get pixels in 5565 format
	 */
	typedef void (*access5565)( uint8_t*, uint16_t&, uint8_t& );

	/**
	 * Use getAccessor5565 on a tilemap to choose the correct data access function.
	 */
	access5565 getAccessor5565( PixelFormat pixelFormat );

	/**
	 * The following functions get a pixel from a bitmap and convert to RGB565 and 8-bit alpha.
	 */
	void get565as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get4444as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get6666as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get8565as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get888as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get8888as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get8as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get1as8565( uint8_t* p, uint16_t& c, uint8_t& a );

	/**
	 * Use getAccessor8565 on a tilemap to choose the correct data access function.
	 */
	typedef void (*access8565)( uint8_t*, uint16_t&, uint8_t& );
	access8565 getAccessor8565( PixelFormat pixelFormat );

	/*
	 * ### CONVERSION
	 */

	/**
	 * Convert individual RGB values to RGB565 16bit format
	 * @param	r		Red component
	 * @param	g		Green component
	 * @param	b		Blue component
	 **/
	inline color565 convertRGBto565(
		uint8_t r,
		uint8_t g,
		uint8_t b
	){
		return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
	}

	/**
	 * Convert 32-bit ARGB to 16-bit RGB565 format and 8-bit alpha
	 * @param	colour		The ARGB 32-bit colour
	 * @param	alpha 		(out) The 8-bit alpha (0-255)
	 **/
	inline color565 convert8888to8565(
		color8888 c,
		uint8_t &alpha
	){
		alpha = c>>24;
		return ((c >> 8) & 0xF800) | ((c >> 5) & 0x07E0) | ((c >> 3) & 0x1F);
	}

	/**
	 * Convert 32-bit ARGB to 16-bit RGB565 format and 5-bit alpha
	 * @param	c			The ARGB 32-bit colour
	 * @param	alpha 		(out) The 5-bit alpha (0-31)
	 **/
	inline color565 convert8888to5565(
		color8888 c,
		uint8_t &alpha
	){
		alpha = c>>27;
		return ((c >> 8) & 0xF800) | ((c >> 5) & 0x07E0) | ((c >> 3) & 0x1F);
	}

	/**
	 * Convert ARGB 32bit to RGB565 16bit format
	 * @param	c			The RGB 24-bit colour (alpha is ignored)
	 **/
	inline color565 convert888to565(
		color888 c
	){
		return ((c >> 8) & 0xF800) | ((c >> 5) & 0x07E0) | ((c >> 3) & 0x1F);
	}

	/**
	 * Convert grayscale 8-bit to RGB565 16-bit format
	 * @param	c			The grayscale color (0-255)
	 **/
	inline color565 convert8to565(
		uint8_t c
	){
		return ((c & 0xF8) << 8) | ((c & 0xFC) << 3) | ((c & 0xF8) >> 3);
	}

	/**
	 * Convert mono 1-bit to RGB565 16-bit format
	 * @param	c			The mono color (0,1)
	 **/
	inline color565 convert1to565(
		uint8_t c
	){
		return (c & 0b1)?RGB565_White:RGB565_Black;
	}

	/**
	 * Convert HSV to components
	 * @param  H 	Hue component
	 * @param  S  	Saturation component
	 * @param  V 	Value component
	 */
	inline color565 convertHSVto565(
		float H,
		float S,
		float V
	){
		float		p, q, t, ff;
		int8_t		i;
		float		r,g,b;

		if (H >= 360.0) H = 0.0;
		H /= 60.0;
		i = (int8_t)H;
		ff = H - i;
		p = V * (1.0 - S);
		q = V * (1.0 - (S * ff));
		t = V * (1.0 - (S * (1.0 - ff)));

		switch(i) {
			case 0: r = V; g = t; b = p; break;
			case 1: r = q; g = V; b = p; break;
			case 2: r = p; g = V; b = t; break;
			case 3: r = p; g = q; b = V; break;
			case 4: r = t; g = p; b = V; break;
			case 5:
			default:
				r = V; g = p; b = q; break;
		}

		return ((uint8_t)(r * 31.0f) << 11) | ((uint8_t)(g * 63.0f) << 5) | (uint8_t)(b * 31.0f);
	}

	/*
	 * ### ALPHA BLENDING
	 */

	/**
	 * Calculate the pre-multiplied value of an RGB565 color for fast blending
	 * @param c  	RGB565 color
	 */
	inline uint32_t colorPrepare565( color565 c ){
		return (((uint32_t)c | ((uint32_t)c << 16)) & 0b00000111111000001111100000011111);
	}

	/**
	 * Calculate the pre-multiplied value of a 24-bit RGB color for 565 fast blending
	 * @param c  	RGB888 color
	 */
	inline uint32_t colorPrepare565( color888 c ){
		return ((c & 0xF80000) >> 8) | ((c & 0xFC00) << 11) | ((c & 0xF8) >> 3);
	}

	/**
	 * Calculate the pre-multiplied value of 8-bit RGB color components for 565 fast blending.
	 * @param r  		Red color component
	 * @param g  		Green color component
	 * @param b  		Blue color component
	 */
	inline uint32_t colorPrepare565( uint8_t r, uint8_t g, uint8_t b ){
		return ((r & 0xF8) << 8) | ((g & 0xFC) << 19) | ((b & 0xF8) >> 3);
	}

	/**
	 * Calculate the pre-multiplied value of alpha for fast blending. Converts to range 0-31
	 * @param alpha  	Alpha value 0-255
	 */
	inline uint8_t alpha5bit( uint8_t a ){
		return a >> 3;
	}
	inline uint8_t alpha5bit( alpha a ){
		return (uint8_t)( alphaClamp(a) * 31 );
	}

	/**
	 * Blend two 16-bit RGB565 colors. Alpha already in range 0-31 (5-bit).
	 * @param	fg		Color to draw in RGB565 (16bit)
	 * @param	bg		Color to draw over in RGB565 (16bit)
	 * @param	a		Alpha 0 - 31. If in range 0-255, use alphaBlend8565
	 **/
	inline color565 alphaBlend5565(
		uint32_t fg,
		uint32_t bg,
		uint8_t a
	){
		bg = (bg | (bg << 16)) & 0b00000111111000001111100000011111;
		fg = (fg | (fg << 16)) & 0b00000111111000001111100000011111;
		uint32_t result = ((((fg - bg) * a) >> 5) + bg) & 0b00000111111000001111100000011111;
		return (color565)((result >> 16) | result); // contract result
	}

	/**
	 * Blend two 16-bit RGB565 colors. Alpha in range 0-255.
	 * @param	fg		Color to draw in RGB565 (16bit)
	 * @param	bg		Color to draw over in RGB565 (16bit)
	 * @param	a		Alpha 0 - 255. If in range 0-31, use alphaBlend5565
	 **/
	inline color565 alphaBlend8565(
		uint32_t fg,
		uint32_t bg,
		uint8_t a
	){
		a = alpha5bit( a );
		bg = (bg | (bg << 16)) & 0b00000111111000001111100000011111;
		fg = (fg | (fg << 16)) & 0b00000111111000001111100000011111;
		uint32_t result = ((((fg - bg) * a) >> 5) + bg) & 0b00000111111000001111100000011111;
		return (color565)((result >> 16) | result); // contract result
	}

	/**
	 * Slightly faster blending if the FG color has been pre-prepared.
	 * @param  preparedFg 	Pre-prepared FG color (@see colorPrepare565)
	 * @param  bg  			BG color
	 * @param  a      		Alpha (5-bit, 0-31)
	 * @return            	The blended color
	 */
	inline color565 alphaBlendPrepared5565(
		uint32_t preparedFg,
		uint32_t bg,
		uint8_t a
	){
		bg = (bg | (bg << 16)) & 0b00000111111000001111100000011111;
		uint32_t result = ((((preparedFg - bg) * a) >> 5) + bg) & 0b00000111111000001111100000011111;
		return (color565)((result >> 16) | result); // contract result
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
	void get565asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get4444asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get6666asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get8565asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get888asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get8888asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get8asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get1asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );

	/**
	 * Use getAccessorARGB on a tilemap to choose the correct data access function.
	 */
	typedef void (*accessARGB)( uint8_t*, uint8_t&, uint8_t&, uint8_t&, uint8_t& );
	accessARGB getAccessorARGB( PixelFormat pixelFormat );

	/*
	 * ### CONVERSION
	 */
	
	/**
	 * Converts RGB565 format to individual RGB color components
	 * @param	color	The RGB565 color to convert
	 * @param	r		(out) Red component
	 * @param	g		(out) Green component
	 * @param	b		(out) Blue component
	 **/
	inline void convert565toRGB(
		color565 color,
		uint8_t &r,
		uint8_t &g,
		uint8_t &b
	){
		r = ((color >> 8) & 0b11111000) | ((color >> 13) & 0b111);
		g = ((color >> 3) & 0b11111100) | ((color >> 9) & 0b11);
		b = ((color << 3) & 0b11111000) | ((color >> 2) & 0b111);
	}

	/**
	 * Converts RGB888 24-bit format to individual RGB color components
	 * @param	color	The RGB888 color to convert
	 * @param	r		(out) Red component
	 * @param	g		(out) Green component
	 * @param	b		(out) Blue component
	 **/
	inline void convert888toRGB(
		color888 color,
		uint8_t &r,
		uint8_t &g,
		uint8_t &b
	){
		r = color >> 16;
		g = (color >> 8) & 0xFF;
		b = color & 0xFF;
	}

	/**
	 * Converts ARGB8888 32-bit format to individual A and RGB color components
	 * @param	color	The RGB8888 color to convert
	 * @param	a		(out) Alpha
	 * @param	r		(out) Red component
	 * @param	g		(out) Green component
	 * @param	b		(out) Blue component
	 **/
	inline void convert8888toRGB(
		color8888 color,
		uint8_t &a,
		uint8_t &r,
		uint8_t &g,
		uint8_t &b
	){
		a = color >> 24;
		r = (color >> 16) & 0xFF;
		g = (color >> 8) & 0xFF;
		b = color & 0xFF;
	}

	/**
	 * Converts grayscale 8-bit format to individual RGB color components
	 * @param	color	The grayscale color to convert
	 * @param	r		(out) Red component
	 * @param	g		(out) Green component
	 * @param	b		(out) Blue component
	 */
	inline void convert8toRGB(
		uint8_t color,
		uint8_t &r,
		uint8_t &g,
		uint8_t &b
	){
		r = color;
		g = color;
		b = color;
	}

	/**
	 * Converts mono 1-bit format to individual RGB color components
	 * @param	color	The mono color to convert (0,1)
	 * @param	r		(out) Red component
	 * @param	g		(out) Green component
	 * @param	b		(out) Blue component
	 */
	inline void convert1toRGB(
		uint8_t color,
		uint8_t &r,
		uint8_t &g,
		uint8_t &b
	){
		if (color & 0b1){
			r = 255; g = 255; b = 255;
		}
		else{
			r = 0; g = 0; b = 0;
		}
	}

	/**
	 * Convert HSV to RGB components
	 * @param  H 	Hue component
	 * @param  S  	Saturation component
	 * @param  V 	Value component
	 * @param  r  	(out) Red
	 * @param  g 	(out) Green
	 * @param  b 	(out) Blue
	 */
	inline void convertHSVtoRGB(
		float H,
		float S,
		float V,
		uint8_t &r,
		uint8_t &g,
		uint8_t &b
	){
		float		p, q, t, ff;
		int8_t		i;

		if (H >= 360.0) H = 0.0;
		H /= 60.0;
		i = (int8_t)H;
		ff = H - i;
		p = V * (1.0 - S);
		q = V * (1.0 - (S * ff));
		t = V * (1.0 - (S * (1.0 - ff)));

		switch(i) {
			case 0: r = (uint8_t)(V*255.0f); g = (uint8_t)(t*255.0f); b = (uint8_t)(p*255.0f); break;
			case 1: r = (uint8_t)(q*255.0f); g = (uint8_t)(V*255.0f); b = (uint8_t)(p*255.0f); break;
			case 2: r = (uint8_t)(p*255.0f); g = (uint8_t)(V*255.0f); b = (uint8_t)(t*255.0f); break;
			case 3: r = (uint8_t)(p*255.0f); g = (uint8_t)(q*255.0f); b = (uint8_t)(V*255.0f); break;
			case 4: r = (uint8_t)(t*255.0f); g = (uint8_t)(p*255.0f); b = (uint8_t)(V*255.0f); break;
			case 5:
			default:
				r = (uint8_t)(V*255.0f); g = (uint8_t)(p*255.0f); b = (uint8_t)(q*255.0f); break;
		}
	}

	/*
	 * ### ALPHA BLENDING
	 */

	/**
	 * Fast alpha-blending of RGB color components
	 * @param r1    First color R component
	 * @param g1    First color G component
	 * @param b1    First color B component
	 * @param r2    Second color R component
	 * @param g2    Second color G component
	 * @param b2    Second color B component
	 * @param alpha The alpha (0-255)
	 * @param r     (out) Blended R component
	 * @param g     (out) Blended G component
	 * @param b     (out) Blended B component
	 */
	inline void alphaBlendARGB(
		uint8_t r1, uint8_t g1, uint8_t b1,
		uint8_t r2, uint8_t g2, uint8_t b2,
		uint8_t alpha,
		uint8_t& r, uint8_t& g, uint8_t& b
	){
		uint32_t rb = (r1 << 16) | b1;
		uint32_t g0  = g1 << 8;
		rb += (((r2 << 16) | b2) - rb) * alpha >> 8;
		g0  += ((g2 << 8) -  g0) * alpha >> 8;
		r = ((rb >> 16) & 0xff);
		g = ((g0 >> 8) & 0xff);
		b = (rb & 0xff);
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
	void get565as8888( uint8_t* p, uint32_t& c );
	void get4444as8888( uint8_t* p, uint32_t& c );
	void get6666as8888( uint8_t* p, uint32_t& c );
	void get8565as8888( uint8_t* p, uint32_t& c );
	void get888as8888( uint8_t* p, uint32_t& c );
	void get8888as8888( uint8_t* p, uint32_t& c );
	void get8as8888( uint8_t* p, uint32_t& c );
	void get1as8888( uint8_t* p, uint32_t& c );

	/**
	 * Use getAccessor8888 on a tilemap to choose the correct data access function.
	 */
	typedef void (*access8888)( uint8_t*, uint32_t& );
	access8888 getAccessor8888( PixelFormat pixelFormat );

	/*
	 * ### CONVERSION
	 */

	/**
	 * Convert individual RGB values to RGB888 24bit format
	 * @param	r		Red component
	 * @param	g		Green component
	 * @param	b		Blue component
	 * @return		The RGB888 color
	 **/
	inline color888 convertRGBto888(
		uint8_t r,
		uint8_t g,
		uint8_t b
	){
		return (r << 16) | (g << 8) | b;
	}

	/**
	 * Converts RGB565 format to RGB888 format
	 * @param	color	The RGB565 color to convert
	 * @return		The RGB888 color
	 **/
	inline color888 convert565to888(
		color565 c
	){
		return ((c & 0b1111100000000000) << 8) | ((c & 0b11100000000) << 3)
			| ((c & 0b11111100000) << 5) | ((c & 0b11000000000) >> 1)
			| ((c & 0b11111) << 3) | ((c & 0b11100) >> 2);
	}

	/**
	 * Converts grayscale (8-bit) to RGB888 format
	 * @param  c 	The grayscale value (0-255)
	 * @return		The RGB888 color
	 */
	inline color888 convert8to888( uint8_t c ){
		return (c << 16) | (c << 8) | c;
	}

	/**
	 * Converts mono (1-bit) to RGB888 format
	 * @param  c 	The mono value (0-1)
	 * @return		The RGB888 color
	 */
	inline color888 convert1to888( uint8_t c ){
		return (c & 0b1)?RGB888_White:RGB888_Black;
	}

	/**
	 * Convert HSV to RGB888 24-bit
	 * @param  H 	Hue component
	 * @param  S  	Saturation component
	 * @param  V 	Value component
	 * @param  r  	(out) Red
	 * @param  g 	(out) Green
	 * @param  b 	(out) Blue
	 */
	inline color888 convertHSVto888(
		float H,
		float S,
		float V
	){
		uint8_t r, g, b;
		convertHSVtoRGB(H,S,V,r,g,b);
		return (r << 16) | (g << 8) | b;
	}

	/*
	 * ### ALPHA BLENDING
	 *
	 * Base code found in XPRoger github
	 * https://gist.github.com/XProger/96253e93baccfbf338de
	 * Matches the 16 bit algorithm, but splits to two 32-bit numbers because of overflow
	 * from the multiplication.
	 **/

	/**
	 * Convert alpha from range 0.0-1.0 to 0-255 (8 bit)
	 * @param  a  	The alpha 0.0 - 1.0
	 * @return   The 8-bit alpha value
	 */
	inline uint8_t alpha8bit( alpha a ){
		return (uint8_t)( alphaClamp(a) * 255 );
	}

	/**
	 * Calculate the pre-multiplied value of a 32-bit RGB color to the two
	 * split components required for 888 fast blending.
	 * @param color  	RGB888 color
	 * @param color  	(out) RB split component
	 * @param color  	(out) G split component
	 */
	inline void colorPrepare888( color888 c, uint32_t& rb, uint32_t& g ){
		rb = c & 0xff00ff;
		g  = c & 0x00ff00;
	}

	/**
	 * Calculate the pre-multiplied value of RGB color components to the two
	 * split components required for 888 fast blending.
	 * @param r  		Red color component
	 * @param g  		Green color component
	 * @param b  		Blue color component
	 * @param orb  	(out) RB split component
	 * @param og  	(out) G split component
	 */
	inline void colorPrepare888( uint8_t r, uint8_t g, uint8_t b, uint32_t& orb, uint32_t& og ){
		orb = (r << 16) | b;
		og  = g << 8;
	}

	/**
	 * Blend two RGB888 pixels
	 * @param	fg		Color to draw in RGB 8-bit (24 bit)
	 * @param	bg		Color to draw over in RGB 8-bit (24 bit)
	 * @param	alpha	Alpha 0-255
	 * @return       Blended color
	 */
	inline color888 alphaBlend8888(
		color888 fg,
		color888 bg,
		uint8_t alpha
	){
		uint32_t rb = fg & 0xff00ff;
		uint32_t g  = fg & 0x00ff00;
		rb += ((bg & 0xff00ff) - rb) * alpha >> 8;
		g  += ((bg & 0x00ff00) -  g) * alpha >> 8;
		return (rb & 0xff00ff) | (g & 0xff00);
	}

	/**
	 * Blend two RGB888 pixels
	 * @param  preparedRB 	Pre-prepared RB split color components (@see colorPrepare888)
	 * @param  preparedG 	Pre-prepared G split color components (@see colorPrepare888)
	 * @param	bg			Color to draw over in RGB 8-bit (24 bit)
	 * @param	alpha		Alpha 0-255
	 * @return       Blended color
	 */
	inline color888 alphaBlendPrepared8888(
		uint32_t preparedRB,
		uint32_t preparedG,
		color888 bg,
		uint8_t alpha
	){
		preparedRB += ((bg & 0xff00ff) - preparedRB) * alpha >> 8;
		preparedG  += ((bg & 0x00ff00) -  preparedG) * alpha >> 8;
		return (preparedRB & 0xff00ff) | (preparedG & 0xff00);
	}
	
} // ns

#endif