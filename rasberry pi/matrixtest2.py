#!/usr/bin/python

# A more complex RGBMatrix example works with the Python Imaging Library,
# demonstrating a few graphics primitives and image loading.
# Note that PIL graphics do not have an immediate effect on the display --
# image is drawn into a separate buffer, which is then copied to the matrix
# using the SetImage() function (see examples below).
# Requires rgbmatrix.so present in the same directory.

# PIL Image module (create or load images) is explained here:
# http://effbot.org/imagingbook/image.htm
# PIL ImageDraw module (draw shapes to images) explained here:
# http://effbot.org/imagingbook/imagedraw.htm

import Image
import ImageDraw
import time
from rgbmatrix import Adafruit_RGBmatrix

# Rows and chain length are both required parameters:
matrix = Adafruit_RGBmatrix(32,2,3)

# Bitmap example w/graphics prims
image = Image.new("1", (32, 32)) # Can be larger than matrix if wanted!!
draw  = ImageDraw.Draw(image)    # Declare Draw instance before prims
# Draw some shapes into image (no immediate effect on matrix)...
draw.rectangle((0, 0, 31, 31), fill=0, outline=1)
draw.line((0, 0, 31, 31), fill=1)
draw.line((0, 31, 31, 0), fill=1)
# Then scroll image across matrix...
for n in range(-32, 60): # Start off top-left, move off bottom-right
	matrix.Clear()
	# IMPORTANT: *MUST* pass image ID, *NOT* image object!
	matrix.SetImage(image.im.id, n, n)
	time.sleep(0.05)

# 8-bit paletted GIF scrolling example
image = Image.open("VDuedC0.png")
image.load()          # Must do this before SetImage() calls
matrix.Fill(0xffffff) # Fill screen to sky color
for n in range(96, -image.size[0], -1): # Scroll R to L
	matrix.SetImage(image.im.id, n, 0)
	time.sleep(0.025)

# 24-bit RGB scrolling example.
# The adafruit.png image has a couple columns of black pixels at
# the right edge, so erasing after the scrolled image isn't necessary.
matrix.Clear()

sprites = []

sprites.append(Image.open("megaman-sprites/1.png"))
sprites.append(Image.open("megaman-sprites/2.png"))
sprites.append(Image.open("megaman-sprites/3.png"))
sprites.append(Image.open("megaman-sprites/4.png"))
sprites.append(Image.open("megaman-sprites/5.png"))
sprites.append(Image.open("megaman-sprites/6.png"))
sprites.append(Image.open("megaman-sprites/7.png"))

matrix.Fill(0xffffff)

for image in sprites:
	image.load()
while 1:
	for image in sprites:
		matrix.Fill(0xffffff)
		matrix.SetImage(image.im.id, 20, 0)
		time.sleep(0.08)
