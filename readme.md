# tilemap
Tilemap helpers and code, aimed at microprocessors

## mac
This file is part of the mac (or μac) "Microprocessor App Creator" library.
mac is a project that enables creating beautiful and useful apps on the [Teensy microprocessor](https://www.pjrc.com/teensy/), but hopefully is generic enough to be ported to other microprocessor boards. The various libraries that make up mac (includign this one) might also be useful in other projects.

# Status
**Work in progress! Use at own risk.**
mac is still in development. Once it's ready for alpha release, I'll be updating this file to link to the full library for your pleasure :) 

## tilemap (tilemap_to_h.py)
`Bitmap.h` contains a tilemap type (`Tilemap`) that describes pixels packed into a tile map in a header file. There is a script (`tilemap_to_h.py`) to convert images to the tilemap format. When it is run it will convert all images in the same directory into tilemaps, each with it's own .h file. Options for the script can be specified in the file name of the image. For example:
 
* `gui_icons.t-24x24.p-RGB565.png` will cut the png into 24x24 pixel tiles, and convert each pixel to RGB565 format (tile tilemap will contain RGB565 pixels).
* `character_sprites.t-30x60.p-6666.png` will create a tilemap of 30x60 pixel tiles in ARGB6666 format (24-bits total, 6-bits each for alpha, R, G and B).
 
An image is cut into tiles from top to bottom, and left to right. The tilemap data will contain the pixels for each tile one after the other. The definition of the tilemap is:
````
typedef struct TilemapS {
	PixelFormat pixelFormat;			// The format of each pixel
    uint32_t transparentColor;          // For non-alpha pixel formats, the color to treat as fully transparent. Usually fuchsia.
	uint32_t dataSize;					// The total number of 8-bit words in the data
	const uint8_t* data __attribute__ ((aligned (4))); // Data, aligned to a 4-byte boundary
	uint32_t tileWidth;					// Width of each tile in the map
	uint32_t tileHeight;				// height of each tile in the map
	uint32_t tileCount;					// Number of tiles in the map
	uint32_t tileStride;				// Stride of each tile in 8-bit words
} Tilemap;
````
A tile is accessed by it's index, not by it's x or y position in the original image. For example, a 100x100 image cut into 25x25 tiles will result in 16 tiles (index 0 to 15). You would access tile number 8 (index=7) like this:
````
// Code example 1
// --------------
// A 100x100 image cut into 25x25 tiles using RGB565 (2-bytes per pixel). i.e.:
//    tilemap.pixelFormat = mac::PF_565;
//    tilemap.dataSize = 20000;
//    tilemap.tileWidth = 25;
//    tilemap.tileHeight = 25;
//    tilemap.tileCount = 16;
//    tilemap.tileStride = 1250; 

int16_t tileIndex = 7; // Access the 8th tile
uint8_t* startOfTileData = tilemap.data + (tilemap.tileStride * tileIndex);
// or
uint8_t* startOfTileData = tilemap.data[tilemap.tileStride * tileIndex];
````
See the notes in `tilemap_to_h.py`, and the comments in `Bitmap.h`, for more details.
 
## Pixel formats
The following pixel formats are supported within a tilemap:

* RGB565 (`p-RGB565` or `p-565`). Total 16 bits. No alpha, 5 bits R, 6 bits G, 5 bits B.
* ARGB4444 (`p-ARGB4444` or `p-4444`). Total 16 bits. 4 bits alpha, 4 bits R, 4 bits G, 4 bits B
* ARGB8565 (`p-ARGB8565` or `p-8565`). Total 24 bits. 8 bits alpha, 5 bits R, 6 bits G, 5 bits B.
* ARGB6666 (`p-ARGB6666` or `p-6666`). Total 24 bits. 6 bits alpha, 6 bits R, 6 bits G, 6 bits B.
* RGB888 (`p-RGB888` or `p-888`). Total 24 bits. No alpha, 8 bits R, 8 bits G, 8 bits B.
* ARGB8888 (`p-ARGB8888` or `p-8888`). Total 32 bits. 8 bits alpha, 8 bits R, 8 bits G, 8 bits B.
 
You can preview what your image will look like in each of the pixel formats using the script `preview.py`. See help below.

## Rendering
Rendering the tiles is handled by the user (i.e. you write the code), or alternatively the mac library has built-in support for fast rendering full alpha-blended tilemaps in 16-bit color. The included header file `Bitmap.h` contains a full set of 'accessor' functions to read pixels from the tilemap in the correct format, and convert them for display in either RGB565 or RGB888 format (whichever your display system or graphics library uses).

Following on from code example 1, this is how you would read a pixel from a tilemap. In this example, the tilemap data is stored as RGB565 format, and the user is reading it as RGB888 i.e. as individual 8-bit R, G and B components.
````
// Code example 2
// --------------
// Use the supplied method to grab the correct accessor function, then step through the pixels in the tile.
access8888 myPixelAccessor = getAccessor8888( tilemap );
uint8_t r,g,b,a;
int16_t tileIndex = 7; // Access the 8th tile
uint8_t* dataPointer = tilemap.data + (tilemap.tileStride * tileIndex);
a = 255; // Alpha is always full as image doesn't contain alpha channel

// Loop for pixels
for (y=0; y<tilemap.tileHeight; y++){
    for (x=0; x<tilemap.tileWidth; x++){
        myPixelAccessor( dataPointer, r, g, b, a );
        // r,g,b now contain the color components
        doSomethingWithPixel(x,y, r,g,b);
    }
}
````
In the example above, `access8888` is a function pointer type. If you are uncomfortable with this you can directly use the correct accessor function if you know the input and output pixel formats in advance:
````
// Code example 3
// --------------
// Use a predetermined accessor function to step through the pixels in the tile.
uint8_t r,g,b,a;
int16_t tileIndex = 7; // Access the 8th tile
uint8_t* dataPointer = tilemap.data + (tilemap.tileStride * tileIndex);

// Loop for pixels
for (y=0; y<tilemap.tileHeight; y++){
    for (x=0; x<tilemap.tileWidth; x++){
        get565as8888( dataPointer, r, g, b, a );
        // r,g,b now contain the color components
        doSomethingWithPixel(x,y, r,g,b);
    }
}
````
## Previewing different pixel formats (preview.py)
You can preview what your tilemap will look like in different image formats by running the script `preview.py`. This will iterate over each image in the same directory and create a preview image for it (with 'preview' prefixed to the filename). Of course, previously generated preview images are ignored :)

For every image, a preview image will be generated that is twice as wide and twice as high as the original. It contains the same image four times:

* The top-left image is the original image
* The top-right image is converted to RGB565 (or ARGB8565 if the source image contains alpha)
* The bottom-left image is converted to RGB444 (or ARGB 4444 if the source image contains alpha)
* The bottom-right image is converted to RGB666 (or ARGB 6666 if the source image contains alpha)

Actually, the pixels are down-sampled to the lower format, and then up-sampled again to the orignal format (most likely RGB8888), but this gives the same effect as viewing the image in the down-sampled pixel format. Open the preview image in your image editor to get a close look at the result.

For example, the 100x100 image `gui_icons.t-25x25.p-565.png` will result in a new image called `preview.gui_icons.png` which is 200x200 pixels.

## Named web colors (colors.py)
The file `Bitmap.h` contains definitions for the standard 'named' web colors, which [can be found on the wiki](https://en.wikipedia.org/wiki/Web_colors#X11_color_names). The colors are included in both RGB888 and RGB565 format. The file to generate these colors, `colors.py` has been included just in case you would like to modify it to either add/change colors, or to generate them in other pixel formats.
