from config import *

class Alien:
	def __init__(self, grid, x, y, lifespan):
		self.x = x
		self.y = y
		self.icon = ALIEN_ICON
		self.lifespan = lifespan
		self.grid = grid
		self.grid.set(self.x, self.y, self.icon)

	def __del__(self):
		self.grid.reset(self.x, self.y)

	def damage(self, dmg):
		self.lifespan += dmg
		self.icon = ALIEN_DAMAGED_ICON
		self.grid.set(self.x, self.y, self.icon)
		
	def tick(self):
		self.lifespan -= 1
		if self.lifespan == 0:
			self.grid.reset(self.x, self.y)
		return self.lifespan
		
