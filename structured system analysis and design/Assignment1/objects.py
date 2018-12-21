from graphics.core import *

import time, random, os

# abstract class for objects
class ILObject:
    # level = level where the object lives in
    # shape = 2D array representing object shape
    # size = size of the shape as Size()
    # position = position as Point() of the object in the scene (not window)
    # active = object is ignored everywhere if it is not active
    # draw(frame, offset) = draws object in the frame with 'offset'
    # - offset is used to transform between scene and frame coordinates
    # has_collision(): returns True of the object supports collisions
    # is_dynamic(): returns True if the object moves
    # is_interactive(): returns True if the object interacts with Mario

    def __init__(self, origin, level):
        self.level = level
        self.position = Point(origin.x, origin.y) # location in the scene
        self.size = Size(len(self.shape[0]), len(self.shape))
        self.active = True

        self.is_dynamic() and self.dynamic_reset(origin)
        self.has_collision() and self.collision_reset()
        self.is_interactive() and self.interactive_reset()

        # indirect asserts for presence of mandatory members
        self.shape = self.shape

    def reset(self):
        self.active = True
        self.is_dynamic() and self.dynamic_reset(self.origin)
        self.has_collision() and self.collision_reset()
        self.is_interactive() and self.interactive_reset()

    def draw(self, frame, offset = Point()):
        position = Point(self.position.x + offset.x, self.position.y + offset.y)
        size = self.size
        for i in range(size.height):
            for j in range(size.width):
                frame.set(Point(position.x + j, position.y + i), self.shape[size.height - i - 1][j])

    @staticmethod
    def is_dynamic(): 
        raise NotImplementedError

    @staticmethod
    def has_collision():
        raise NotImplementedError

    @staticmethod
    def is_interactive():
        raise NotImplementedError

# Name convention: [I]nterface[L]evel[O]bject[description]
# Object properties:
# static:- fixed objects
# dynamic:- movable objects
#
# coalesce:- does not collide with other objects
# collision:- collides with other objects
#
# ignores:- does not interact with the player
# interactive:- interacts with the player

# abstract class (supposed to be) for fixed objects
class ILOStatic(ILObject):
    @staticmethod
    def is_dynamic():
        return False

# abstract class for objects that move
class ILODynamic(ILObject):
    # tick(): called automatically to update position (if necessary)

    def dynamic_reset(self, origin):
        self.origin = Point(origin.x, origin.y)        
        self.velocity = Point()
        self.active = True

    def tick(self, offset):
        raise NotImplementedError

    @staticmethod
    def is_dynamic():
        return True

# abstract class (supposed to be) for objects that do not collide
class ILOCoalesce(ILObject):
    @staticmethod
    def has_collision():
        return False

# abstract internal class for overlap checking
class ILOOverlap(ILObject):
    # check if 'other' rectangle collides with the object
    def check_overlap(self, other, offset = Point()):
        point = Point(self.position.x + offset.x, self.position.y + offset.y + self.size.height - 1)
        crect = Rectangle(point, self.size)
        return crect.is_intersect(other)

# abstract class for objects that can collide
class ILOCollision(ILOOverlap):
    # material properties:
    # - friction: how fast Mario slows down
    # - elasticity: how difficult it is for Mario to jump

    def collision_reset(self):
        # indirect assertions
        self.friction = self.friction
        self.elasticity = self.elasticity    

    @staticmethod
    def has_collision():
        return True

# abstract class for objects that interact with Mario
class ILOInteractive(ILOOverlap):
    # properties:
    # - damage: damage dealt to Mario; Range: [0, 100]

    def interactive_reset(self):
        # indirect assertion
        self.damage = self.damage

    # called when Mario interacts with the object
    def interact(self, details):
        return 0

    @staticmethod
    def is_interactive():
        return True

# abstract class for objects that do not interact with Mario
class ILOIgnores(ILObject):
    @staticmethod
    def is_interactive():
        return False

# Name convention: LO[name][D=dynamic][C=collision][I=interactive]
# Mountains
class LOMountainLarge(ILOStatic, ILOCoalesce, ILOIgnores):
    shape = [[' ', ' ', ' ', '/', '¯', '¯', '\\', ' ', ' ', ' '],
             [' ', ' ', '/', ' ', ' ', ' ', ' ', '\\', ' ', ' '],
             [' ', '/', ' ', ' ', ' ', ' ', ' ', ' ', '\\', ' '],
             ['/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\\']] 

class LOMountainMedium(ILOStatic, ILOCoalesce, ILOIgnores):
    shape = [[' ', ' ', '/', '\\', ' ', ' '],
             [' ', '/', ' ', ' ', '\\', ' '],
             ['/', ' ', ' ', ' ', ' ', '\\']] 

class LOMountainSmall(ILOStatic, ILOCoalesce, ILOIgnores):
    shape = [[' ', '/', '¯', '\\', ' '],
             ['/', ' ', ' ', ' ', '\\']] 

