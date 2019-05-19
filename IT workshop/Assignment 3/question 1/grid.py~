import os
from config import *

class Grid:
	def __init__(self, rows, cols):
		self.rows = rows
		self.cols = cols
		
		self.__require_update = True
		
		self.frame_rows = ((2 * GRID_CELL_PADDING_Y + 1) * self.rows) + 2
		self.frame_cols = ((2 * GRID_CELL_PADDING_X + 1) * self.cols) + 4
		
		self.frame = []
		for i in range(self.frame_rows):
			self.frame.append([])
			for j in range(self.frame_cols):
				self.frame[i].append(GRID_DEFAULT_CHARACTER)				
				
		for i in range(self.frame_rows):
			self.frame[i][0] = self.frame[i][-1] = GRID_BORDER_Y
			self.frame[i][0] = self.frame[i][-1] = GRID_BORDER_Y
		
		self.frame[0] = self.frame[-1] = [GRID_BORDER_X] * self.frame_cols

	def force_update(self):
		self.__require_update = True

	def update(self):
		if self.__require_update is True:
			os.system("clear")
			for row in self.frame:
				print(''.join(row))
			self.__require_update = False
			return True
		return False
			
	def set(self, x, y, char):
		assert(x < self.cols)
		assert(y < self.rows)
		frame_x = x * (2 * GRID_CELL_PADDING_X + 1) + 3
		frame_y = self.frame_rows - (y * (2 * GRID_CELL_PADDING_Y + 1) + 3) + 1
		self.frame[frame_y][frame_x] = char
		self.__require_update = True
	
	def reset(self, x, y):
		self.set(x, y, GRID_DEFAULT_CHARACTER)
		self.__require_update = True
	
	def get(self, x, y):
		assert(x < self.cols)
		assert(y < self.rows)
		frame_x = x * (2 * GRID_CELL_PADDING_X + 1) + 3
		frame_y = self.frame_rows - (y * (2 * GRID_CELL_PADDING_Y + 1) + 3) + 1
		return self.frame[frame_y][frame_x]	
