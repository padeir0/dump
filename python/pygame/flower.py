import pygame, math
import random as rnd

pygame.init()
width, height = 500, 500
dimensions = [width, height]
center = [int(x/2) for x in dimensions]

display = pygame.display.set_mode([width, height])
pygame.display.set_caption("Dunno")
clock = pygame.time.Clock()

def nextpos(posstart, step, angle):
    output = []
    output.append(int(posstart[0] - (math.sin(math.radians(angle)) * step))) # simple pythagorean math
    output.append(int(posstart[1] - (math.cos(math.radians(angle)) * step))) # step == hypotenusa or line lenght
    return output   # outputs a [x, y] point

def xydistance(p1, p2): # p == point == [x, y]
    cat1 = p1[0] - p2[0]
    cat2 = p1[1] - p2[1]
    return (cat1 ** 2 + cat2 ** 2) ** 0.5

def rndcolor():
    red = rnd.randint(40, 255)
    green = rnd.randint(0, 255)
    blue = rnd.randint(0, 255)
    return (red, green, blue)

class Flower(object):
    def __init__(self, npetals, size):
        self.size = int(size)
        self.ccolor = rndcolor()
        self.petals = []
        self.gencircle(npetals + 4, size)
        self.genpetals(self.petals)
        pygame.draw.circle(display, self.ccolor, center, 10, 0)

    def gencircle(self, nlines, size): # the petal is composed of two lines a arc
        angle = 0
        increment = 360 / nlines
        while angle < 360:
            t1 = nextpos(center, size, angle)
            t2 = nextpos(center, size, angle+increment)
            cpos = nextpos(center, size, angle+(increment/2))
            epos = nextpos(center, size - 3, angle+(increment/2))
            self.petals.append((t1, t2, cpos, epos))
            angle += increment

    def genpetals(self, petals):
        r = int(xydistance(petals[0][0], petals[0][1]) / 2) #circle radius
        for petal in petals:
            color = rndcolor()
            pygame.draw.line(display, color, center, petal[0], 3)
            pygame.draw.line(display, color, center, petal[1], 3)
            pygame.draw.circle(display, color, petal[2], r, 0)
            pygame.draw.circle(display, [0, 0, 0], petal[3], abs(r - 1), 0)

closed = False
while not closed:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
        elif True in pygame.mouse.get_pressed():
            mousepos = pygame.mouse.get_pos()
            g = [10 * round(mousepos[0] / width, 1), 200 * round((mousepos[1] / height), 1)]
            display.fill([0,0,0])
            f = Flower(g[0], g[1])
            print(mousepos)
    pygame.display.update()
    clock.tick(15)

pygame.quit()