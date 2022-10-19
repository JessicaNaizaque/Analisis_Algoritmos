#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

struct sCoordenada{
    int i;
    int j;
    int respuesta = 0;
};

bool checkNum(vector<vector<int>> const &matriz, int num){
  int n = matriz.size();
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if (num == matriz[i][j]){
        return false;
      }
    }
  }
  return true;
}
vector<vector<int>> initialMat(int n){
  int num;
  vector<vector<int>> matriz(n, vector<int>(n));
  srand(time(0));
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      num = 1 + rand() % (n*n);
      while(!checkNum(matriz, num)){
        num = 1 + rand() % (n*n);
      }
      matriz.at(i).at(j) = num;
    }
  }
  return matriz;
} 

void printSequence(vector<int> const &seq) {
  cout << "[";
  int n = seq.size();
  for (int i = 0; i < n; i++) {
    cout << seq[i];
    if (i < n - 1) {
      cout << ", ";
    }
  }
  cout << "]";
  cout << endl;
}

void printCoor(vector<sCoordenada> const &coor) {
  cout << "[";
  int n = coor.size();
  for (int i = 0; i < n; i++) {
    cout << coor[i].i << "-" << coor[i].j;
    if (i < n - 1) {
      cout << ", ";
    }
  }
  cout << "]";
  cout << endl;
}

int longestSequence(vector<vector<int>> const &matriz, int i, int j, vector<vector<int>> &M, vector<vector<sCoordenada>> &B) {
  int recursion = 0;
  int maximo = 0;
  sCoordenada coor;
  int n = matriz.size();

  if (M[i][j] != 0) {
    return M[i][j];
  }
  if ((matriz[i][j] - matriz[i - 1][j] == 1) && (i > 0)) {
    recursion = longestSequence(matriz, i - 1, j, M, B);
    if (maximo < recursion){
      maximo = recursion;
    }
    if (maximo == M[i-1][j]){
      coor.i = i-1;
      coor.j = j;
      B[i][j] = coor;
    }
  }  
  if ((matriz[i][j] - matriz[i][j + 1] == 1) && (j + 1 < n)) {
    recursion = longestSequence(matriz, i, j + 1, M, B);
    if (maximo < recursion){
      maximo = recursion;
    }
    if (maximo == M[i][j+1]){
      coor.i = i;
      coor.j = j+1;
      B[i][j] = coor;
    }
  }
  if ((matriz[i][j] - matriz[i + 1][j] == 1) && (i + 1 < n)) {
    recursion = longestSequence(matriz, i + 1, j, M, B);
    if (maximo < recursion){
      maximo = recursion;
    }
    if (maximo == M[i+1][j]){
      coor.i = i+1;
      coor.j = j;
      B[i][j] = coor;
    }
  }
  if ((matriz[i][j] - matriz[i][j - 1] == 1) && (j > 0)) {
    recursion = longestSequence(matriz, i, j - 1, M, B);
    if (maximo < recursion){
      maximo = recursion;
    }
    if (maximo == M[i][j-1]){
      coor.i = i;
      coor.j = j-1;
      B[i][j] = coor;
    }
  }
  M[i][j] = recursion + 1;
  return M[i][j];
}

sCoordenada longestSequence(vector<vector<int>> const &matriz, vector<vector<int>> &M, vector<vector<sCoordenada>> &B) {
  int actual = 0;
  sCoordenada final;
  for (int i = 0; i < matriz.size(); i++) {
    for (int j = 0; j < matriz.size(); j++) {
      int len = longestSequence(matriz, i, j, M, B);
      if (len > actual) {
        final.i = i;
        final.j = j;
        actual = len;
      }
    }
  }
  final.respuesta = actual;
  return final;
}

