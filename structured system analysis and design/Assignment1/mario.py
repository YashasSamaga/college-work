from graphics.frame import *
from graphics.drawing import *
from graphics.core import *

from level import *

import os

# class representing an interaciton between Mario and an object
class Interaction:
    def __init__(self, crect, cur_velocity, stage):
        # shared information
        self.crect = crect
        self.cur_velocity = cur_velocity   
        self.stage = stage

        # changes due to interaction
        self.score = 0 # change in score
        self.ups = 0 # 1 = give life
        self.damage = 0 # amount of damage
        self.velocity = Point() # change in velocity

class Mario:
    BABY_MARIO = 0 # can just walk
    TEEN_MARIO = 1 # can crush enemies
    ADULT_MARIO = 2 # can fire bombs (TODO)

    ACTION_JUMP = 0
    ACTION_RIGHT = 1
    ACTION_LEFT = 2

    STATE_RIGHT = 0 # right facing mario
    STATE_LEFT = 1 # left facing mario

    __mario_shapes = [
                      [ # baby mario
                       [
                        ['@'],
                        ['@'],
                        ['@']
                       ],
                       [
                        ['@'],
                        ['@'],
                        ['@']
                       ]
                      ], 
                      [ # teen mario
                       [
                        ['⧭'],
                        ['\\'],
                        ['/']
                       ],
                       [
                        ['⧭'],
                        ['/'],
                        ['\\']
                       ]
                      ],
                      [ # adult mario
                       [
                        ['█', '▅'], 
                        ['┗', '┛'],
                        ['/', '\\'],
                        ['⧺', '⧺']
                       ],
                       [
                        ['▅', '█'], 
                        ['┗', '┛'],
                        ['/', '\\'],
                        ['⧺', '⧺']
                       ]
                      ]
                     ]

    def __init__(self, point = Point()):
        self.reset(point)

    def reset(self, left_bottom = Point(), curlevel = None, initial_score = 0):
        self.point = left_bottom
        self.velocity = Point()        
        self.stage = self.BABY_MARIO
        self.state = self.STATE_RIGHT
        self.score = initial_score
        self.dead = False
        self.__curlevel = curlevel
        self.__tick = 0
 
    def __process_overlaps(self, overlaps):
        collision = False
        wildcard = False
        crect = Rectangle(Point(self.point.x, self.point.y + self.size().height - 1), self.size())
        for obj in overlaps:
            collision = collision or obj.has_collision()     
            if obj.is_interactive():
                deltas = Interaction(crect, self.velocity, self.stage)
                obj.interact(deltas)
                self.score = self.score + deltas.score
                self.damage(deltas.damage)
                if deltas.ups:
                    os.system("aplay ./audio/smb_powerup.wav > /dev/null 2>&1 &")                    
                    self.levelup()
                if deltas.velocity.x or deltas.velocity.y:
                    self.velocity.x = self.velocity.x + deltas.velocity.x
                    self.velocity.y = self.velocity.y + deltas.velocity.y    
                    wildcard = True
        return (wildcard == False) and collision

    def tick(self):        
        self.__tick = self.__tick + 1

        curlevel = self.__curlevel
        if curlevel.get_state() == curlevel.STATE_FINAL:
            self.score = self.score + 20
            if self.__tick % 5 == 0:
                os.system("aplay ./audio/smb_coin.wav > /dev/null 2>&1 &")
            return

        if curlevel.get_state() == curlevel.STATE_COMPLETE:
            return

        # deal with objects which moved towards the player
        top_left = Point(self.point.x, self.point.y + self.size().height - 1)
        crect = Rectangle(top_left, self.size())                 
        overlaps = curlevel.get_overlaps(crect)
        if self.__process_overlaps(overlaps):
            self.velocity.x = 0
            self.velocity.y = 0

        # horizontal and vertical motion happen in separate ticks
        if self.__tick % 2 == 0:
            # update horizontal parameters
            for i in range(abs(self.velocity.x)):
                if self.velocity.x > 0:
                    crect = Rectangle(Point(top_left.x + 1, top_left.y), self.size())                 
                    overlaps = curlevel.get_overlaps(crect)
                    if self.__process_overlaps(overlaps):
                        self.velocity.x = 0
                        break
                    curlevel.move_offset(1)
                else:
                    crect = Rectangle(Point(top_left.x - 1, top_left.y), self.size()) 
                    overlaps = curlevel.get_overlaps(crect)
                    if self.__process_overlaps(overlaps):
                        self.velocity.x = 0
                        break
                    curlevel.move_offset(-1)

            # friction is applicable only when mario is on a surface
            # friction dominates drag (random physics!)
            # i.e. drag effects come into play when there is no friction
            crect = Rectangle(Point(self.point.x, self.point.y - 1), Size(self.size().width, 1))
            overlaps = curlevel.get_overlaps(crect)
            change = curlevel.drag
            if len(overlaps) > 0 and overlaps[0].has_collision():
                change = overlaps[0].friction

            # change velocities and set facing direction       
            if self.velocity.x > 0:
                self.velocity.x = max(0, self.velocity.x - change)
                self.state = self.STATE_RIGHT
            elif self.velocity.x < 0:
                self.velocity.x = min(self.velocity.x + change, 0)
                self.state = self.STATE_LEFT
        else:
            # update vertical parameters
            for i in range(abs(self.velocity.y)):
                if self.velocity.y > 0:
                    crect = Rectangle(Point(top_left.x, top_left.y + 1), self.size())             
                    overlaps = curlevel.get_overlaps(crect)
                    if self.__process_overlaps(overlaps):
                        self.velocity.y = 0
                        break
                    self.point.y = self.point.y + 1
                    top_left = Point(self.point.x, self.point.y + self.size().height - 1)
                else:
                    crect = Rectangle(Point(top_left.x, top_left.y - 1), self.size())         
                    overlaps = curlevel.get_overlaps(crect)
                    if self.__process_overlaps(overlaps):
                        self.velocity.y = 0
                        break
                    self.point.y = self.point.y - 1
                    top_left = Point(self.point.x, self.point.y + self.size().height - 1)

            # acclerate fall due to gravity until Mario hits terminal velocity
            if self.velocity.y > -3:
                self.velocity.y = self.velocity.y - curlevel.gravity                 

    def do_action(self, action):
        curlevel = self.__curlevel
        crect = Rectangle(Point(self.point.x, self.point.y - 1), Size(self.size().width, 1))
        overlaps = curlevel.get_overlaps(crect)
        elasticity = 0
        if curlevel.drag > 0:
            elasticity = 2
        if len(overlaps) > 0 and overlaps[0].has_collision():
            elasticity = overlaps[0].elasticity   
        if elasticity: 
            if action == self.ACTION_JUMP:
                if curlevel.drag == 0:
                    os.system("aplay ./audio/smb_jump-small.wav > /dev/null 2>&1  &")
                self.velocity.y = 4 // elasticity
            elif action == self.ACTION_RIGHT:
                self.velocity.x = min(self.velocity.x + 2, 4)
            elif action == self.ACTION_LEFT:
                self.velocity.x = max(self.velocity.x - 2, -4)

    def damage(self, damage):
        prev_stage = self.stage
        if damage == 100:
            self.stage = self.stage - 3
        elif damage > 50:
            self.stage = self.stage - 2
        elif damage > 0:
            self.stage = self.stage - 1
                   
        if self.stage < 0:
            os.system("aplay ./audio/smb_mariodie.wav > /dev/null 2>&1  &")
            self.stage = prev_stage
            self.dead = True       

    def levelup(self):
        self.stage = self.stage + 1
        if self.stage > self.ADULT_MARIO:
            self.stage = self.ADULT_MARIO

    def size(self):
        shape = self.__mario_shapes[self.stage][self.state]
        return Size(len(shape[0]), len(shape))

    def draw(self, overlay):
        shape = self.__mario_shapes[self.stage][self.state]
        point = self.point
        size = self.size()
        for i in range(size.height):
            for j in range(size.width):
                overlay.set(Point(point.x + j, point.y + i), shape[size.height - i - 1][j])

        if self.dead:
            if self.stage == self.BABY_MARIO or self.stage == self.TEEN_MARIO:
                putText(overlay, "R.I.P", Point(point.x - 2, point.y + size.height))
            else:
                putText(overlay, "DEAD", Point(point.x - 1, point.y + size.height))