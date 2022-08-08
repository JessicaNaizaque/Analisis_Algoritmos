'''
Sorts a sequence
@input S a sequence of weakly orderable elements.
@output S is modified to be an ordered sequence.
@requires Elements in S should be weakly comparable (i.e. they should support
          he use of the "<" symbol).
'''

RUN = 32
  
def CalculateMinRun(n): 
  r = 0
  while RUN <= n: 
    r |= n & 1
    n >>= 1
  #end while
  return n + r
#end def
  
def InsertionSort(S, b, e): 
  for i in range(b+1, e+1):
    aux = S[i]
    j = i-1
    while aux < S[j] and b <= j:
      S[j+1] = S[j]
      j -= 1
    S[j+1] = aux
    #end while
  #end for
  return S
#end def
              
def Merge(S, l, m, r): 
  length1 = m - l + 1
  length2 = r - m 
  left = []
  right = []
  for i in range(0, length1): 
    left.append(S[l + i]) 
  #end for

  for i in range(0, length2): 
    right.append(S[m + 1 + i]) 
  #end for

  i=0
  j=0
  k=l
  while j < length2 and  i < length1: 
    if left[i] <= right[j]: 
      S[k] = left[i] 
      i += 1
    else: 
      S[k] = right[j] 
      j += 1
    #end if
    k += 1
  #end while

  while i < length1: 
    S[k] = left[i] 
    k += 1
    i += 1
  #end while

  while j < length2: 
    S[k] = right[j] 
    k += 1
    j += 1
  #end while
#end def
  
def TimSortMethod( S ): 
    n = len(S) 
    minrun = CalculateMinRun(n) 
  
    for b in range(0, n, minrun): 
      e = min(b + minrun - 1, n - 1) 
      InsertionSort(S, b, e) 
    #end for

    size = minrun 
    while size < n: 
      for left in range(0, n, 2 * size): 
        mid = min(n - 1, left + size - 1) 
        right = min((left + 2 * size - 1), (n - 1)) 
        Merge(S, left, mid, right) 
      #end for
      size = 2 * size
    #end while 
#end def
  

#array = [-1,5,0,-3,11,9,-2,7,0] 
  
#print("Array:") 
#print(array) 
  
#TimSort(array) 
  
#print("Sorted Array:") 
#print(array)

## eof - TimSort.py
