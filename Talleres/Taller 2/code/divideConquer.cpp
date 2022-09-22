#include <iostream>
#include <math.h>
#include <string>
#include <algorithm>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

struct sTupla {
  unsigned long long decimal;
  unsigned long long binario;
};

unsigned long long decBinary(unsigned long long a){
  unsigned long long bin = 0, prod = 1, rem;
  while (a != 0){
    rem =  a%2;
    bin += rem * prod;
    a = a/2;
    prod *= 10;
  }
  return bin;
}
unsigned long long binDecimal(unsigned long long n){
  unsigned long long a = 0, i = 0, rem;
  if ((n == 0)||(n == 1)){
    return n;
  } else {
    while (n != 0){
      rem =  n%10;
      n = n / 10;
      a = a + (rem*pow(2,i));
      i++;
    }
    return a;
  }
}
unsigned long long reversebinary_aux(unsigned long long bin, int b, int e, int tam) {
  if (e-b <= 1){
    unsigned long long devolver;
    int num;
    num = bin/pow(10,tam-e-1);
    if (e-b == 1) {
      devolver = (num%10) * 10;
      num = num/10;
      devolver = devolver + (num%10);
      return devolver;
    } else if (e-b == 0) {
      devolver = num%10;
      return devolver;
    }
  } else if (e-b > 1){
    int q = ((b + e) / 2);
    double left = reversebinary_aux(bin, b, q, tam);
    double right = reversebinary_aux(bin, q+1, e, tam);
    string l = to_string((int)left);
    string r = to_string((int)right);
    string res = r+l;
    return std::stod(res);
  }
}

sTupla reverseBinary(unsigned long long a){
  sTupla tupla;
  unsigned long long bin, revBin, newNum;
  if ((a == 0)||(a == 1)){
    tupla.binario = a;
    tupla.decimal = a;
    return tupla;
  } else {
    bin = decBinary(a);
    string aux = to_string(bin);
    std::replace(aux.begin(), aux.end(), '0', '9');
    revBin = reversebinary_aux(std::stoull(aux), 0, aux.length()-1, aux.length());
    string aux2 = to_string(revBin);
    std::replace(aux2.begin(), aux2.end(), '9', '0');
    tupla.binario = std::stoull(aux2);
    newNum = binDecimal(std::stoull(aux2));
    tupla.decimal = newNum;
    return tupla;
  }
}


int main() {
  unsigned long long num = 0;
  cout << "~~~~~ Algoritmo dividir y vencer ~~~~~ \n";
  cout << "Ingrese un número: ";
  cin >> num;
  sTupla tupla;
  tupla = reverseBinary(num);
  cout << "El binario invertido es: " << tupla.binario << " y su decimal es: " << tupla.decimal;
}
