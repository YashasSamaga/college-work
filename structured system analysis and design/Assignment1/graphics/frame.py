from .core import Point, Size

DEFAULT_CHAR = ' '

class OverlayCell:
        def __init__(self, char = None):
            self.__char = DEFAULT_CHAR
            self.__used = False
            if char != None:      
                self.__char = char
                self.__used = True

        def set(self, char):
            self.__char = char
            self.__used = True

        def is_used(self):
            return self.__used

        def get(self):
            return self.__char

class Overlay:            
    def __init__(self, size):
        assert type(size) == Size

        self.__frame = [[]]
        self.size = size
        for i in range(size.height):
            self.__frame.append(list())
            for j in range(size.width):
                self.__frame[i].append(OverlayCell())

    def clear(self):
        for i in range(self.size.height):
            for j in range(self.size.width):
                self.__frame[i][j] = DEFAULT_CHAR 

    def set(self, point, char):
        tp = self.__coord_translate(point)
        if tp.x < self.size.height and tp.y < self.size.width:
            self.__frame[tp.x][tp.y].set(char)

    def get(self, point):
        tp = self.__coord_translate(point)
        return self.__frame[tp.x][tp.y].get()

    def is_used(self, point):
        tp = self.__coord_translate(point)
        return self.__frame[tp.x][tp.y].is_used()

    def __coord_translate(self, point):
        return Point(self.size.height - point.y - 1, point.x)

class FrameBuffer:
    def __init__(self, size):
        self.frame = [[]]
        self.size = size
        for i in range(size.height):
            self.frame.append(list())
            for j in range(size.width):
                self.frame[i].append(DEFAULT_CHAR)        

    def clear(self):
        for i in range(self.size.height):
            for j in range(self.size.width):
                self.frame[i][j] = DEFAULT_CHAR     

    def set(self, point, char):
        tp = self.__coord_translate(point)
        self.frame[tp.x][tp.y] = char

    def add_overlay(self, overlay):
        assert type(overlay) == Overlay
        assert overlay.size == self.size
        
        for i in range(overlay.size.width):
            for j in range(overlay.size.height):
                point = Point(i, j)
                if overlay.is_used(point):
                    self.set(point, overlay.get(point))

    def render(self):
        for row in self.frame:
            print("".join(row))

    def __coord_translate(self, point):
        return Point(self.size.height - point.y - 1, point.x)
