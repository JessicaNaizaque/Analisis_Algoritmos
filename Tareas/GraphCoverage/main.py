import math, random, sys, itertools, pprint

def bruteForce(vertices, adjMatrix, numEdges):
  for r in range(1, len(vertices) + 1):
    for c in itertools.combinations(vertices, r):
      countEdges = 0
      c = list(c)
      vert = [-1 for x in range(len(vertices))
              ]  #-1 cuando el camino no ha sido recorrido
      pairs = []
      for k in c:  #Recorrer todos los vértices de la combinación
        vert[k] = 1  #1 cuando el camino sí se recorre
        for j in range(len(vertices)):
          if adjMatrix[k][j] != 0:
            vert[j] = 1
            if [k, j] not in pairs and [j, k] not in pairs:
              countEdges += 1
            #end if
            pairs.append([k, j])
          #end if
        #end for
      #end for
      if -1 not in vert and countEdges == numEdges:
        return c
      #end if
    #end for
  #end for
  return []
#end def

def approx(vertices, adjMatrix, edges, shuffle=True):
  c = [-1 for i in range(len(vertices))]
  copyEdges = edges

  while len(copyEdges) > 0:
    ind = random.randint(0, len(copyEdges)-1) #Seleccionar una arista aleatoria con un índice aleatorio
    randomEdge = copyEdges[ind]
    c[randomEdge[0]] = randomEdge[0]
    c[randomEdge[1]] = randomEdge[1]

    x = len(edges)-1
    while x >= 0:
      if randomEdge[0] in copyEdges[x] or randomEdge[1] in copyEdges[x]:
        copyEdges.pop(x)
      #end if
      x -= 1
    #end while
  #end while
      
  for i in range(len(vertices)):
    count = 0 #Count revisa si el vértice tiene una arista
    j = 0
    while count == 0 and j < len(vertices):
        if i != j and adjMatrix[i][j] != 0:
            count += 1
        #end if
        j += 1
    #end while
    if count != 0:
        c[i] = vertices[i]
    #end if
  #end for
  return c
#end def
  
def createGraph(n, p):
  vertices = [i for i in range(n)]
  adjMatrix = [[0 for i in range(n)] for j in range(n)]
  numEdges = 0
  edges = []
  # Show results
  print(n)
  for i in range(n):
    for j in range(i + 1, n):
      if i != j:
        q = random.uniform(0, 1)
        if q < p:
          costo = random.randint(1, 100)
          print(i, j, costo)
          adjMatrix[i][j] = costo
          adjMatrix[j][i] = costo
          numEdges += 1
          edges += [(i, j)]
        # end if
      # end if
    # end for
  # end for
  print(-1)
  return adjMatrix, vertices, edges, numEdges

## Read data
if len(sys.argv) < 4:
  print("Usage: python3", sys.argv[0], "n p d")
  sys.exit(1)
# end if
n = int(sys.argv[1])
p = float(sys.argv[2])
d = bool(sys.argv[3])

adjMatrix, vertices, edges, numEdges = createGraph(n, p)
# vertices = [0, 1, 2, 3, 4, 5, 6]
# numEdges = 8
# edges = [[0,1], [1, 2], [2, 3], [2, 4], [3, 4], [3, 5], [3, 6], [4, 5]]
# adjMatrix = [[0, 1, 0, 0, 0, 0, 0], [1, 0, 1, 0, 0, 0,
#                                      0], [0, 1, 0, 1, 1, 0, 0],
#              [0, 0, 1, 0, 1, 1, 1], [0, 0, 1, 1, 0, 1, 0],
#              [0, 0, 0, 1, 1, 0, 0], [0, 0, 0, 1, 0, 0, 0]]
# pprint.pprint(adjMatrix)
bf = bruteForce(vertices, adjMatrix, numEdges)
print("Brute force:")
print(bf)
app = approx(vertices, adjMatrix, edges)
print("Approximation:")
print(app)

## eof
