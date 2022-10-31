import pygame, math

pygame.init()

# display stuff
width, height = 800, 600
startpos = [width / 2, height - 190]
display = pygame.display.set_mode([width, height])
pygame.display.set_caption("Fractal Tree")
clock = pygame.time.Clock()

def nextpos(posstart, size, angle):
    output = []
    output.append(posstart[0] - (math.sin(math.radians(angle)) * size))
    output.append(posstart[1] - (math.cos(math.radians(angle)) * size))
    return output

def Fractal(spoint, size, rangle, langle, q, g):
    if q == 0:
        return True

    rpoint, lpoint = nextpos(spoint, size, rangle), nextpos(spoint, size, langle)
    pygame.draw.line(display, [30,190,40], spoint, rpoint, 1)
    pygame.draw.line(display, [30,190,40], spoint, lpoint, 1)

    Fractal(rpoint, size - 2, rangle + g, langle + g, q - 1, g)
    Fractal(lpoint, size - 2, rangle - g, langle - g, q - 1, g)

Fractal(startpos, 45, 30, -30, 10, 10)

pygame.display.update()

closed = False
while not closed:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
        elif True in pygame.mouse.get_pressed():
            mousepos = pygame.mouse.get_pos()
            gradient = [round(mousepos[0] / width, 2), 10 * round((mousepos[1] / height), 1)]
            print(gradient[0], 10 - gradient[1])
            display.fill([0, 0, 0])
            Fractal(startpos, 40, 30, -30, 13 - gradient[1], 30 * gradient[0])
    clock.tick(15)
    pygame.display.update()
pygame.quit()