class LOMountainRangeSmall(ILOStatic, ILOCoalesce, ILOIgnores):
    shape = [[' ', '/', '\\', '/', '\\', '/', '\\', ' '],
             ['/', ' ', ' ', ' ', ' ', ' ', ' ', '\\']] 

# Clouds
class LOCloudSmall(ILOStatic, ILOCoalesce, ILOIgnores):
    shape = [[' ',  '/', '\\', ' '],
             ['/',  ' ', ' ',  '\\'],
             ['\\', '_', '_',  '/']]

class LOCloudBig(ILOStatic, ILOCoalesce, ILOIgnores):
    shape = [[' ',  '/', '\\', '/', '\\', ' '],
             ['/',  ' ', ' ',  ' ', ' ',  '\\'],
             ['\\', '_', '_',  '_', '_',  '/']]

# Castel
class LOCastelBrick(ILOStatic, ILOCoalesce, ILOIgnores):
    shape = [['▒', '▒'],
             ['▒', '▒']]

class LOCastelFlagCI(ILOStatic, ILOCollision, ILOInteractive):
    friction = 1 # (not applicable)
    elasticity = 1 # (not applicable)
    damage = 0
    shape =  [[' ', ' ', ' ', '^'],
              [' ', ' ', ' ', '|'],
              [' ', ' ', '/', '|'],
              [' ', '/', ' ', '|'],
              ['/', '-', '-', '|'],
              [' ', ' ', ' ', '|'],
              [' ', ' ', ' ', '|'],
              [' ', ' ', ' ', '|'],
              [' ', ' ', ' ', '|'],
              [' ', ' ', ' ', '|'],
              [' ', ' ', ' ', '|'],
              [' ', ' ', ' ', '|'],
              [' ', ' ', ' ', '|'],
              [' ', ' ', ' ', '|'],
              [' ', ' ', ' ', '|']]

    def interact(self, details):
        curlevel = self.level        
        curlevel.set_state(curlevel.STATE_FINAL)
        curlevel.move_offset(3)
        curlevel.skip_ticks(curlevel.get_time_remaining() + 25)

# Bricks
# abstract class representing colliding bricks
class ILOTBrick(ILOStatic, ILOCollision):
    friction = 1
    elasticity = 1

class LOSolidBrickC(ILOTBrick, ILOIgnores):    
    shape = [['⌧', '⌧'],
             ['⌧', '⌧']]

class LOTrollBrick(ILOStatic, ILOCoalesce, ILOIgnores):
    damage = 0
    shape = [['▩', '▩'],
             ['▩', '▩']]

class LOEmptyBrickCI(ILOTBrick, ILOInteractive):
    damage = 0
    shape = [['▩', '▩'],
             ['▩', '▩']]

    def interact(self, details):
        pos = details.crect.left_top()
        pos.x = pos.x + self.level.offset
        if pos.y < self.position.y:
            if pos.x >= self.position.x or pos.x < self.position.x + self.size.width:
                os.system("aplay ./audio/smb_breakblock.wav > /dev/null 2>&1  &")
                self.active = False

class LOMysteryBrickScoreCI(ILOTBrick, ILOInteractive):
    damage = 0
    shape = [['?', '?'],
             ['?', '?']]
    
    def interact(self, details):
        pos = details.crect.left_top()
        pos.x = pos.x + self.level.offset
        if pos.y < self.position.y:
            if pos.x >= self.position.x or pos.x < self.position.x + self.size.width:
                os.system("aplay ./audio/smb_breakblock.wav > /dev/null 2>&1  &")
                self.active = False
                details.score = 100

class LOMysteryBrickUpsCI(ILOTBrick, ILOInteractive):
    damage = 0
    shape = [['?', '?'],
             ['?', '?']]
    
    def interact(self, details):
        pos = details.crect.left_top()
        pos.x = pos.x + self.level.offset
        if pos.y < self.position.y:
            if pos.x >= self.position.x or pos.x < self.position.x + self.size.width:
                os.system("aplay ./audio/smb_breakblock.wav > /dev/null 2>&1  &")
                self.active = False
                details.score = 250
                details.ups = 1

# Tunnels
# abstract class representing tunnels
class ILOTunnel(ILOStatic, ILOCollision):
    friction = 1
    elasticity = 1

