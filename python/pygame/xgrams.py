import pygame, math, random

pygame.init()

width, height = 500, 500
center = [width/2, height/2]

display = pygame.display.set_mode((width, height))
pygame.display.set_caption('X-Grams')
clock = pygame.time.Clock()

def rndcolor():
    red = random.randint(0, 255)
    green = random.randint(0, 255)
    blue = random.randint(0, 255)
    return [red, green, blue]

def nextpos(posstart, size, angle):
    output = []
    output.append(posstart[0] - (math.sin(math.radians(angle)) * size))
    output.append(posstart[1] - (math.cos(math.radians(angle)) * size))
    return output

def draw(nofpoints, size):
    angle = 0
    output = []
    increment = 360/nofpoints
    for i in range(nofpoints):
        output.append(nextpos(center, size, angle))
        angle += increment
    
    for start in output:
        for end in output:
            pygame.draw.line(display, rndcolor(), start, end, 3)

draw(3, 50)

closed = False
while not closed:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
        elif True in pygame.mouse.get_pressed():
            mousepos = pygame.mouse.get_pos()
            points = int((mousepos[0]/500) * 17)
            size = int((mousepos[1]/500) * 200)
            display.fill([0, 0, 0])
            draw(3 + points, 30 + size)
    clock.tick(15)
    pygame.display.update()
pygame.quit()