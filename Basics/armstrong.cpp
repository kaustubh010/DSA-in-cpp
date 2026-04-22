#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;
    int dup =n;
    int arm = 0;
    while(dup!=0){
        int ld=dup%10;
        int count = log10(dup) +1;
        dup/=10;
        arm = arm + pow(ld,count);
    }
    if(n==arm)cout<<"true";
    else cout<<"false";
    return 0;
}