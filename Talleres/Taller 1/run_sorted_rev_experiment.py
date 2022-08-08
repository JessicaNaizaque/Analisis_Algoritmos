## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## @author Camila Aguirre
## @author Jessica Naizaque
## =========================================================================

import struct, sys, time, random
from NaiveBubbleSort import *
from ImprovedBubbleSort import *
from InsertionSort import *

## -------------------------------------------------------------------------
def IsSorted( S ):
  f = True
  for i in range( len( S ) - 1 ):
    f = f and not( S[ i + 1 ] < S[ i ] )
  # end for
  return f
# end def

## -------------------------------------------------------------------------
def DoExperiment( S, f ):
  r = 10 
  t = 0 
  s = True
  for i in range( r ):
    C = S.copy( ) 
    start = time.time( )
    f( C ) 
    end = time.time( )
    s = s and IsSorted( C ) 
    t += float( end - start ) 
  # end for
  return [ s, t / float( r ) ]
# end def

## -------------------------------------------------------------------------
def CreateSequence( n ):
  seq = [] 
  for i in range (0, n):
    num = random.randint(1, 20000)
    seq.append(num)
  # end for
  return seq
# end def

## -------------------------------------------------------------------------
# Inputs
b = int( sys.argv[ 1 ] ) 
e = int( sys.argv[ 2 ] ) 
s = int( sys.argv[ 3 ] ) 
input_sequence = CreateSequence(e)
input_sequence.sort(reverse=True)

print(input_sequence)

# Perform experiments
for n in range( b, e + 1, s ):
  nbr = DoExperiment( input_sequence[ 0 : n ], NaiveBubbleSort )
  ibr = DoExperiment( input_sequence[ 0 : n ], ImprovedBubbleSort )
  inr = DoExperiment( input_sequence[ 0 : n ], InsertionSort )
  if not( nbr[ 0 ] and ibr[ 0 ] and inr[ 0 ] ):
    print( "ERROR: Input sequence was not ordered" )
    sys.exit( 1 )
  # end if
  print( n, nbr[ 1 ], ibr[ 1 ], inr[ 1 ] )
# end for

## eof - run_experiment.py