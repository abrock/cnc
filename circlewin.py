import gtk
import threading
import time
import math
gtk.gdk.threads_init()

class main(dict):
	def __init__(self, window):
		self.window = window
		self.count = 0 #nur fuer den kreis, kann raus
		self.reverse = False #nur fuer den kreis, kann raus
		self.x = 0
		self.y = 0
		self.xV = 0
		self.yV = 50
		self.xA = 0
		self.yA = 0
                self.xMax = 250
		self.yMax = 250
		self.xDest = 100
		self.yDest = 100

	def calculateAcc(self):
		# Aktuelle Abweichung von den Zielkoordinaten berechnen.
		yE = self.yDest - self.y
		xE = self.xDest - self.x

		self.yA = yE - self.yV
		self.xA = xE - self.xV


	def run(self):
		#alles nur fuer den kreis
		winkel = 2 * math.pi / 500
                step = 0.01
		while True:
			self.calculateAcc();

			self.y += step*self.yV;
			self.x += step*self.xV;
			self.y += step*step*self.yA/2
			self.y += step*step*self.xA/2
			if self.y > self.yMax:
				self.y = self.yMax-(self.y-self.yMax)
				self.yV = -self.yV
			if self.x > self.xMax:
				self.x = self.xMax-(self.x-self.xMax)
				self.xV = -self.xV
			if self.y < 0:
				self.y = -self.y
				self.yV = -self.yV
			if self.x < 0:
				self.x = -self.x
				self.xV = -self.xV

			self.yV += step*self.yA
			self.xV += step*self.xA
			
			window.move(self.x, self.y);
			time.sleep(step)

class window(gtk.Window):
	def __init__(self):
		gtk.Window.__init__(self)

	def run(self):
		self.layout = gtk.Layout()
		self.add(self.layout)

		self.image = gtk.Image()
		self.image.set_from_file("kreis.jpg")
		self.layout.put(self.image, -10, -10)
		
		self.show_all()
		gtk.main()
		
	def move(self, *args):
		self.layout.remove(self.image)
		self.layout.put(self.image, *args)
		self.image.show()
		
if __name__ == '__main__':
	window = window()
	windowThread = threading.Thread(target=window.run)
	windowThread.start()
	main = main(window)
	mainThread = threading.Thread(target=main.run)
	mainThread.start()
