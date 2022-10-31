import pygame, math, random
pygame.init()

width, height = 500, 500
center = [width/2, height/2]

display = pygame.display.set_mode([width, height])
pygame.display.set_caption("Spiral")
clock = pygame.time.Clock()

def rndcolour():
    red = random.randint(0, 255)
    green = random.randint(0, 255)
    blue = random.randint(0, 255)
    return [red, green, blue]

def nextpos(posstart, size, angle):
    output = []
    output.append(posstart[0] - (math.sin(math.radians(angle)) * size))
    output.append(posstart[1] - (math.cos(math.radians(angle)) * size))
    return output

def spiral(spoint, q, size, angle, w): #spoint == startint point, q == max number of draws
    if q == 0:
        return True
    npoint = nextpos(spoint, size, angle)
    pygame.draw.line(display, rndcolour(), spoint, npoint, w)
    spiral(npoint, q - 1, size + 0.1, 10 + angle, random.randint(-1, 1))

spiral(center, 500, 2, 10, 2)

pygame.display.update()

closed = False
while not closed:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
        elif True in pygame.mouse.get_pressed():
            mousepos = pygame.mouse.get_pos()
            gradient = [round(mousepos[0] / width, 1), round((mousepos[1] / height), 1)]
            print(gradient[0], 10 - gradient[1])
            display.fill([0, 0, 0])
            spiral(center, 500, 10 * gradient[0], 100 * gradient[1], 2)
    clock.tick(15)
    pygame.display.update()
pygame.quit()