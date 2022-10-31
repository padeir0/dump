import pygame, random as rnd, Gmath

pygame.init()

width, height = 500, 500
center = (width/2, height/2)
tSize = 5
oPoints = (center, (center[0], center[1] + 5), (center[0] + 5, 0))
oSides = ((oPoints[0], oPoints[1]), (oPoints[1], oPoints [2]), (oPoints[2], oPoints[0]))

display = pygame.display.set_mode([width, height])
pygame.display.set_caption("Triangles")
clock = pygame.time.Clock()

sList = []
sList.extend(oSides)

class Triangle(object):
    def __init__(self, aSide):
        self.aSide = aSide
        points = (aSide[0], aSide[1], )


closed = False
while not closed:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
    pygame.display.update()
    clock.tick(15)

pygame.quit()