class LOTunnelSmallC(ILOTunnel, ILOIgnores):
    friction = 1
    elasticity = 1
    shape =  [['=', '=', '=', '='],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|']]    

class LOTunnelMediumC(ILOTunnel, ILOIgnores):
    friction = 1
    elasticity = 1
    shape =  [['=', '=', '=', '='],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|']]   

class LOTunnelLargeC(ILOTunnel, ILOIgnores):
    friction = 1
    elasticity = 1
    shape =  [['=', '=', '=', '='],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|'],
              ['|', ' ', ' ', '|']]

class LOHorzTunnelLargeCI(ILOTunnel, ILOInteractive):
    friction = 1
    elasticity = 1
    damage = 0
    shape =  [['-', '-', '-', '-', '-', '-', '-'],
              ['[', ' ', 'W', 'A', 'Y', ' ', ' '],
              ['[', ' ', 'T', 'O', ' ', ' ', ' '],
              ['[', ' ', 'H', 'E', 'L', 'L', ' '],
              ['[', ' ', '>', '>', '>', '>', ' ']]

    def interact(self, details):
        pos = details.crect.left_bottom()
        if pos.y == self.position.y:
            os.system("aplay ./audio/smb_pipe.wav > /dev/null 2>&1 &") 
            curlevel = self.level        
            curlevel.set_state(curlevel.STATE_FINAL)
            curlevel.move_offset(1)
            curlevel.skip_ticks(curlevel.get_time_remaining() + 25)

# Bridge
class LOBridge(ILOStatic, ILOCollision, ILOIgnores):
    friction = 1
    elasticity = 2
    shape = [['=', '=', '=', '=', '=', '=']]

# Spring
class LOSpringCI(ILOStatic, ILOCollision, ILOInteractive):
    friction = 1
    elasticity = 1
    damage = 0
    shape =  [['~', '~', '~', '~'],
              ['+', '+', '+', '+'],
              ['+', '+', '+', '+'],
              ['+', '+', '+', '+']]

    def interact(self, details):
        pos = details.crect.left_bottom() 
        if pos.y >= self.position.y + self.size.height:
            details.velocity.y = 8
            details.velocity.x = 2

# Enemies
class LOTortoiseDCI(ILODynamic, ILOCollision, ILOInteractive):
    friction = 1
    elasticity = 2
    damage = 50
    shape = [[ '/', '\\'],
             [ 'O', 'O' ]]

    def tick(self, offset):        
        if (int(time.time() * 1000) % 200) > 100:
            if self.velocity.x < 0:
                self.velocity.x = self.velocity.x + 1
            elif self.velocity.x > 0:
                self.velocity.x = self.velocity.x - 1

            if self.velocity.x == 0:
                if self.position.x <= self.origin.x:
                    self.velocity.x = 3
                else:
                    self.velocity.x = -3
            
            self.position.x = self.position.x + self.velocity.x

    def interact(self, details):
        pos = details.crect.left_bottom()
        self.active = False
        if pos.y < self.position.y + self.size.height:
            details.damage = self.damage
        elif details.stage >= 0:
            os.system("aplay ./audio/smb_kick.wav > /dev/null 2>&1 &") 
            details.score = 100

class LOSmartDuckDCI(ILODynamic, ILOCollision, ILOInteractive):
    friction = 1
    elasticity = 2
    damage = 50
    shape = [[ '@', '@'],
             [ '<', '>'],
             [ '@', '@'],
             [ '/', '\\' ]]

    def tick(self, offset):        
        if (int(time.time() * 1000) % 500) > 250:
            if offset > self.position.x and (self.position.x < (self.origin.x + 10)):
                self.position.x = self.position.x + 1
            elif offset < self.position.x and (self.position.x > (self.origin.x - 10)):
                self.position.x = self.position.x - 1

            if abs(self.position.x - offset) < 5 and abs(self.position.y == self.origin.y):
                self.position.y = self.origin.y + random.randrange(0, 5)
            elif self.position.y > self.origin.y:
                self.position.y = self.position.y - 1

    def interact(self, details):
        details.damage = self.damage

# Collectables
class LOCoinI(ILOStatic, ILOCoalesce, ILOInteractive):
    damage = 0
    shape = ['$']
    
    def interact(self, details):
        os.system("aplay ./audio/smb_coin.wav > /dev/null 2>&1  &")
        self.active = False
        details.score = 25

objmap = {
    # static
    "B0" : LOMountainLarge,
    "B1" : LOMountainMedium,
    "B2" : LOMountainSmall,
    "B3" : LOMountainRangeSmall,
    "C0" : LOCloudSmall,
    "C1" : LOCloudBig,
    "B4" : LOCastelBrick,
    "B5" : LOBridge,
    "S0" : LOSpringCI,
    "C2" : LOCoinI,
    "B6" : LOTrollBrick,
    "H0" : LOHorzTunnelLargeCI,

    # interactive
    "X0" : LOMysteryBrickScoreCI,
    "X1" : LOEmptyBrickCI,
    "X2" : LOSolidBrickC,
    "X3" : LOMysteryBrickUpsCI,
    "E1" : LOTortoiseDCI,
    "E2" : LOSmartDuckDCI,
    "T0" : LOTunnelSmallC,
    "T1" : LOTunnelMediumC,
    "T2" : LOTunnelLargeC,
    "F0" : LOCastelFlagCI
}

class LOGroundC(ILOStatic, ILOCollision, ILOIgnores):
    friction = 1
    elasticity = 1
    shape = [[]]

class LORoofC(ILOStatic, ILOCollision, ILOIgnores):
    friction = 1
    elasticity = 2 # (not applicable)
    shape = [[]]

class LOEdgeCI(ILOStatic, ILOCollision, ILOInteractive):
    friction = 1
    elasticity = 0
    shape = [[]]
    damage = 100

    def interact(self, details):
        details.damage = self.damage
