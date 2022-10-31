import pygame, Gmath, time, random as rnd, math

pygame.init()

width, heigth = 500, 500
center = [int(width/2), int(heigth/2)]
fps = 30

display = pygame.display.set_mode([width, heigth])
pygame.display.set_caption("ships")
clock = pygame.time.Clock()

entities = []
npcs = []

class Player(object):
    def __init__(self, name, lvl):
        self.alive = True
        self.isbullet = False
        self.isnpc = False

        # positioning
        self.pos = center
        self.speed = 2
        self.orientation = 0
        self.size = 10
        self.cannon = Gmath.nPoint(self.pos, 20, self.orientation)

        # stats
        self.lvl = lvl
        self.health = 50.0 + 50.0 * self.lvl
        self.heal = (2 / fps) * self.lvl
        self.damage = 10
        self.tbshots = 1 / (2 ** self.lvl)    #time between shots
        self.t = time.clock()

    def draw(self):
        p = self.pos
        self.cannon = Gmath.nPoint(p, 20, self.orientation)
        self.health += self.heal
        self.orientation = self.orientation % 360

        pygame.draw.line(display, (0, 140, 140), p, self.cannon, 3)
        pygame.draw.circle(display, (255, 255, 255), p, self.size, 0)

    def move(self, foward):
        if foward:
            self.pos = Gmath.nPoint(self.pos, self.speed, self.orientation)
        else:
            self.pos = Gmath.nPoint(self.pos, self.speed, self.orientation - 180)
    
    def shoot(self):
        if time.clock() - self.t > self.tbshots:
            entities.append(Bullet(self))
            self.t = time.clock()
        else:
            return False

    def isdead(self):
        if self.health > 0.0:
            for obj in entities:
                if obj is not self and Gmath.pDistance(self.pos, obj.pos) < self.size:
                    if obj.isbullet:
                        self.health -= obj.damage
                        obj.ship.lvl += 1
                        entities.remove(obj)
            return False
        else:
            return True

preier = Player("Artur", 1)
entities.append(preier)

class NPC(object):
    def __init__(self, lvl):
        self.alive = True
        self.isbullet = False
        self.isnpc = True

        # positioning
        self.pos = [rnd.randint(0, width), rnd.randint(0, heigth)]
        self.speed = 2
        self.orientation = 0
        self.size = 10
        self.cannon = Gmath.nPoint(self.pos, 20, self.orientation)

        # stats
        self.lvl = lvl
        self.health = 50.0 + 50.0 * self.lvl
        self.heal = (1 / fps) * self.lvl
        self.damage = 10
        self.tbshots = 5 / (self.lvl)       #time between shots
        self.st = time.clock()
        self.tbmov = 1 / (self.lvl)         #time between movement
        self.mt = time.clock()

    def reset(self):
        self.pos = [rnd.randint(0, width), rnd.randint(0, heigth)]
        self.cannon = Gmath.nPoint(self.pos, 20, self.orientation)
        self.orientation = 0
        self.lvl = 1
        self.health = 50.0 + 50.0 * self.lvl

    def draw(self):
        p = self.pos
        self.cannon = Gmath.nPoint(p, 20, self.orientation)
        self.health += self.heal
        self.orientation = self.orientation % 360

        pygame.draw.line(display, (0, 140, 140), p, self.cannon, 3)
        pygame.draw.circle(display, (255, 255, 255), p, self.size, 0)

    def move(self):
        if time.clock() - self.mt > self.tbmov:
            try:
                self.orientation += Gmath.pAngle(self.pos, self.cannon, preier.pos)
            except:
                print("BOOOP!")
        self.pos = Gmath.nPoint(self.pos, self.speed, self.orientation)
    def shoot(self):
        if time.clock() - self.st > self.tbshots:
            entities.append(Bullet(self))
            self.st = time.clock()
        else:
            return False

    def isdead(self):
        if self.health > 0.0:
            for obj in entities:
                if obj is not self and Gmath.pDistance(self.pos, obj.pos) < self.size:
                    if obj.isbullet:
                        self.health -= obj.damage
                        obj.ship.lvl += 1
                        entities.remove(obj)
            return False
        else:
            return True

class Bullet(object):
    def __init__(self, ship):
        self.isbullet = True
        self.isnpc = False
        self.pos = ship.cannon
        self.size = 2
        self.speed = 10
        self.direction = ship.orientation
        self.damage = 25
        self.ship = ship
    
    def draw(self):
        self.pos = Gmath.nPoint(self.pos, self.speed, self.direction)
        pygame.draw.circle(display, (255, 255, 255), self.pos, self.size, 0)

    def isdead(self):
        if self.pos[0] < 0 or self.pos[1] < 0 or self.pos[0] > width or self.pos[1] > heigth:
            return True
        else:
            return False

for i in range(1):
    n = NPC(1)
    entities.append(n)
    npcs.append(n)

movement = -1
manouver = -1
shooting = 0

closed = False
while not closed:
    display.fill((0, 0, 0))
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                movement = 0
                break
            elif event.key == pygame.K_DOWN:
                movement = 1
                break
            elif event.key == pygame.K_RIGHT:
                manouver = 0
                break
            elif event.key == pygame.K_LEFT:
                manouver = 1
                break
            elif event.key == pygame.K_RSHIFT:
                shooting = 1
                break
        elif event.type == pygame.KEYUP:
            if event.key == pygame.K_DOWN or event.key == pygame.K_UP:
                movement = -1
                break
            elif event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                manouver = -1
                break
            elif event.key == pygame.K_RSHIFT:
                shooting = 0
                break

    if movement == 0:
        preier.move(True)
    elif movement == 1:
        preier.move(False)
    if manouver == 0:
        preier.orientation -= 5
    elif manouver == 1:
        preier.orientation += 5
    if shooting == 1:
        preier.shoot()

    for obj in entities:
        obj.draw()
        if obj.isdead():
            if obj.isbullet:
                entities.remove(obj)
            elif obj.isnpc:
                obj.reset()

    for i, npc in enumerate(npcs):
        npc.move()
        npc.shoot()
        print("NPC%s LVL: %s" % (i, npc.lvl))

    print(preier.lvl)

    pygame.display.update()
    clock.tick(fps)

pygame.quit()