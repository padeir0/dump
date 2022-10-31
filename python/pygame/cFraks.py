import pygame, Gmath

height, width = 600, 600
center = 300, 300

display = pygame.display.set_mode([width, height])
pygame.display.set_caption("Fractal")
clock = pygame.time.Clock()

def frak(pos, lenght, plus, sides, qq):
    if qq < 1:
        return 0
    else:
        angle = round(360 / sides, 2)
        for i in range(sides):
            npoint = Gmath.nPoint(pos, lenght, angle * i)
            pygame.draw.line(display, [30,190,40], pos, npoint, 1)
            frak(npoint, lenght - plus, plus, sides, qq - 1)


pygame.display.update()

lst = [0, 0, 0, center]

closed = False
while not closed:
    display.fill((0, 0, 0))
    for event in pygame.event.get():
        pos = pygame.mouse.get_pos()
        if event.type == pygame.QUIT:
            closed = True
        elif pygame.mouse.get_pressed()[2] and pygame.mouse.get_pressed()[0]:
            lst[3] = pos
        elif pygame.mouse.get_pressed()[0]:
            lst[0] = int(pos[0] / 6)
        elif pygame.mouse.get_pressed()[1]:
            lst[1] = int(pos[0] / 30)
        elif pygame.mouse.get_pressed()[2]:
            lst[2] = int(pos[0] / 120)

    frak(lst[3], 120, lst[0], lst[1] + 1, lst[2])

    clock.tick(15)
    pygame.display.update()
pygame.quit()