import pygame, random

pygame.init()
pygame.font.init() 
myfont = pygame.font.SysFont('Comic Sans MS', 35)

width, height = 600, 400

display = pygame.display.set_mode((width, height))
pygame.display.set_caption('2048')
clock = pygame.time.Clock()

def movelineleft(matrice):
    mtrx = []
    for i in matrice:
        line = [tile for tile in i if tile != 0]
        line += [0 for tile in i if tile == 0]
        mtrx.append(line)
    return mtrx

def movelineright(matrice):
    mtrx = []
    for i in matrice:
        line = [0 for tile in i if tile == 0]
        line += [tile for tile in i if tile != 0]
        mtrx.append(line)
    return mtrx

def merge(matrice, s, boolean):
    mtrx = []
    if s == 'r':
        for line in matrice:
            for j in range(len(line)):
                if j < 3 and line[j] == line[j+1]:
                    line[j + 1] *= 2
                    line[j] = 0
                    boolean = True
            mtrx.append(line)
    elif s == 'l':
        for line in matrice:
            for j in range(len(line)):
                if j < 3 and line[j] == line[j+1]:
                    line[j] *= 2
                    line[j + 1] = 0
                    boolean = True
            mtrx.append(line)
    return mtrx

def transpose(matrice):
	return [list(row) for row in zip(*matrice)]

class Cell(object):
    def __init__(self, y, x, size, val):
        self.x = x * size
        self.y = y * size
        self.size = size
        self.gap = 35
        self.val = val
        self.text = myfont.render(str(val), False, (255, 255, 255))

    def valupdate(self):
        self.text = myfont.render(str(self.val), False, (255, 255, 255))

    def draw(self):
        pygame.draw.rect(display, [255, 255, 255], [self.x, self.y, self.size, self.size], 2)

    def blt(self):
        display.blit(self.text,(self.x + self.gap, self.y + self.gap))

class board(object):
    def __init__(self, rows, cols, side):
        self.rows = rows
        self.cols = cols
        self.area = rows * cols
        self.table = []
        self.values = []
        self.numofzeros = rows * cols   #count the number of zeros
        self.boo = False                #verifies if one item was merged
        for x in range(rows):
            self.table.append([])
            self.values.append([])
            for y in range(cols):
                self.table[x].append(Cell(x, y, side/4, 0))
                self.values[x].append(0)

    def debug(self): # for debugging
        output = []
        for i in range(self.rows):
            output.append([])
            for j in range(self.cols):
                output[i].append(self.table[i][j].val) #self.table[i][j].x, self.table[i][j].y, 
            print(output[i])
        print(self.numofzeros)

    def gencells(self):
        for rows in self.table:
            for cel in rows:
                cel.draw()
                cel.blt()
        board.newtile()
        board.newtile()
    
    def update(self):
        self.numofzeros = 0
        for i in range(self.rows):
            for j in range(self.cols):
                self.table[i][j].val = self.values[i][j]
                self.table[i][j].valupdate()
                if self.values[i][j] == 0:
                    self.numofzeros += 1
        display.fill([200, 96, 0])
        for rows in self.table:
            for cel in rows:
                cel.draw()
                cel.blt()
        self.debug()

    def newtile(self):  #recursive function, var 'q' = total number of tiles
        x, y = random.randint(0, 3), random.randint(0, 3)
        if self.values[x][y] != 0 and self.numofzeros > 0:
            self.newtile()
        elif self.values[x][y] == 0:
            self.values[x][y] = random.randint(1, 2) * 2
            self.update()

    def move(self, string):
        upboard = []
        transvalues = transpose(self.values)
        trans = False
        if string == 'LEFT':
            # move all items left, merge equal items, them move them all again
            upboard = movelineleft(merge(movelineleft(self.values), 'l', self.boo))
        elif string == 'RIGHT':
            upboard = movelineright(merge(movelineright(self.values), 'r', self.boo))
        elif string == 'UP':
            trans = True # for transposing the matrice back to normal in the end
            upboard = movelineleft(merge(movelineleft(transvalues), 'l', self.boo))
        elif string == 'DOWN':
            trans = True
            upboard = movelineright(merge(movelineright(transvalues), 'r', self.boo))
        if trans == True:
            self.values = transpose(upboard)
        else:
            self.values = upboard
        if self.numofzeros == 0 and self.boo == False:
            self.gameover()
        self.newtile()
        self.boo = False
    
    def gameover(self):
        pass


board = board(4, 4, 400)
board.gencells()
board.update()

closed = False
while not closed:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                board.move('UP')
                board.update()
                print('UP')
            elif event.key == pygame.K_DOWN:
                board.move('DOWN')
                board.update()
                print('DOWN')
            elif event.key == pygame.K_RIGHT:
                board.move('RIGHT')
                board.update()
                print('RIGHT')
            elif event.key == pygame.K_LEFT:
                board.move('LEFT')
                board.update()
                print('LEFT')

    pygame.display.update()
    clock.tick(15)

pygame.quit()

# K_UP                  up arrow
# K_DOWN                down arrow
# K_RIGHT               right arrow
# K_LEFT                left arrow