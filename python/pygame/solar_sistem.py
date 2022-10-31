import pygame, math, random

pygame.init()
width, height = 750, 750
center = [int(width/2), int(height/2)]

display = pygame.display.set_mode([width, height])
pygame.display.set_caption("solar")
clock = pygame.time.Clock()

class planet(object):
    def __init__(self, r, mxpoints, color):
        self.r = r          # distance from center (radius)
        self.n = mxpoints   # max number of points (changes speed)
        self.counter = 0    # so each planet can keep track of its own location
        self.color = color
        self.orbit = []     # stores every point the planet will be drawn
        self.defineorbit(r) # generate the points of the orbit

    def nextpos(self, posstart, step, angle):
        output = []
        output.append(posstart[0] - (math.sin(math.radians(angle)) * step)) # simple pythagorean math
        output.append(posstart[1] - (math.cos(math.radians(angle)) * step)) # step == hypotenusa or line lenght
        return output   # outputs a [x, y] point

    def defineorbit(self, r):   # draw a circle by creating small lines (basically a big polygon)
        rr = r ** 2
        angle = 360/self.n
        step = (2 * rr - 2 * rr * math.cos(angle)) ** 0.5 # law of cosines
        for i in range(self.n):
            npos = self.nextpos(center, r, angle)
            self.orbit.append([int(npos[0]), int(npos[1])]) # the int() makes it a bit innacurate
            angle += 360/self.n                             # but it doesn't make a difference
                                                            # if you don't draw a line connecting every point
    def draw(self):     # to be iterated in the game loop
        if self.counter >= self.n:
            self.counter = 0
        pygame.draw.circle(display, self.color, self.orbit[self.counter], 2, 0)
        self.counter += 1

rads = [58, 108, 149, 227, 778, 1433, 2872, 4495]
for i, rad in enumerate(rads):
    rads[i] = round(rad / 8)        # scaling it down (so it can fit in the screen)

points = [88, 224, 365, 687, 4331, 10747, 30590, 59800] # each point == one day
for i, point in enumerate(points):
    points[i] = round(point / 4)    # scalint it down (4 times faster)

#planet(radius, mxpoints, color)
mercury = planet(rads[0], points[0], (140, 39, 0))
venus = planet(rads[1], points[1], (162, 84, 0))
earth = planet(rads[2], points[2], (49, 81, 194))
mars = planet(rads[3], points[3], (162, 42, 0))
jupiter = planet(rads[4], points[4], (197, 84, 0))
saturn = planet(rads[5], points[5], (197, 128, 0))
uranus = planet(rads[6], points[6], (197, 197, 197))
neptune = planet(rads[7], points[7], (75, 75, 213))

planets = [mercury, venus, earth, mars, jupiter, saturn, uranus, neptune]

closed = False
while not closed:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
    display.fill([0, 0, 0])
    pygame.draw.circle(display, [150, 150, 0], center, 3, 0) # PRAISE THE SUN
    for plnt in planets:
        plnt.draw()
    pygame.display.update()
    clock.tick(15)  # 15 fps -> 60 days per second
pygame.quit()