#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int longestSequence(vector<vector<int>> const &matriz, int i, int j) {
  int recursion = 0;
  int n = matriz.size();

  if ((matriz[i][j] - matriz[i - 1][j] == 1) && (i > 0)) {
    recursion = longestSequence(matriz, i - 1, j);
  }
  if ((matriz[i][j] - matriz[i][j + 1] == 1) && (j + 1 < n)) {
    recursion = longestSequence(matriz, i, j + 1);
  }
  if ((matriz[i][j] - matriz[i + 1][j] == 1) && (i + 1 < n)) {
    recursion = longestSequence(matriz, i + 1, j);
  }
  if ((matriz[i][j] - matriz[i][j - 1] == 1) && (j > 0)) {
    recursion = longestSequence(matriz, i, j - 1);
  }
  return recursion+1;
}

int longestSequence(vector<vector<int>> const &matriz) {
  int actual = 0;
  for (int i = 0; i < matriz.size(); i++) {
    for (int j = 0; j < matriz.size(); j++) {
      int len = longestSequence(matriz, i, j);
      if (len > actual) {
        actual = len;
      }
    }
  }
  return actual;
}

int main() {
  vector<vector<int>> matriz = {
      {10, 16, 15, 12}, 
      {9, 8, 7, 13}, 
      {2, 5, 6, 14}, 
      {3, 4, 1, 11}};
  cout << longestSequence(matriz);

  return 0;
}
