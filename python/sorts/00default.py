from graphics import *

width = 400
height = 400
center = Point(width/2, height/2)
black = color_rgb(0, 0, 0)

canvas = GraphWin(title = "canvas", width=width, height=height)

while canvas.checkKey() != 'x': 
    
    rec = Rectangle(Point(180,height), Point(220, 200))
    rec.setFill(black)
    rec.draw(canvas)
    cir = Circle(center, 35)
    cir.setFill(black)
    cir.draw(canvas)

    canvas.flush()

canvas.close()