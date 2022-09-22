#Backtracking:
function Parentization(B, b, e)
  if b == e
    return string("A", b)
  else
    q = floor(Int,((b+e)/2))
    Z = ""
    Z = Z * "("
    Z = Z * Parentization(B, b, q)
    Z = Z * Parentization(B, q+1,e)
    Z = Z * ")"
    return Z
  end
end

function MatSeqBT(D)
  wT = length( D ) - 1
  hT = length( D ) - 1
  T = [0 for i = 1:hT, j = 1:wT]
  B = [-1 for i = 1:hT, j = 1:wT]
  for i in hT-2:-1:0
    for j in i+1:wT-1
      q = Inf
      m = 0
      for k in i:j-1      
        l = T[i+1, k+1]
        r = T[k+2, j+1]
        if i==0
          x = last(D)
        else
          x = D[i]
        end
        v = l + r + x * D[k+1] * D[j+1]
        if v < q
          q = v
          m = k + 1
        end
      end
      T[i+1, j+1] = q
      B[i+1, j+1] = m
    end
  end
  println(T)
  println(B)

  println(Parentization(B, 1, length(D)-1))
  return T[1, wT] #Mínima cantidad de mult. escalares
end

#D = [10, 100, 5, 50]
#D = [5, 7, 4, 3, 5]
#D = [10, 20, 40, 3, 12, 5, 7]
#D = [10, 100, 20, 3, 2, 8, 40, 64, 7, 5, 11, 50, 14, 15, 20, 5]
D = [5, 10, 3, 7, 100, 8, 4, 11, 20, 3, 14, 40, 5, 12, 16, 28, 3, 2, 1]

println(string("Mínima cantidad de mult. escalares: ",MatSeqBT(D)))