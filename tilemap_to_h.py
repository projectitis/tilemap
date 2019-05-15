from glob import glob
from os import path
from PIL import Image
import re

###
### Compile resources to c header files
###

# This code is available under the MIT license
# Copyright (c) 2018 Peter Vullings (Projectitis)
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Step through all image files in the script folder and prepare
# a header file for each so that the tilemap is compiled into the
# program.

# The filename will determine the header file name and variable name.
# Optional parameters may be included in the filename of the resource.

#		.bmp
#		.png
#		.jpg
#		.jpeg
#
#		Options:
#			Add these options as part of the file name of the source image:
#		
#				t-__x__
#						will process the image as individual tiles.
#						instead of all pixels top to bottom, the array will
#						contain the pixels of the first tile, followed by the
#						second etc. Examples:
#						t-32x32		(tileset.t-32x32.bmp)
#						t-8x16		(character_sprites.t-8x16.png)
#				p-___
#						Specify the pixel format. Note: If a format with alpah is specified and the
#						source image does not contain an alpha channel, all alpha values will be  
#						p-RGB565		p-565		Default. 16-bit packed format. 	RRRRRGGGGGGBBBBB
#						p-ARGB4444		p-4444		16-bit packed with alpha.		aaaaRRRRGGGGBBBB
#						p-ARGB8565		p-8565		24-bit packed with alpha.		aaaaaaaaRRRRRGGGGGGBBBBB
#						p-ARGB6666		p-6666		24-bit packed with alpha.		aaaaaaRRRRRRGGGGGGBBBBBB
#						p-RGB888		p-888		24-bit, no alpha				RRRRRRRRGGGGGGGGBBBBBBBB
#						p-ARGB8888		p-8888		32-bit, with alpha				aaaaaaaaRRRRRRRRGGGGGGGGBBBBBBBB
#						Examples:
#						character_sprites.t-8x16.p-565.png
#						gui_icons.t-24x24.p-ARGB8888.png
#						
#				a-___
#						If the pixel format does not support an alpha channel, specify a colour to be
#						treated as a fully transparent color (for on/off alpha). This can be specified as
#						any of the following:
#						a-FF00FF		A hexideciaml color value that matches the pixel format. Do NOT
#										start with 0x		
#						a-10x12			NOT YET SUPPORTED: The coordinates of a pixel within the image. The color
#										of that pixel will be used as the transparent color. Most often
#										this is 0x0 (top-left).
#									
	
# Define some pixel formatting functions
# 565 as two 8-bit unsigned int
def pixel565( a, r, g, b ):
	# first place in single 16-bit number, then split
	p = int((r << 8) & 0b1111100000000000) | int((g << 3) & 0b0000011111100000) | int((b >> 3) & 0b0000000000011111)
	return [(p>>8),p&255]

# 888 as three 8-bit unsigned ints
def pixel888( a, r, g, b ):
	return [int(r), int(g), int(b)]

# 4444 as two 8-bit unsigned int
def pixel4444( a, r, g, b ):
	# first place in single 16-bit number, then split
	p = int((a << 8) & 0b1111000000000000) | int((r << 4) & 0b0000111100000000) | int(g & 0b0000000011110000) | int((b >> 4) & 0b0000000000001111)
	return [(p>>8),p&255]

# 6666 as three 8-bit unsigned ints
def pixel6666( a, r, g, b ):
	# first place in single 24-bit number, then split
	p = int((a << 16) & 0b111111000000000000000000) | int((r << 10) & 0b000000111111000000000000) | int((g<<4) & 0b000000000000111111000000) | int((b >> 2) & 0b000000000000000000111111)
	return [int(p & 0b000000000000000011111111),int((p >> 8) & 0b000000000000000011111111),int((p>>16) & 0b000000000000000011111111)]

