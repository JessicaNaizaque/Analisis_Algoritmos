#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int longestSequence(vector<vector<int>> const &matriz, int i, int j,
                    vector<vector<int>> &M) {
  int recursion = 0;
  int n = matriz.size();

  if (M[i][j] != 0) {
    return M[i][j];
  }
  if ((matriz[i][j] - matriz[i - 1][j] == 1) && (i > 0)) {
    recursion = longestSequence(matriz, i - 1, j, M);
  }
  if ((matriz[i][j] - matriz[i][j + 1] == 1) && (j + 1 < n)) {
    recursion = longestSequence(matriz, i, j + 1, M);
  }
  if ((matriz[i][j] - matriz[i + 1][j] == 1) && (i + 1 < n)) {
    recursion = longestSequence(matriz, i + 1, j, M);
  }
  if ((matriz[i][j] - matriz[i][j - 1] == 1) && (j > 0)) {
    recursion = longestSequence(matriz, i, j - 1, M);
  }
  M[i][j] = recursion + 1;
  return M[i][j];
}

int longestSequence(vector<vector<int>> const &matriz, vector<vector<int>> &M) {
  int actual = 0;
  for (int i = 0; i < matriz.size(); i++) {
    for (int j = 0; j < matriz.size(); j++) {
      int len = longestSequence(matriz, i, j, M);
      if (len > actual) {
        actual = len;
      }
    }
  }
  return actual;
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

int main() {
  vector<vector<int>> matriz = {
      {10, 16, 15, 12}, 
      {9, 8, 7, 13}, 
      {2, 5, 6, 14}, 
      {3, 4, 1, 11}
  };
  vector<vector<int>> M(matriz.size(), vector<int>(matriz.size()));
  cout << longestSequence(matriz, M) << endl;
  // for (int i = 0; i < matriz.size(); i++) {
  //   printSequence(M[i]);
  // }

  return 0;
}