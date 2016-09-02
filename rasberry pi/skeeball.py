#!/usr/bin/python
import time
import serial
import Image
import ImageFont
import ImageDraw
from rgbmatrix import Adafruit_RGBmatrix


class Skeeball:
	score = 0
	highscore = 0
	balls = 0
	BUTTON = { 
		'B1000L': int("0000",16),
		'B1000R': int("0001",16),
		'B500': int("0002",16),
		'B400': int("0004",16),
		'B300': int("0008",16),
		'B200': int("0010",16),
		'B100': int("0020",16),
		'BRET': int("0040",16), 
		'SELECT': int("0080",16),
		'START': int("0100",16),
		'SCORED': int("003F",16),
		'ANY': int("FFFF",16)
	}
	MODE = {
		'ATTRACT': 0,
		'POST': 1,
		'GAME': 2
	}

	def __init__(self):
		self.__initSerial()
		self.game_mode = self.MODE['ATTRACT']
		self.matrix = Adafruit_RGBmatrix(32,2,3)
		self.image = Image.new("RGB", (96, 64))
		self.draw  = ImageDraw.Draw(self.image)
		font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeSerif.ttf", 14)
		self.draw.text((20, 10), "LOADING",font=font,fill=(255,60,5))
		self.draw.text((18, 30), "SKEEBALL",font=font,fill=(255,60,5))
		self.matrix.Clear()
		self.matrix.SetImage(self.image.im.id,0,0)
		time.sleep(6)


	def __initSerial(self):
		try:
			self.serial = serial.Serial(
			    port='/dev/arduino',
			    baudrate=9600,
			    parity=serial.PARITY_NONE,
			    stopbits=serial.STOPBITS_ONE,
			    bytesize=serial.EIGHTBITS,
			    timeout=.1,
			    write_timeout=.1,
			    rtscts=False,
			    dsrdtr=False
			)
		except:
			self.serial=None

	def __updateButtons(self):
		self.serial.write("B\n")
		buttons = self.serial.read(2)
		self.buttons = int(buttons.encode('hex'), 16)

	def __releaseBalls(self):
		self.serial.write("R\n")

	def __isPressed(self,button):
		return self.buttons & button

	def __start(self):
		score = 0
		balls = 6
		self.game_mode = self.MODE['GAME']
		self.__releaseBalls()

	def __update(self):
		self.__updateButtons()
		if self.game_mode == self.MODE['ATTRACT']:
			if self.__isPressed(self.BUTTON['START']):
				self.__start()
				return
		if self.game_mode == self.MODE['POST']:
			self.__doPost()
		if self.game_mode == self.MODE['GAME']:
			self.__doGame()

	def __doGame(self):
		if balls > 0:
			if self.__isPressed(self.BUTTON['B1000L']) or self.__isPressed(self.BUTTON['B1000R']):
				score += 1000
			if self.__isPressed(self.BUTTON['B500']):
				score += 500
			if self.__isPressed(self.BUTTON['B400']):
				score += 400
			if self.__isPressed(self.BUTTON['B300']):
				score += 300
			if self.__isPressed(self.BUTTON['B200']):
				score += 200
			if self.__isPressed(self.BUTTON['B100']):
				score += 100
			if self.__isPressed(self.BUTTON['BRET']):
				balls-=1
		else:
			self.game_mode = self.MODE['POST']
			self.__startPost()


	def __startPost(self):
		return


game = Skeeball()
