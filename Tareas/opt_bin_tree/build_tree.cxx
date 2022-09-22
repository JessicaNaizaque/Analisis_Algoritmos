
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "nodo.h"

void saltosPalabraRepetida(Nodo<std::string>* optPadre, Nodo<std::string>* avlPadre, std::string pal) { //¿Cuántos saltos tendría que dar cada árbol para llegar a la palabra más repetida?
  const long long opt = optPadre->buscar(pal);
  const long long avl = avlPadre->buscar(pal);
  
  //Mostrar cuántos saltos da cada árbol
  std::cout << "Cantidad de saltos que da el arbol opt para llegar a la palabra " << pal << ": " << opt << std::endl;
  std::cout << "Cantidad de saltos que da el arbol avl para llegar a la palabra " << pal << ": " << avl << std::endl;

  if (avl < opt) {
    std::cout << "***El arbol de AVL encontro la palabra en menos saltos" << std::endl;
  } else if (opt < avl) {
    std::cout << "***El arbol optimo encontro la palabra en menos saltos" << std::endl;
  } else {
    std::cout << "***Los dos arboles tuvieron la misma cantidad de saltos para encontrar la palabra más repetida" << std::endl;  
  }
}

//Crea árbol avl recursivamente
Nodo<std::string>* treeAvl(const std::vector<std::string>& T, unsigned long long i, unsigned long long j) {
  unsigned long long x = (i+j)/2;
  Nodo<std::string>* nodo = new Nodo<std::string>(T[x]); //Crear el nodo para hacer sus subárboles
  if (i >= j) {
    return NULL;
  }
  
  //Llamados recurrentes para llenar el árbol:
  nodo->setIzq(treeAvl(T, i, x));
  nodo->setDer(treeAvl(T, x + 1, j));
  return nodo;
}

//Crea árbol óptimo recursivamente
Nodo<std::string>* treeOpt(const std::vector<std::string>& T, const std::vector<std::vector<unsigned long long>> B, unsigned long long i, unsigned long long j) {
  unsigned long long x = B[i][j];
  Nodo<std::string>* nodo = new Nodo<std::string>(T[x]);
  if (i > j) {
    return NULL;
  } else if (i == j) {
    return nodo;
  }
  //Llamados recurrentes para llenar el árbol:  
  nodo->setIzq(treeOpt(T, B, i, x - 1));
  nodo->setDer(treeOpt(T, B, x + 1, j));
  return nodo;
}

double BuildTree(
  const std::vector< std::string >& T,
  const std::vector< double >& P,
  const std::vector< double >& Q,
  Nodo<std::string>* &optPadre,
  Nodo<std::string>* &avlPadre
) {
  std::vector< std::vector< double > > M( Q.size( ), std::vector< double >( Q.size( ), 0 ) );
  std::vector< std::vector< unsigned long long > > B( Q.size( ), std::vector< unsigned long long >( Q.size( ), 0 ) ); //Crear matriz backtraking
  // Base cases
  for( unsigned long long i = 0; i < Q.size( ); ++i )
  {
    std::cout << "Base case: " << ( i + 1 ) << "/" << P.size( ) << std::endl;
    M[ i ][ i ] = Q[ i ];
	B[ i ][ i ] = i;
  } // end for
  
  // Recursive cases
  for( unsigned long long i = P.size( ); i > 1; --i )
  {
    std::cout << "Row: " << ( i + 1 ) << "/" << P.size( ) << std::endl;
    for( unsigned long long j = i; j < Q.size( ); ++j )
    {
	  double w = Q[ i - 1 ];
	  for( unsigned long long l = i; l <= j; ++l )
	    w += P[ l - 1 ] + Q[ l ];
      double q;
      unsigned long long x;
      for( unsigned long long r = i; r <= j; ++ r )
      {
        double v  = M[ i - 1 ][ r - 1 ] + M[ r ][ j ] + w;
        if( r == i || v < q ) {
          q = v;
		  x = r - 1;
		}
      } // end for
      M[ i - 1 ][ j ] = q;
	  B[ i - 2 ][ j - 1 ] = x;
    } // end for
  } // end for

  unsigned long long k = T.size();
  optPadre = treeOpt(T, B, 0, k - 1);
  avlPadre = treeAvl(T, 0, k);
  return( M[ 1 ][ P.size( ) ] );
}

int main( int argc, char** argv )
{
  std::vector< std::string > T;
  std::vector< double > P, Q;
  Nodo<std::string>* optPadre;
  Nodo<std::string>* avlPadre;
  unsigned long long repeticionesPalabra = 0; //¿Cuántas veces está la palabra más repetida?
  std::string palabraRepetida = "";

  std::ifstream file( argv[ 1 ] );
  std::string line;
  Q.push_back( 1 );
  double nP = 0;
  while( std::getline( file, line ) )
  {
    std::istringstream in_line( line );
    T.push_back( "" );
    P.push_back( 0 );
    Q.push_back( 1 );
    in_line >> T.back( ) >> P.back( );
	if (repeticionesPalabra < P.back()){ //Probabilidad de éxito para enocntrarla
	  repeticionesPalabra = P.back();
	  palabraRepetida = T.back();
	}
    nP += P.back( );
  } // end while

  double pP = 0.8 / nP;
  double pQ = 0.2 / double( Q.size( ) );

  for( unsigned i = 0; i < P.size( ); ++i )
  {
    P[ i ] *= pP;
    Q[ i ] *= pQ;
  } // end for
  Q[ P.size( ) ] *= pQ;

  double R = BuildTree( T, P, Q, optPadre, avlPadre );
  
  std::cout << "\n";
  std::cout << "El arbol binario optimo visto en preorden es: ";
  std::vector<std::string> arbolPreorden = optPadre->preorden();
  for (unsigned long long i = 0; i < arbolPreorden.size(); i++) {
    std::cout << arbolPreorden[i];
    if (i < arbolPreorden.size() - 1) {
      std::cout << " ";
	}
  }
  std::cout << "\n";
  std::cout << "El arbol avl visto en preorden es: ";
  arbolPreorden = avlPadre->preorden();
  for (unsigned long long i = 0; i < arbolPreorden.size(); i++) {
    std::cout << arbolPreorden[i];
    if (i < arbolPreorden.size() - 1) {
      std::cout << " ";
	}
  }
  std::cout << "\n\n";
  saltosPalabraRepetida(optPadre, avlPadre, palabraRepetida);
  //std::cout << R << std::endl;
  
  return( EXIT_SUCCESS );
}

// eof - build_tree.cxx
