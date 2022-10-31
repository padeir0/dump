import random

# var. 'i' stands for lines, var. 'j' for columns
board = []

def transpose(field):
	return [list(row) for row in zip(*field)]

def newboard():
    for i in range(4):
        board.append([])
        for j in range(4):
            board[i].append(0)

def printboard():
    print('\n')
    for line in board:
        print(line)

def newtile():
    for line in range(4):
        if 0 in board[line]:
            while True:
                i, j = random.randint(0, 3), random.randint(0, 3)
                if board[i][j] == 0:
                    board[i][j] = 2
                    break
                elif board[i][j] != 0:
                    i, j = random.randint(0, 3), random.randint(0, 3)
            break

def move(matrice, string):
    upboard = []
    transboard = transpose(matrice) # by transposing the matrice lines become columns and vice versa
    trans = False
    if string == 'a':
        # move all items left, merge equal items, them move them all again
        upboard = movelineleft(merge(movelineleft(matrice), 'l'))
    elif string == 'd':
        upboard = movelineright(merge(movelineright(matrice), 'r'))
    elif string == 'w':
        trans = True # for transposing the matrice back to normal in the end
        upboard = movelineleft(merge(movelineleft(transboard), 'l'))
    elif string == 's':
        trans = True
        upboard = movelineright(merge(movelineright(transboard), 'r'))
    if trans == True:
        return transpose(upboard)
    else:
        return upboard

def check_victory(matrice):
    for line in matrice:
        if 2048 in line:
            return True

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

def merge(matrice, s):
    mtrx = []
    if s == 'r':
        for line in matrice:
            for j in range(len(line)):
                if j < 3 and line[j] == line[j+1]:
                    line[j + 1] *= 2
                    line[j] = 0
            mtrx.append(line)
    elif s == 'l':
        for line in matrice:
            for j in range(len(line)):
                if j < 3 and line[j] == line[j+1]:
                    line[j] *= 2
                    line[j + 1] = 0
            mtrx.append(line)
    return mtrx

newboard()
newtile()
newtile()
printboard()

pinputs = ['w', 'a', 's', 'd', 'quit']
while True:
    enter = input("Enter a direction (w/a/s/d) or (quit): ")
    if enter in pinputs:
        if enter == 'quit':
            break
        elif check_victory(board) == "Victory":
            print("YOU FUCKING WON MATE")
            break
        else:
            board = move(board, enter)
            newtile()
            printboard()