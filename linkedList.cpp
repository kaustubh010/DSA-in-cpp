#include <bits/stdc++.h>
using namespace std;

class Node {
 public:
  int data;
  Node* next;
  Node(int data1, Node* next1) {
    data = data1;
    next = next1;
  }
  Node(int data1) {
    data = data1;
    next = nullptr;
  }
};

Node* convert2LL(vector<int>& arr) {
  Node* head = new Node(arr[0]);
  Node* mover = head;
  for (int i = 1; i < arr.size(); i++) {
    Node* temp = new Node(arr[i]);
    mover->next = temp;
    mover = temp;
  }
  return head;
}

int lengthofLL(Node* head) {
  int cnt = 0;
  Node* temp = head;
  while (temp) {
    temp = temp->next;
    cnt++;
  }
  return cnt;
}

int isPresentInLL(Node* head, int val) {
  Node* temp = head;
  while (temp) {
    if (temp->data == val) {
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}

int main() {
  vector<int> arr = {5, 7, 8, 9};
  Node* head = convert2LL(arr);
//   cout << lengthofLL(head);
  cout << isPresentInLL(head, 15);
  return 0;
}