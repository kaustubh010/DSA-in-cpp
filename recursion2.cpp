#include <bits/stdc++.h>
using namespace std;

void printName(int i, int n) {
  if (i > n) return;
  printName(i + 1, n);
  cout << i << endl;
}

int main() {
  int n;
  cin >> n;
  printName(1, n);
  return 0;
}