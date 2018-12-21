from graphics.core import *
from graphics.frame import *
from objects import *

import time, os

LEVEL_FILE_IGNORE_CHARACTER = '*'
LEVEL_FILE_GROUND_CHARACTER = '#'
LEVEL_GROUND_CHARACTER = '█'

# Level
class Level:
    STATE_IN_PROGRESS = 0 # level being played
    STATE_FINAL = 1 # giving rewards for completion
    STATE_COMPLETE = 2 # everything complete

    def __init__(self, world, level, window_size):
        self.world = world
        self.level = level
        self.window_size = window_size

        # read level configuration
        self.config = { "time" : "600",
                        "next_world" : "-1",
                        "next_level" : "-1",
                        "initial_offset" : "0",
                        "fill" : ' ',
                        "gravity" : "1",
                        "drag" : "0" }

        length = 0
        with open("data/worlds/" + str(world) + "/" + str(level) + "/meta") as lfile:
            for line in lfile:
                fields = line.split()
                self.config[fields[0]] = fields[1]

        # OPTIMIZATION:
        # objects which do not collide, interact and are static
        # are stored in 'static_scene'; otherwise, they are put into
        # 'objects'
        self.objects = []
        self.static_scene = []

        with open("data/worlds/" + str(world) + "/" + str(level) + "/scene") as lfile:
            for line in lfile:                
                row = list(line.rstrip())
                length = max(length, len(row))
                self.static_scene.append(row)

        for row in self.static_scene:
            row.extend([' '] * (length - len(row)))

        height = len(self.static_scene)
        assert height == window_size.height

        for y in range(height):
            row = self.static_scene[y]
            for x in range(length):
                # '*' are ignored
                # '#' are considered to be ground
                if row[x] == LEVEL_FILE_IGNORE_CHARACTER:
                    row[x] = ' '
                elif row[x] == LEVEL_FILE_GROUND_CHARACTER:
                    row[x] = LEVEL_GROUND_CHARACTER

                if row[x].isalpha():
                    assert x + 1 < length
                    obj_t = objmap[row[x] + row[x + 1]]
                    position = Point(x, height - y - 1)
                    if obj_t.is_dynamic() or obj_t.has_collision() or obj_t.is_interactive():
                        row[x] = row[x + 1] = ' '
                        self.objects.append(obj_t(position, self))
                    else:
                        obj_t(position, self).draw(self)

        for y in range(height):
            for x in range(length):
                if self.static_scene[y][x] == ' ':
                    self.static_scene[y][x] = self.config["fill"]                 

    def reset(self):
        self.skip = 0
        self.end_time = time.time() + int(self.config["time"])
        self.offset = int(self.config["initial_offset"])        
        self.state = self.STATE_IN_PROGRESS

        self.gravity = int(self.config["gravity"])
        self.drag = int(self.config["drag"])

        for obj in self.objects:
            obj.reset()

    def get_state(self):
        return self.state    
    def set_state(self, state):
        self.state = state

    # set/get points in the static background
    def set(self, point, char):
        self.static_scene[self.size().height - point.y - 1][point.x] = char
    def get(self, point):
        return self.static_scene[self.size().height - point.y - 1][point.x]

    def skip_ticks(self, ticks):
        self.skip = ticks

    def size(self):
        return Size(len(self.static_scene[0]), len(self.static_scene))   

    def tick(self):
        if self.skip:            
            self.skip = self.skip - 1
            return

        if self.get_state() == self.STATE_FINAL:
            self.set_state(self.STATE_COMPLETE)

        for obj in self.objects:
            if obj.is_dynamic():
                obj.tick(self.offset + self.window_size.width/2)

    def move_offset(self, delta):
        self.offset = self.offset + delta
        self.offset = max(self.offset, 0)
        self.offset = min(self.offset, self.size().width)

    def get_time_remaining(self):
        return int(self.end_time - time.time())

    def get_overlaps(self, crect):
        if crect.min_y < 0:
            return [LOEdgeCI(Point(self.offset + crect.min_x, crect.min_y), self)]

        if crect.max_y >= self.size().height - 1:
            return [LORoofC(Point(crect.min_x, crect.max_y), self)]

        overlaps = []
        for obj in self.objects:
            if obj.active:
                if obj.check_overlap(crect, Point(-self.offset, 0)):
                    overlaps.append(obj)

        if self.get(Point(self.offset + crect.min_x, crect.min_y)) == LEVEL_GROUND_CHARACTER:
            overlaps.append(LOGroundC(Point(self.offset + crect.min_x, crect.min_y), self))     

        if self.get(Point(self.offset + crect.min_x, crect.max_y)) == LEVEL_GROUND_CHARACTER:
            overlaps.append(LOGroundC(Point(self.offset + crect.min_x, crect.max_y), self))

        return overlaps

    def render(self, overlay):
        size = self.size()
        assert overlay.size.height == size.height
        assert overlay.size.width <= size.width
        
        offset = min(self.offset, size.width - overlay.size.width)          
        for x in range(offset, offset + overlay.size.width):
            for y in range(size.height):
                overlay.set(Point(x - offset, size.height - y - 1), self.static_scene[y][x])

        for obj in self.objects:
            if obj.active:
                if offset < obj.position.x and obj.position.x < (offset + overlay.size.width):
                    obj.draw(overlay, Point(-offset, 0))