import pygame, pyperclip

pygame.init()
pygame.font.init() 
myfont = pygame.font.SysFont('Comic Sans MS', 10)

width, height = 255, 255

pallete = pygame.display.set_mode((width, height))
pygame.display.set_caption('Color Pallette')
clock = pygame.time.Clock()
r, t = 4, 4
lst = [0, 0, 0]
closed = False
while not closed:
    for event in pygame.event.get():
        pos = pygame.mouse.get_pos()
        if event.type == pygame.QUIT:
            closed = True
        elif pygame.mouse.get_pressed()[0]:
            lst[0] = pos[0]
        elif pygame.mouse.get_pressed()[1]:
            lst[1] = pos[0]
        elif pygame.mouse.get_pressed()[2]:
            lst[2] = pos[0]
    pallete.fill(lst)
    pygame.draw.circle(pallete, (255, 0, 0), (lst[0], 50), r, t)
    pygame.draw.circle(pallete, (0, 255, 0), (lst[1], 50), r, t)
    pygame.draw.circle(pallete, (0, 0, 255), (lst[2], 50), r, t)
    text = myfont.render("(%s, %s, %s)" % (lst[0], lst[1], lst[2]), False, (255 - lst[0], 255 - lst[1], 255 - lst[2]))
    pallete.blit(text, (110 - 4 * int(lst[0]/100), 10))
    pyperclip.copy("(%s, %s, %s)" % (lst[0], lst[1], lst[2]))
    pygame.display.update()
    clock.tick(5)

pygame.quit()