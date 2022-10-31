import pygame, math

pygame.init()

width, height = 800, 600
center = [width/2, height/2]
currpos = [width/2, height/2]
angle = -90

display = pygame.display.set_mode((width, height))
pygame.display.set_caption('hey there')
clock = pygame.time.Clock()

def nextpos1(pos, angle):
    output = []
    output.append(pos[0] - (math.sin(math.radians(angle)) * 100))
    output.append(pos[1] - (math.cos(math.radians(angle)) * 100))
    return output

def nextpos2(pos, angle):
    output = []
    output.append(pos[0] - (math.sin(math.radians(angle)) * 100))
    output.append(pos[1] - (math.cos(math.radians(angle)) * 100))
    return output

closed = False
while not closed:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
        elif True in pygame.mouse.get_pressed():
            angle += int((pygame.mouse.get_pos()[1]/height) * 180)
            print(angle)
            npos = nextpos2(currpos, angle)
            pygame.draw.line(display, [30,190,40], currpos, npos, 2)
            currpos = [npos[0], npos[1]]
    pygame.display.update()
    clock.tick(15)

pygame.quit()