int main() {
  /*
          Matriz donde se ingresa el tamaño y se crea de manera aleatoria
  int n;
  cout << "Por favor ingrese el tamaño de la matriz: ";
  cin >> n;
  vector<vector<int>> matriz(n, vector<int>(n));
  matriz  = initialMat(n);
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      cout << setw(3) << matriz[i][j];
    }
    cout << endl;
  }
  cout << endl;

*/
  
  //        MATRICES CREADAS (casos de prueba)
  vector<vector<int>> matriz = {
      {10, 16, 15, 12}, 
      {9, 8, 7, 13}, 
      {2, 5, 6, 14}, 
      {3, 4, 1, 11}
  };
  /*
  vector<vector<int>> matriz = {
      {1,42,43,20,19,16,15,12},
      {5,2,44,21,18,17,14,13},
      {6,45,3,22,23,59,60,61},
      {7,29,28,4,24,58,63,62},
      {8,30,27,26,25,57,41,64},
      {9,31,32,54,55,56,40,39},
      {10,53,33,34,35,36,37,38},
      {11,52,51,50,49,48,47,46}
  };
  
  vector<vector<int>> matriz = {
      {1,2,49,71,111,112,113,114,115,116,117,118,119,120,81,52},
      {109,3,73,72,193,194,195,196,197,198,199,200,201,202,82,53},
      {110,4,5,137,249,250,251,252,253,254,255,256,248,247,83,54},
      {8,7,6,138,139,140,141,142,143,144,145,146,147,148,84,55},
      {9,10,11,12,13,14,15,16,227,226,221,220,59,58,57,56},
      {130,149,74,75,76,77,80,17,228,225,222,219,60,242,85,246},
      {131,150,180,203,79,78,19,18,229,224,223,218,61,243,244,245},
      {132,151,181,204,207,21,20,101,102,103,104,105,62,106,107,108},
      {133,152,182,205,206,22,23,24,25,26,27,217,63,230,231,232},
      {134,153,183,184,185,121,208,211,212,215,28,216,64,239,240,233},
      {135,154,190,189,186,122,209,210,213,214,29,30,31,238,241,234},
      {136,155,191,188,187,123,38,37,36,35,34,33,32,237,236,235},
      {90,91,192,99,100,124,39,40,41,42,43,44,45,46,47,48},
      {89,92,93,98,51,125,167,168,169,172,173,176,65,177,178,179},
      {88,87,94,97,129,126,157,158,170,171,174,175,66,67,68,69},
      {50,86,95,96,128,127,156,159,160,161,162,163,164,165,166,70}
  };
  
  vector<vector<int>> matriz = {
      {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18},
      {86,87,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,19},
      {85,88,99,204,205,206,207,208,209,210,211,212,213,214,145,144,115,20},
      {84,89,98,203,244,243,242,241,240,239,238,237,236,215,146,143,116,21},
      {83,90,97,202,245,292,293,294,295,296,271,270,235,216,147,142,117,22},
      {82,91,96,201,246,291,312,313,324,297,272,269,234,217,148,141,118,23},
      {81,92,95,200,247,290,311,314,323,298,273,268,233,218,149,140,119,24},
      {80,93,94,199,248,289,310,315,322,299,274,267,232,219,150,139,120,25},
      {79,78,77,198,249,288,309,316,321,300,275,266,231,220,151,138,121,26},
      {60,61,76,197,250,287,308,317,320,301,276,265,230,221,152,137,122,27},
      {59,62,75,196,251,286,307,318,319,302,277,264,229,222,153,136,123,28},
      {58,63,74,195,252,285,306,305,304,303,278,263,228,223,154,135,124,29},
      {57,64,73,194,253,284,283,282,281,280,279,262,227,224,155,134,125,30},
      {56,65,72,193,254,255,256,257,258,259,260,261,226,225,156,133,126,31},
      {55,66,71,192,191,190,189,188,187,186,185,184,183,182,157,132,127,32},
      {54,67,70,171,172,173,174,175,176,177,178,179,180,181,158,131,128,33},
      {53,68,69,170,169,168,167,166,165,164,163,162,161,160,159,130,129,34},
      {52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35}
  };
  */
  vector<vector<int>> M(matriz.size(), vector<int>(matriz.size()));
  for (int i = 0; i < matriz.size(); i++){
    for (int j = 0; j < matriz.size(); j++){
      M[i][j] = 0;
    }
  }
  vector<vector<sCoordenada>> B(matriz.size(), vector<sCoordenada>(matriz.size()));
  sCoordenada c;
  for (int i = 0; i < matriz.size(); i++){
    for (int j = 0; j < matriz.size(); j++){
      c.i = i;
      c.j = j;
      B[i][j] = c;
    }
  }
  sCoordenada resp = longestSequence(matriz, M, B);
  cout << resp.respuesta << endl;
  
  cout << endl;
  for (int i = 0; i < matriz.size(); i++) {
    printSequence(M[i]);
  }
  cout << endl;
  for (int i = 0; i < matriz.size(); i++) {
    printCoor(B[i]);
  }
  //Para encontrar el camino con la matriz de backtracking:
  vector<int> camino;
  bool sigue = true;
  sCoordenada backCoor = resp;
  int conta = 0;
  while (conta < resp.respuesta){
    camino.push_back(matriz[backCoor.i][backCoor.j]);
    backCoor = B[backCoor.i][backCoor.j];
    conta++;
  }
  cout << "\nLa secuencia creciente más larga de la matriz es: ";
  reverse(camino.begin(), camino.end());
  printSequence(camino);
  return 0;
}