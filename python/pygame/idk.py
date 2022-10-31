import pygame
import math
import random as rnd
import time

pygame.init()

width, height = 500, 500
center = (int(width/2), int(height/2))

display = pygame.display.set_mode((width, height))
pygame.display.set_caption('idk')
clock = pygame.time.Clock()

entities = []
counter = 0

def distance(p0, p1):
    return ((p1[0] - p0[0]) ** 2 + (p1[1] - p0[1]) ** 2) ** 0.5

class Bee(object):
    def __init__(self, pos, speed, orientation, radius):
        self.x, self.y = pos
        self.radius = radius
        self.alive = True
        self.speed = speed
        self.orientation = orientation
        self.color = (rnd.randint(0,255), rnd.randint(0,255), rnd.randint(0,255))
    
    def draw(self):
        pygame.draw.circle(display, self.color, (self.x, self.y), self.radius, 0)
    
    def edge(self):
        boo = False
        if self.x < 0:
            self.x = width
            boo = True
        elif self.x > width:
            self.x = 0
            boo = True
        if self.y < 0:
            self.y = height
            boo = True
        elif self.y > height:
            self.y = 0
            boo = True
        return boo

    def move(self):
        if self.edge():
            return False
        else:
            if self.orientation == 0:
                self.x += self.speed
            elif self.orientation == 1:
                self.x -= self.speed
            elif self.orientation == 2:
                self.y += self.speed
            elif self.orientation == 3:
                self.y -= self.speed
            return True

firstbee = Bee(center, 1, rnd.randint(0, 3), 50)
entities.append(firstbee)

t = time.clock()

closed = False
while not closed:
    display.fill([0, 0, 0])

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
    for item in entities:
        if True in pygame.mouse.get_pressed():
            mousepos = pygame.mouse.get_pos()
            if distance((item.x, item.y), mousepos) < item.radius and time.clock() - t > 0.01:
                item.alive = False
                entities.append(Bee((item.x, item.y), int(counter/2)+1, rnd.randint(0, 3), int(item.radius*0.85)))
                entities.append(Bee((item.x, item.y), int(counter/2)+1, rnd.randint(0, 3), int(item.radius*0.85)))
                entities.remove(item)
                counter += 1
                t = time.clock()
            
        if item.alive == True:
            item.move()
            item.draw()
    
    pygame.display.update()
    clock.tick(15)
pygame.quit()