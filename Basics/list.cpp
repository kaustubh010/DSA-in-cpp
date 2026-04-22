#include <bits/stdc++.h>
using namespace std;

int main() {
  list<int> ls;
  ls.push_back(2);
  ls.emplace_back(4);
  ls.push_front(5);
  ls.emplace_front(2);
  //   for (auto i : ls) {
  //     cout << i << endl;
  //   }

  stack<int> st;
  st.push(2);
  st.emplace(4);
  //   cout<< st.top();
  //   cout<< st.size();
  //   cout << st.empty();
  stack<int> st1, st2;
  st1.swap(st2);

  queue<int> q;
  q.push(1);
  q.push(4);
  q.emplace(2);
  q.back() += 5;
  //   cout<<q.back();
  //   cout<<q.front();
  q.pop();
  //   cout<<q.front();

  // Max Heap
  priority_queue<int> pq;
  pq.push(2);
  pq.push(5);
  pq.emplace(10);
  cout << pq.top() << endl;
  pq.pop();
  cout << pq.top() << endl;

  // Min Heap
  priority_queue<int, vector<int>, greater<int>> mpq;
  mpq.push(4);
  mpq.push(8);
  mpq.emplace(10);
  cout << mpq.top() << endl;
  mpq.pop();
  cout << mpq.top() << endl;
  return 0;
}