import math, timeit

def selectAct_Aux(actividades, i, j, M):
  if M[i][j] == -math.inf:
    act = []
    for x in range(i, j+1):
      if actividades[i][2] <= actividades[x][1]:
        if actividades[x][2] <=actividades[j][1]:
            act.append(x)
      #end if

    if len(act) == 0:
      M[i][j] = 0
    else:
      maxim = -math.inf
      for k in act:
        res = selectAct_Aux(actividades, i, k, M) + selectAct_Aux(actividades, k, j, M) + 1
        if maxim < res:
          maxim = res
      #end for
      M[i][j] = maxim
    #end if
  #end if
  return M[i][j]
#end def

def selectAct(actividades):
  activit = sorted(actividades, key = lambda a: a[2])
  activit.insert(0, ["test", -math.inf, 0])
  activit.insert(len(activit), ["test", activit[-1][2], math.inf])
  M = [[-math.inf for i in range(len(activit))] for j in range(len(activit))]
  return selectAct_Aux(activit, 0, len(activit) - 1, M)
#end def

activities = []
with open("experimento100.txt") as f:
  for line in f:
    for info in line.split("\n"):
      data = info.split()
      if len(data) >= 3:
        activities.append([data[0], int(data[1]), int(data[2])])
    #end for
  #end for


start = timeit.default_timer()
print(selectAct(activities))
stop = timeit.default_timer()
print('Tiempo algoritmo programación dinámica: ' + str(stop - start) + ' segundos')