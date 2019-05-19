from config import *
from grid import *

class Missile:
	def __init__(self, grid, icon, x, y, maxX, maxY, stepX, stepY):
		self.grid = grid
		self.icon = icon	
		self.x = x
		self.y = y
		self.maxX = maxX
		self.maxY = maxY
		self.stepX = stepX
		self.stepY = stepY		
		self.grid.set(x, y, self.icon)
		
	def __del__(self):
		if self.y < self.maxY and self.x < self.maxX:
			self.grid.reset(self.x, self.y)
		
	def tick(self):		
		for i in range(self.y, self.y + self.stepY + 1):
			if i < self.maxY:
				next = self.grid.get(self.x, i)
				if i < self.maxY and (next == ALIEN_ICON or next == ALIEN_DAMAGED_ICON):				
					self.grid.reset(self.x, self.y)
					self.y = self.maxY
					return (self.x, i)
		
		self.grid.reset(self.x, self.y)	
		self.x += self.stepX
		self.y += self.stepY
		if self.y >= self.maxY or self.x >= self.maxX:
			return False
		
		self.grid.set(self.x, self.y, self.icon)
		return True
		
class MissileSlow(Missile):
	def __init__(self, grid, x, y, maxX, maxY):
		super(MissileSlow, self).__init__(grid, MISSILE_SLOW_ICON, x, y, maxX, maxY, MISSILE_SLOW_SPEED_X, MISSILE_SLOW_SPEED_Y)
		
class MissileFast(Missile):
	def __init__(self, grid, x, y, maxX, maxY):
		super(MissileFast, self).__init__(grid, MISSILE_FAST_ICON, x, y, maxX, maxY, MISSILE_FAST_SPEED_X, MISSILE_FAST_SPEED_Y)
