from .frame import Overlay
from .core import Point

def putText(overlay, text, point):
    for pos in range(len(text)):
        overlay.set(Point(point.x + pos, point.y), text[pos])

def putRectange(overlay, top_left, size, corner = True, fill = None):
    x = top_left.x
    y = top_left.y
    
    for i in range(size.width):
        overlay.set(Point(x + i, y), '━')
        overlay.set(Point(x + i, y - size.height + 1), '━')
    for i in range(1, size.height - 1):
        overlay.set(Point(x, y - i), '┃')
        overlay.set(Point(x + size.width - 1, y - i), '┃')        

    if corner == True:
        overlay.set(Point(x, y), '┏')
        overlay.set(Point(x + size.width - 1, y), '┓')
        overlay.set(Point(x, y - size.height + 1), '┗')
        overlay.set(Point(x + size.width - 1, y - size.height + 1), '┛')

    if fill != None:
        for i in range(size.width):
            for j in range(size.height):
                overlay.set(Point(x + i, y - j), fill)