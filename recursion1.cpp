#include <bits/stdc++.h>
using namespace std;

int cnt = 0;
void printCount(){
    if (cnt == 10) return;
    cout<<cnt<<endl;
    cnt++;
    printCount();
}

int main() {
    printCount();
    return 0;
}