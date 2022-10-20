import random, sys, itertools, pprint

board = []
minesBoard = set()

def createBoard(dim, mines):
    for i in range(dim):
        arr = []
        for j in range(dim):
            arr.append(0)
        #end for
        board.append(arr)
    #end for

    while len(minesBoard) < mines:
        i = random.randint(0, dim-1)
        j = random.randint(0, dim-1)
        board[i][j] = 1
        minesBoard.add((i, j))
    #end while
#end def

def findMines(mines, allCoordenates):
    for c in itertools.combinations(allCoordenates, mines):
        if all(board[coordenate[0]][coordenate[1]] == 1 for coordenate in c):
            return list(c)
        #end if
    #end for
    return []
#end def

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Usage: python3", sys.argv[0], "dim mines")
        sys.exit()
    dim = int(sys.argv[1]) #Dimension of the board
    mines = int(sys.argv[2]) #Number of mines in the board
    
    coordenates = []
    for i in range(dim):
        for j in range(dim):
            coordenates += [[i, j]]
        #end for
    #end for
    createBoard(dim, mines)
    print("Board:")
    pprint.pprint(board)
    print("Mines set original:", minesBoard)
    print("Mines found: ", findMines(mines, coordenates))
#end if