#include <bits/stdc++.h>
using namespace std;

void ePair(int a, int b, int c) {
  pair<int, int> p = {a, b};
  cout << p.first << " " << p.second << endl;
  pair<int, pair<int, int>> p2 = {a, {b, c}};
  cout << p2.first << " " << p2.second.second << " " << p2.second.first << endl;
  pair<int, int> arr[] = {{a, b}, {b, c}, {c, a}};
  cout << arr[1].second;
}

void eVector(int a, int b, int c) {
  vector<int> v;
  v.push_back(a);
  v.emplace_back(b);
  v.emplace_back(c);

  vector<pair<int, int>> vec;
  vec.push_back({1, 2});
  vec.emplace_back(1, 2);

  vector<int> v2(5, 100);

  vector<int> v3(5);
  vector<int> v4(5, 20);
  vector<int> v5(v4);

//   vector<int>::iterator it = v.begin();
//   it++;
//   //   cout << *(it) << endl;

//   vector<int>::iterator it2 = v.end();
  //   cout << *(it2-1) << endl;

  for(vector<int>::iterator it = v.begin(); it!=v.end();it++){
    cout<< *(it) << endl;
  }

  for (auto it = v.begin(); it != v.end(); it++) {
    cout << *(it) << endl;
  }

  for (auto i : v) {
    cout << i << endl;
  }

  v.erase(v.begin()+1);
  
}

int main() {
  int a, b, c;
  cin >> a;
  cin >> b;
  cin >> c;
  //   ePair(a, b, c);
  eVector(a, b, c);
  return 0;
}