# 8565 as three 8-bit unsigned ints
def pixel8565( a, r, g, b ):
	# first place in single 24-bit number, then split
	p = int((a << 16) & 0b111111110000000000000000) | int((r << 8) & 0b000000001111100000000000) | int((g<<3) & 0b000000000000011111100000) | int((b >> 3) & 0b000000000000000000011111)
	return [int(p & 0b000000000000000011111111),int((p >> 8) & 0b000000000000000011111111),int((p>>16) & 0b000000000000000011111111)]

# 8888 as four 8-bit unsigned ints 
def pixel8888( a, r, g, b ):
	return [int(a), int(r), int(g), int(b)]

# Pixel transformations
convertPixelFuncs = {
    'RGB565': pixel565,
    'RGB888': pixel888,
    'ARGB4444': pixel4444,
    'ARGB6666': pixel6666,
    'ARGB8565': pixel8565,
    'ARGB8888': pixel8888
}

# slugify a string
def slugify(text):
    text = text.lower()
    return re.sub(r'[\W_]+', '_', text)

# Get list of files in this folder
resources = glob('*.png')
resources.extend(glob('*.bmp'))
resources.extend(glob('*.jpg'))
resources.extend(glob('*.jpeg'))
for file in list(resources):

	# Split the filename by dot to get the parts, including options
	filename = path.basename(file)
	fileparts = filename.split('.')
	if len(fileparts) < 2:
		continue
	
	# first and last parts of filename are name and extn
	name = slugify(fileparts.pop(0))
	extn = fileparts.pop().lower();

	# ignore previews
	if name == 'preview': continue
	
	# any remaining parts are options
	options = {}
	for opstr in fileparts:
		options[opstr[:1]] = opstr[2:]
	
	# Start the output
	outstr = '';
	
	### IMAGES
	if extn in ['png','bmp','jpg','jpg']:
		# load the image
		im = Image.open(file)
		
		# Check if the image has alpha
		alpha = im.mode == 'RGBA'
		
		# Some useful messages to console
		print()
		print('Processing',filename,'(image)')
		print('  Source image mode is',im.mode)
		
		# Pixel format
		# Option: p-___
		pfAlpha = {
			"4444": "ARGB4444",
			"6666": "ARGB6666",
			"8565": "ARGB8565",
			"8888": "ARGB8888"
		}
		pfSolid = {
			"565": "RGB565",
			"888": "RGB888"
		}
		pfBits = {
			"ARGB4444": 16,
			"ARGB6666": 24,
			"ARGB8565": 24,
			"ARGB8888": 32,
			"RGB565": 16,
			"RGB888": 24
		}
		pfCodes = {
			"ARGB4444": 'mac::PF_4444',
			"ARGB6666": 'mac::PF_6666',
			"ARGB8565": 'mac::PF_8565',
			"ARGB8888": 'mac::PF_8888',
			"RGB565": 'mac::PF_565',
			"RGB888": 'mac::PF_888'
		}
		pfTransparentColor = {
			"ARGB4444": '0',
			"ARGB6666": '0',
			"ARGB8565": '0',
			"ARGB8888": '0',
			"RGB565": 'mac::RGB565_Transparent',
			"RGB888": 'mac::RGB888_Transparent'
		}
		pfmt = 'RGB565';
		if 'p' in options:
			pfmt = options['p']
		else:
			print('  WARNING: No destination pixel format specified. Use p-___ option to specify.')
			print('  Add it to the filename after a period. For example: mytilemap.p-RGB565.png')
		if not pfmt in pfAlpha.values() and not pfmt in pfAlpha.keys() and not pfmt in pfSolid.values() and not pfmt in pfSolid.keys():
			pfmt = 'ARGB6666' if alpha else 'RGB565'
		if pfmt in pfAlpha.keys():
			pfmt = pfAlpha[pfmt]
		elif pfmt in pfSolid.keys():
			pfmt = pfSolid[pfmt]
		print('  Using destination pixel format',pfmt)
		if (not alpha) and (pfmt in pfAlpha.values() or pfmt in pfAlpha.keys()):
			print('  WARNING: Source image does not contain alpha channel. Alpha will be set to full. This may result in a larger file than intended?')
		
		# Get image dimensions
		width, height = im.size
		tilewidth, tileheight = width, height
		rows, cols = 1, 1
		tilesize = tilewidth*tileheight

		# transparent color
		trns = pfTransparentColor[pfmt];
		if not trns == '0':
			if 'a' in options:
				trns = '0x'+options['a']
				print('  Setting transparent color',trns)
			else:
				print('  Assuming transparent color',trns)

		# Option: t-__x__
		# Are we splitting the image in to tiles?
		if 't' in options:
			tilesize = [int(x) for x in options['t'].split('x')]
			if len(tilesize)==2:
				tilewidth, tileheight = tilesize[:2]
				if (width%tilewidth==0) and (height%tileheight==0):
					rows = int(height/tileheight)
					cols = int(width/tilewidth)
					print('  Slicing',(cols*rows),'tiles at',tilewidth,'x',tileheight)
		else:
			print('  WARNING: No tiles. Destination image single large bitmap. Use t-__x__ option to specify.')
			print('  Add it to the filename after a period. For example: mytilemap.t-16x16.png')
					
		# Holds pixel data
		p = [];
		
		# steps tiles
		a = 255
		convertFunc = convertPixelFuncs[pfmt]
		for row in range(rows):
			for col in range(cols):
				# step pixels in tile
				for y in range(tileheight):
					for x in range(tilewidth):
						if alpha:
							# get pixels including alpha
							r,g,b,a = im.getpixel((col*tilewidth+x,row*tileheight+y))
						else:
							r,g,b = im.getpixel((col*tilewidth+x,row*tileheight+y))
						p += convertFunc(a,r,g,b)
				
		# Output to file
		outstr += '#ifndef _TILEMAP_'+name+'_H_\n'
		outstr += '#define _TILEMAP_'+name+'_H_ 1\n\n'
		outstr += '#include "Bitmap.h"\n\n'
		outstr += '__attribute__((aligned(4))) static const uint8_t '+name+'_data[] = {\n'
		c = 0
		tp = 0
		f = True
		print(' ',len(p),'bytes in output as 8-bit words');
		# Step pixels and output in groups of 48
		for pc in p:
			if f:
				outstr += ' '
				f = False
			else:
				outstr += ','
			# XXX: 2, 3 or 4 bytes instead of just one
			outstr += '0x{:02x}'.format(pc)
			c += 1
			tp += 1
			if c == 36:
				outstr += '\n'
				c = 0
		outstr += '};\n\n'
		
		# typedef struct {
		# 	uint8_t pixelFormat;
		# 	uint32_t transparentColor;
		# 	uint32_t dataSize;
		# 	uint8_t* data;
		# 	uint32_t tileWidth;
		# 	uint32_t tileHeight;
		# 	uint32_t tileCount;
		# 	uint32_t tileStride;
		# } Tilemap;
		outstr += 'const mac::Tilemap '+name+' = {\n'
		outstr += '\t.pixelFormat = '+pfCodes[pfmt]+',\n'
		outstr += '\t.transparentColor = '+trns+',\n'
		outstr += '\t.dataSize = '+str(tp)+',\n'
		outstr += '\t.data = '+name+'_data,\n'
		outstr += '\t.tileWidth = '+str(tilewidth)+',\n'
		outstr += '\t.tileHeight = '+str(tileheight)+',\n'
		outstr += '\t.tileCount = '+str(rows*cols)+',\n'
		outstr += '\t.tileStride = '+str(tilewidth*tileheight)+',\n'
		outstr += '};\n\n'
		outstr += '#endif'

		# Save
		outfile = open('./'+name+'.h', 'w')
		outfile.write(outstr)
		outfile.close()
		print('  Saved as '+name+'.h');
			
# If called directly (ignored if run by another script)
if __name__ == '__main__':
	# Wait before exit for user to read messages
	print()
	input("Press enter to close")