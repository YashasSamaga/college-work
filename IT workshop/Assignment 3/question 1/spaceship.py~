from config import *
from grid import *
from missile import *

class Spaceship:
	def __init__(self, grid, initialX, initialY, maxX, maxY):
		assert(initialX < maxX)
		assert(initialY < maxY)
		self.grid = grid
		self.x = initialX
		self.y = initialY
		self.maxX = maxX
		self.maxY = maxY
		self.icon = SPACESHIP_ICON
		
		self.hitfunc = lambda x, y, z : 0
		self.checkfunc = lambda x, y : 0
		self.missiles = []
		self.grid.set(self.x, self.y, self.icon)	
		
	def __del__(self):
		self.grid.reset(self.x, self.y)
	
	def register_hit_handler(self, f):
		self.hitfunc = f
	
	def onKeyPress(self, key):
		if key in SPACESHIP_KEY_LEFT and self.x > 0:
			self.grid.reset(self.x, self.y)
			self.x -= 1
			self.grid.set(self.x, self.y, self.icon)
		elif key in SPACESHIP_KEY_RIGHT and self.x + 1 < self.maxX:
			self.grid.reset(self.x, self.y)
			self.x += 1	
			self.grid.set(self.x, self.y, self.icon)
		elif key in SPACESHIP_KEY_SLOW_MISSILE:
			for missile in self.missiles:
				if missile.x == self.x and missile.y == self.y + 1:
					return 
			self.missiles.append(MissileSlow(self.grid, self.x, self.y + 1, self.maxX, self.maxY))
		elif key in SPACESHIP_KEY_FAST_MISSILE:
			for missile in self.missiles:
				if missile.x == self.x and missile.y == self.y + 1:
					return 
			self.missiles.append(MissileFast(self.grid, self.x, self.y + 1, self.maxX, self.maxY))
	
	def tick(self):
		for missile in self.missiles:
			res = missile.tick()
			if res is False:
				self.missiles.remove(missile)
			if type(res) == tuple:
				self.hitfunc(type(missile), *res)
				self.missiles.remove(missile)
