###
### Create a list of 'named colors' for use in c/c++
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


# below is the raw list of colors in R G B component form, these are from:
# https://en.wikipedia.org/wiki/Web_colors
colors = {
	# Fuschia is generally used as a transparent color
	'Transparent' : [255,0,255],

	# Pink colors
	'Pink' : [255,192,203],
	'LightPink': [255,182,193],
	'HotPink': [255,105,180],
	'DeepPink': [255,20,147],
	'PaleVioletRed': [219,112,147],
	'MediumVioletRed': [199,21,133],

	# Red colors
	'LightSalmon': [255,160,122],
	'Salmon': [250,128,114],
	'DarkSalmon': [233,150,122],
	'LightCoral': [240,128,128],
	'IndianRed': [205,92,92],
	'Crimson': [220,20,60],
	'Firebrick': [178,34,34],
	'DarkRed': [139,0,0],
	'Red': [255,0,0],

	# Orange colors	
	'OrangeRed': [255,69,0],
	'Tomato': [255,99,71],
	'Coral': [255,127,80],
	'DarkOrange': [255,140,0],
	'Orange': [255,165,0],

	# Yellow colors	
	'Yellow': [255,255,0],
	'LightYellow': [255,255,224],
	'LemonChiffon': [255,250,205],
	'LightGoldenrodYellow': [250,250,210],
	'PapayaWhip': [255,239,213],
	'Moccasin': [255,228,181],
	'PeachPuff': [255,218,185],
	'PaleGoldenrod': [238,232,170],
	'Khaki': [240,230,140],
	'DarkKhaki': [189,183,107],
	'Gold': [255,215,0],

	# Brown colors	
	'Cornsilk': [255,248,220],
	'BlanchedAlmond': [255,235,205],
	'Bisque': [255,228,196],
	'NavajoWhite': [255,222,173],
	'Wheat': [245,222,179],
	'Burlywood': [222,184,135],
	'Tan': [210,180,140],
	'RosyBrown': [188,143,143],
	'SandyBrown': [244,164,96],
	'Goldenrod': [218,165,32],
	'DarkGoldenrod': [184,134,11],
	'Peru': [205,133,63],
	'Chocolate': [210,105,30],
	'SaddleBrown': [139,69,19],
	'Sienna': [160,82,45],
	'Brown': [165,42,42],
	'Maroon': [128,0,0],

	# Green colors	
	'DarkOliveGreen': [85,107,47],
	'Olive': [128,128,0],
	'OliveDrab': [107,142,35],
	'YellowGreen': [154,205,50],
	'LimeGreen': [50,205,50],
	'Lime': [0,255,0],
	'LawnGreen': [124,252,0],
	'Chartreuse': [127,255,0],	
	'GreenYellow': [173,255,47],
	'SpringGreen': [0,255,127],
	'MediumSpringGreen': [0,250,154],
	'LightGreen': [144,238,144],
	'PaleGreen': [152,251,152],
	'DarkSeaGreen': [143,188,143],
	'MediumAquamarine': [102,205,170],
	'MediumSeaGreen': [60,179,113],
	'SeaGreen': [46,139,87],
	'ForestGreen': [34,139,34],
	'Green': [0,128,0],
	'DarkGreen': [0,100,0],

	# Cyan colors	
	'Aqua': [0,255,255],
	'Cyan': [0,255,255],
	'LightCyan': [224,255,255],
	'PaleTurquoise': [175,238,238],
	'Aquamarine': [127,255,212],
	'Turquoise': [64,224,208],
	'MediumTurquoise': [72,209,204],
	'DarkTurquoise': [0,206,209],
	'LightSeaGreen': [32,178,170],
	'CadetBlue': [95,158,160],
	'DarkCyan': [0,139,139],
	'Teal': [0,128,128],

	# Blue colors	
	'LightSteelBlue': [176,196,222],
	'PowderBlue': [176,224,230],
	'LightBlue': [173,216,230],
	'SkyBlue': [135,206,235],
	'LightSkyBlue': [135,206,250],
	'DeepSkyBlue': [0,191,255],
	'DodgerBlue': [30,144,255],
	'CornflowerBlue': [100,149,237],
	'SteelBlue': [70,130,180],
	'RoyalBlue': [65,105,225],
	'Blue': [0,0,255],
	'MediumBlue': [0,0,205],
	'DarkBlue': [0,0,139],
	'Navy': [0,0,128],
	'MidnightBlue': [25,25,112],

	# Purple, violet, and magenta colors	
	'Lavender': [230,230,250],
	'Thistle': [216,191,216],
	'Plum': [221,160,221],
	'Violet': [238,130,238],
	'Orchid': [218,112,214],
	'Fuchsia': [255,0,255],
	'Magenta': [255,0,255],
	'MediumOrchid': [186,85,211],
	'MediumPurple': [147,112,219],
	'BlueViolet': [138,43,226],
	'DarkViolet': [148,0,211],
	'DarkOrchid': [153,50,204],
	'DarkMagenta': [139,0,139],
	'Purple': [128,0,128],
	'Indigo': [75,0,130],
	'DarkSlateBlue': [72,61,139],
	'SlateBlue': [106,90,205],
	'MediumSlateBlue': [123,104,238],

	# White colors	
	'White': [255,255,255],
	'Snow': [255,250,250],
	'Honeydew': [240,255,240],
	'MintCream': [245,255,250],
	'Azure': [240,255,255],
	'AliceBlue': [240,248,255],
	'GhostWhite': [248,248,255],
	'WhiteSmoke': [245,245,245],
	'Seashell': [255,245,238],
	'Beige': [245,245,220],
	'OldLace': [253,245,230],
	'FloralWhite': [255,250,240],
	'Ivory': [255,255,240],
	'AntiqueWhite': [250,235,215],
	'Linen': [250,240,230],
	'LavenderBlush': [255,240,245],
	'MistyRose': [255,228,225],

	# Gray and black colors	
	'Gainsboro': [220,220,220],
	'LightGray': [211,211,211],
	'Silver': [192,192,192],
	'DarkGray': [169,169,169],
	'Gray': [128,128,128],
	'DimGray': [105,105,105],
	'LightSlateGray': [119,136,153],
	'SlateGray': [112,128,144],
	'DarkSlateGray': [47,79,79],
	'Black': [0,0,0]
}

# Output RGB triplet as 24-bit RGB hex
def to888( rgb ):
	c = rgb[0]<<16 | rgb[1]<<8 | rgb[2]
	return '0x{:06x}'.format(c)

# Output RGB triplet as 16-bit RGB565 hex
def to565( rgb ):
	c = (rgb[0] & 0b11111000) <<8 | (rgb[1] & 0b11111100)<<3 | rgb[2]>>3
	return '0x{:04x}'.format(c)

# Generate color definitions for header file
print("\t/*")
print("\t * RGB888 colors")
print("\t */")
print("\tenum {")
for colorName in colors:
	print("\t\tRGB888_"+colorName+" = "+to888(colors[colorName])+',')
print("\t};\n")

print("\t/*")
print("\t * RGB565 colors")
print("\t */")
print("\tenum {")
for colorName in colors:
	print("\t\tRGB565_"+colorName+" = "+to565(colors[colorName])+',')
print("\t};\n")
