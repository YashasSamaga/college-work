class Point:
    def __init__(self, x = 0, y = 0):
        self.x = int(x)
        self.y = int(y)
        
    def __eq__(self, other):
        if self.x == other.x and self.y == other.y:
               return True
        return False
        
class Size:
    def __init__(self, width = 0, height = 0):
        self.width = width
        self.height = height      

    def __eq__(self, other):
        if self.width == other.width and self.height == other.height:
               return True
        return False

class Rectangle:
    def __init__(self, top = Point(), size = Size()):
        self.min_x = top.x
        self.max_y = top.y
        self.max_x = top.x + size.width - 1
        self.min_y = top.y - size.height + 1        

    def left_top(self):
        return Point(self.min_x, self.max_y)

    def left_bottom(self):
        return Point(self.min_x, self.min_y)

    def right_top(self):
        return Point(self.max_x, self.max_y)

    def right_bottom(self):
        return Point(self.max_x, self.min_y)

    def size(self):
        return Size(self.max_x - self.min_x, self.max_y - self.min_y)

    def is_intersect(self, other):
        if self.min_x > other.max_x or self.max_x < other.min_x:
            return False
        if self.min_y > other.max_y or self.max_y < other.min_y:
            return False
        return True

    def __and__(self, other):
        if not self.is_intersect(other):
            return Rectangle()
        min_x = max(self.min_x, other.min_x)
        max_x = min(self.max_x, other.max_x)
        min_y = max(self.min_y, other.min_y)
        max_y = min(self.max_y, other.max_y)
        return Rectangle(min_x, max_x, min_y, max_y)
        
    def __or__(self, other):
        min_x = min(self.min_x, other.min_x)
        max_x = max(self.max_x, other.max_x)
        min_y = min(self.min_y, other.min_y)
        max_y = max(self.max_y, other.max_y)
        return Rectangle(min_x, max_x, min_y, max_y)