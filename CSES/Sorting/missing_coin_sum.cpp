// missing coin_sum.cpp
#include <bits/stdc++.h>
using namespace std;  
int main() {
    int n;
    cin>>n;
    vector<int> coins(n);
    for(int i = 0;i<n;i++ )cin>>coins[i];
    sort(coins.begin(),coins.end());
    long long c = 1;
    for(int i = 0;i<n;i++){
        if(coins[i]>c)break;
        c+=coins[i];
    }
    cout<<c;
    return 0; 
  }
// -     --- IGNORE ---