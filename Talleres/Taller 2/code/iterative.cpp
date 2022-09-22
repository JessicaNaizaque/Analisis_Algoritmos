#include <iostream>
#include <math.h>

using namespace std;

struct sTupla {
  unsigned long long decimal;
  unsigned long long binario;
};  

unsigned long long decBinary(unsigned long long a){
  unsigned long long bin = 0, prod = 1, rem = 0;
  if(a == 0 || a == 1){
    return a;
  } else {
    while (a != 0) {
      rem = a%2;
      bin = bin + (rem*prod);
      a = a/2;
      prod = prod*10;
    }
    return bin;
  }
}

unsigned long long binDecimal(unsigned long long n) {
  unsigned long long a = 0, rem = 0;
  int i = 0;
  if(n == 0 || n == 1) {
    return n;
  } else {
    while(n != 0) {
      rem = n%10;
      n = n/10;
      a = a + (rem*(pow(2, i)));
      i++;
    }
    return a;
  }
}

sTupla reverseBinary(unsigned long long a){
  unsigned long long binary = decBinary(a);
  unsigned long long binaryInv = 0, rem = 0, newNum = 0;
  while (binary > 0) {
    rem = binary%10;
    binaryInv = (binaryInv * 10) + rem;
    binary = binary/10;
  }
  newNum = binDecimal(binaryInv);
  sTupla tupla;
  tupla.decimal = newNum;
  tupla.binario = binaryInv;
  return tupla;  
}

int main() {
  unsigned long long a;
  cout << "~~~~~ Algoritmo Iterativo ~~~~~ \n";
  cout << "Ingrese el número decimal: ";
  cin >> a;
  sTupla tupla = reverseBinary(a);
  cout << "El binario invertido es: " << tupla.binario << " y su decimal es: " << tupla.decimal;
}