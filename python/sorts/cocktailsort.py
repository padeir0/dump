import mArray, time
from graphics import *

canvWidth = 400
canvHeight = 400
center = Point(canvWidth/2, canvHeight/2)
canvas = GraphWin(title = "canvas", width=canvWidth, height=canvHeight)

black = color_rgb(0, 0, 0)
red = color_rgb(150, 20, 20)
blue = color_rgb(20, 20, 150)
green = color_rgb(20, 150, 20)

arrayLenght = 400
pillarWidth = canvWidth / arrayLenght
heightFactor = canvHeight / arrayLenght
a = mArray.unordArray(arrayLenght)
sorted = False
foward = 0      # number of foward loops
backward = 0    # number of backward loops
c = 0 # number of comparisons

class Pillar(object):
    def __init__(self, value, index):
        self.value = value
        self.index = index
        self.p1 = Point(index * pillarWidth, canvHeight)
        self.p2 = Point((index +1) * pillarWidth, canvHeight - value * heightFactor)
        self.pil = Rectangle(self.p1, self.p2)

    def draw(self):
        self.pil.setFill(black)
        self.pil.draw(canvas)

    def move(self, relativeIndex):
        self.index = relativeIndex
        self.pil.move(self.index * pillarWidth, 0)

    def color(self, color):
        self.pil.setFill(color)
        self.pil.setOutline(color)


pillars = []

for index, item in enumerate(a):
    pillars.append(Pillar(item, index))
    pillars[index].draw()

while canvas.checkKey() != 'x':
    if not sorted:
        sorted = True
        for i in range(backward, arrayLenght - 1 - foward):
            if pillars[i].value > pillars[i+1].value:
                backup = pillars[i]
                pillars[i] = pillars[i+1]
                pillars[i+1] = backup

                pillars[i].move(-1)
                pillars[i+1].move(1)

                sorted = False
                canvas.flush()
            c += 1
        foward += 1
        pillars[arrayLenght - foward].color(green)

        for i in range(arrayLenght - 1 - foward, backward, -1):
            if pillars[i].value < pillars[i-1].value:
                backup = pillars[i]
                pillars[i] = pillars[i-1]
                pillars[i-1] = backup

                pillars[i].move(1)
                pillars[i-1].move(-1)

                sorted = False
                canvas.flush()
            c += 1
        backward += 1
        pillars[backward - 1].color(blue)

print("number of loops: ", foward + backward)
print("number of coparisons: ", c)

canvas.close()