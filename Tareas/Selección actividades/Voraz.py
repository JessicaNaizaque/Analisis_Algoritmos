import timeit

def ActivitySelector_GREEDY(activities):
  actividades = sorted(activities, key = lambda c: c[2])
  R = [actividades[0]]
  k = 0
  for m in range(1, len(actividades)):
    if actividades[m][1] >= actividades[k][2]:
      R += [actividades[m]]
      k = m
    # end if
  # end for
  return(len(R))
# end def

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
print(ActivitySelector_GREEDY(activities))
stop = timeit.default_timer()
print('Tiempo algoritmo voraz: ' + str(stop - start) + ' segundos')