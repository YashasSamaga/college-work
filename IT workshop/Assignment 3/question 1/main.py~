from config import *
from grid import *
from spaceship import *
from alien import *
import sys
import time
import random
import select

def getlc(): # non-blocking getc
	""" non-blocking character input
	   	reads the last character if it exists in the standard input	
	"""
	ch = 0
	while select.select([sys.stdin], [], [], 0) == ([sys.stdin], [], []):
		ch = sys.stdin.read(1)
	return ch

def main():
	grid = Grid(GRID_SIZE_X, GRID_SIZE_Y)
	
	# missiles are launched from spaceship (therefore, a property of it)
	# hence, they are handeled by the spaceship object
	#
	# spaceship and alien are independent concepts
	# therefore, we handle spaceship and aliens here
	spaceship = Spaceship(grid, 0, 0, GRID_SIZE_X, GRID_SIZE_Y)
	
	# populate all the coordinates which aliens can take in `aliens_free`
	aliens_free = []
	for i in range(0, GRID_SIZE_X):
		for j in range(GRID_SIZE_Y - 2, GRID_SIZE_Y):
			aliens_free.append((i, j))		
	
	# alien objects are stored in `aliens` list
	aliens = []
	
	# keeps track of score
	score = 0
	
	# first update
	grid.update()
	print("Score: ", score)
	
	# alien hit event handler
	def alienHit(mtype, x, y):
		if mtype is MissileSlow: # hit by slow missile
			nonlocal score
			score += 1
			for alien in aliens:
				if alien.x == x and alien.y == y:
					grid.reset(x, y);				
					aliens.remove(alien)
					aliens_free.append((x, y))					
		elif mtype is MissileFast: # hit by fast missile
			for alien in aliens:
				if alien.x == x and alien.y == y:
					alien.damage(ALIEN_MHIT_LIFESPAN_INCREASE)
					
	spaceship.register_hit_handler(alienHit)	
				
	# tracks current second from epoch used by time.time()
	# default initialized to zero to trick the time tracker
	# to create an alien irrespective of the value of time.time()
	startTick = int(time.time())
	currentTick = startTick
	while True:
		newTick = int(time.time())
		if currentTick != newTick: # check if one second has passed
			# inform time-dependent objects (tick() method)
			spaceship.tick()				
			
			# check alien's lifespan
			for alien in aliens:
				if alien.tick() is 0:
					# alien's lifespan has been hit
					grid.reset(alien.x, alien.y);
					aliens.remove(alien)
					aliens_free.append((alien.x, alien.y))		
			
			# check if a new alien has to be spawned
			if (currentTick - startTick) % ALIEN_SPAWN_TIME == 0:
				pos = aliens_free[random.randrange(0, len(aliens_free))]
				aliens.append(Alien(grid, *pos, ALIEN_LIFESPAN))
				
			currentTick = newTick
			grid.force_update()
		
		# check if the user has entered a character
		# only the most recent character is processed
		# i.e: if the user types "AAD", it is equivalent to typing just "D"
		ch = getlc()
		if ch != 0:
			if ch in GAME_KEY_QUIT:
				exit()
			spaceship.onKeyPress(ch)

		# flush any pending updates to the screen
		# Note: if score changes, there will definitely be updates pending
		# 		hence, special check to just update the score is not required
		if grid.update() == True:
			print("Score: ", score)
			print("Time: ", currentTick - startTick)
	
if __name__ == "__main__": 
	main()
