#include <bits/stdc++.h>
using namespace std;

int printSum(int n) {
  if (n == 0) {
    return 0;
  }
  return n + printSum(n - 1);
}

int factorial(int n){
    if(n==0){
        return 1;
    }
    return n * factorial(n-1);
}

int main() {
  int n;
  cin >> n;
  cout << "Sum is: " << printSum(n)<<endl;
  cout << "Factorial is: "<< factorial(n);
  return 0;
}