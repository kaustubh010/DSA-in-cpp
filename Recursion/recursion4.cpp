#include <bits/stdc++.h>
using namespace std;

void reverseArr(int i, int arr[], int n) {
  if (i >= n / 2) return;
  swap(arr[i], arr[n - i - 1]);
  reverseArr(i + 1, arr, n);
}

bool checkPalindrome(int i, string &s) {
  if (i >= s.size() / 2) return true;
  if (s[i] != s[s.size() - i - 1]) {
    return false;
  }
  return checkPalindrome(i + 1, s);
}

int main() {
  int n;
  cin >> n;
  int arr[n];
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  reverseArr(0, arr, n);
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }

  string s;
  cin >> s;
  cout << endl << checkPalindrome(0, s);
  return 0;
}