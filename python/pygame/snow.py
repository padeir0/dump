import pygame, random as rnd, Gmath

pygame.init()

width, height = 500, 500
center = [width/2, height/2]

display = pygame.display.set_mode([width, height])
pygame.display.set_caption("Spiral")
clock = pygame.time.Clock()

entities = []

class Flake(object):
    def __init__(self, mass):
        self.x, self.y = rnd.randint(2, 498), 0
        self.velocity = [0, 0]
        self.aceleration = [0, 0]
        self.termVelo = 0.5 * mass
        self.pos = [self.x, self.y]
        self.mass = mass
        self.force = [0, mass/2]
        self.drag = [2 * self.velocity[0]/mass, 2 * self.velocity[1]/mass]

    def draw(self):
        pygame.draw.circle(display, (255, 255, 255), self.pos, self.mass, 0)
    
    def onTheEdge(self):
        if self.pos[0] < 0 or self.pos[0] > 500:
            return True
        elif self.pos[1] < 0 or self.pos[1] > 500:
            return True
        else:
            return False

    def phy(self, d):
        self.drag = [2 * self.velocity[0]/self.mass, 2 * self.velocity[1]/self.mass]
        self.pos[0] += int(self.velocity[0])
        self.pos[1] += int(self.velocity[1])
        if d == 0:
            self.force[0] = 2 - self.drag[0]
        else:
            self.force[0] = -2 - self.drag[0]
        self.force[1] = self.mass - self.drag[1]
        self.velocity[0] += self.force[0] / self.mass
        self.velocity[1] += self.force[1] / self.mass
        if self.onTheEdge() is True:
            entities.remove(self)

pygame.display.update()

closed = False
while not closed:
    if len(entities) < 300:
        entities.append(Flake(rnd.randint(3, 7)))
    
    mousepos = pygame.mouse.get_pos()

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
        elif True in pygame.mouse.get_pressed():
            print(mousepos)
    
    if mousepos[0] < 250:
        d = 0
    else:
        d = 1

    display.fill([0, 0, 0])
    for flake in entities:
        flake.draw()
        flake.phy(d)

    clock.tick(15)
    pygame.display.update()
pygame.quit()