from glob import glob
from os import path
from PIL import Image

###
### Take a source image and concert it into a bunch of different
### pixel formats for preview purposes.
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

# Step through all image files in the folder and create a new image
# for preview purposes. The new image is twice the width and twice
# the height, and contains the source image and 3 variants:
# 
# ARGB 8 888|ARGB 8 565
# ----------+----------
# ARGB 4 444|ARGB 6 666
#
# In practice the pixels are converted to the destination format (e.g.
# 444) and then expanded back to 888 format.
# 
# The preview image is saved as a PNG with the same filename, but with
# 'preview' prepended.


# Function to remap values
def remap6to8(x):
  return (x << 2) | (x >> 4)

def remap5to8(x):
  return (x << 3) | (x >> 2)

def remap4to8(x):
  return (x << 4) | x			

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
	name = fileparts.pop(0)
	extn = fileparts.pop().lower();

	# skip any preview images
	if name=='preview': continue
	
	# any remaining parts are options
	options = {}
	for opstr in fileparts:
		options[opstr[:1]] = opstr[2:]
	
	# Start the output
	outstr = '';

	# load the image
	im = Image.open(file)
	
	# Check if the image has alpha
	alpha = im.mode == 'RGBA'
	
	# Some useful messages to console
	print()
	print('Processing',filename,'(image)')
	print('  Source image mode:',im.mode)
	
	# Get image dimensions
	width, height = im.size

	# Stats
	print('  RGBA 8888:',(width*height*4),'bytes') #32-bit
	print('  RGBA 8565:',(width*height*3),'bytes') #24-bit
	print('  RGBA 6666:',(width*height*3),'bytes') #24-bit
	print('  RGBA 4444:',(width*height*2),'bytes') #16-bit
	
	# Create destination image
	preview = Image.new('RGBA', (width*2,height*2), (0,0,0,0))

	# Copy source image to the top-left
	preview.paste(im, (0, 0, width, height))

	# step pixels in the image
	a = 255
	for y in range(height):
		for x in range(width):
			# grab source pixel
			if alpha:
				r,g,b,a = im.getpixel((x,y))
			else:
				r,g,b = im.getpixel((x,y))
			# 565 - top-right
			r1 = remap5to8(r>>3)
			g1 = remap6to8(g>>2)
			b1 = remap5to8(b>>3)
			a1 = a
			preview.putpixel((width+x,y),(r1,g1,b1,a1))
			# 444 - bottom-left
			r2 = remap4to8(r>>4)
			g2 = remap4to8(g>>4)
			b2 = remap4to8(b>>4)
			a2 = remap4to8(a>>4)
			preview.putpixel((x,height+y),(r2,g2,b2,a2))
			# 666 - bottom-right
			r3 = remap6to8(r>>2)
			g3 = remap6to8(g>>2)
			b3 = remap6to8(b>>2)
			a3 = remap6to8(a>>2)
			preview.putpixel((width+x,height+y),(r3,g3,b3,a3))
				
	# Output preview
	preview.save('preview.'+name+'.png', 'PNG')

# If called directly as as script
if __name__ == '__main__':
	# Wait before exit for user to read messages
	print()
	input("Press enter to close")