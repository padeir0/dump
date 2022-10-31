import pygame,random

pygame.init()
pygame.font.init() 
myfont = pygame.font.SysFont('Comic Sans MS', 20)

width, height = 500, 500

display = pygame.display.set_mode((width, height + 50))
pygame.display.set_caption('Cells on fire')
clock = pygame.time.Clock()

buttony = height + 2
buttonx = height - 48
buttonsize = 46
bttyend = buttony + buttonsize
bttxend = buttonx + buttonsize

class Cell(object):
    def __init__(self, i, j, size):
        self.i = i
        self.j = j
        self.x = i * size
        self.xend = self.x + size
        self.y = j * size
        self.yend = self.y + size
        self.size = size - 1
        self.burned = False

    def draw(self):
        if self.burned == True:
            pygame.draw.rect(display, [255, 255, 255], [self.x, self.y, self.size, self.size], 0)
        elif self.burned == False:
            pygame.draw.rect(display, [0, 0, 0], [self.x, self.y, self.size, self.size], 0)
    
    def toggle(self):
        self.burned = not self.burned


class Board(object):
    def __init__(self, n):
        self.n = n
        self.board = []
        self.victory = []
        size = width / n
        for i in range(n):
            self.board.append([])
            self.victory.append([])
            for j in range(n):
                self.board[i].append(Cell(i, j, size))
                self.board[i][j].draw()
                self.victory[i].append(self.board[i][j].burned)
    
    def stamp(self, cell):
        i = cell.i - 1
        lenght = len(self.board[0]) - 1
        for i in range(i, i + 3):
            j = cell.j - 1
            for j in range (j, j + 3):
                if 0 <= i <= lenght and 0 <= j <= lenght:
                    self.board[i][j].toggle()
                    self.victory[i][j] = not self.victory[i][j]
                    self.board[i][j].draw()
    
    def randomize(self):
        for stamps in range(7): 
            rndi, rndj = random.randint(0, self.n - 1), random.randint(0, self.n - 1)
            self.stamp(self.board[rndi][rndj])

    def winquestionmark(self):
        output = True
        for item in self.victory:
            if False in item:
                output = False
        return output

bd = Board(6)

pygame.draw.rect(display, [255, 0, 0], [buttonx, buttony, buttonsize, buttonsize], 0)

counter = 0
closed = False
while not closed:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
        elif True in pygame.mouse.get_pressed():
            mousepos = pygame.mouse.get_pos()
            counter += 1
            for row in bd.board:
                for item in row:
                    if item.x < mousepos[0] < item.xend and item.y < mousepos[1] < item.yend:
                        bd.stamp(item)
            if bd.winquestionmark():
                display.fill([0, 0, 0])
                text = myfont.render("Victory! With only: " + str(counter) + " clicks.", False, (255, 255, 255))
                display.blit(text,(width/2 - 100, height/2))
                pygame.draw.rect(display, [255, 0, 0], [buttonx, buttony, buttonsize, buttonsize], 0)
            if buttonx < mousepos[0] < bttxend and buttony < mousepos[1] < bttyend:
                display.fill([0, 0, 0])
                pygame.draw.rect(display, [255, 0, 0], [buttonx, buttony, buttonsize, buttonsize], 0)
                bd.randomize()
                counter = 0
            print(counter)
    clock.tick(15)
    pygame.display.update()
pygame.quit()