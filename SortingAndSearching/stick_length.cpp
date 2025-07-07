#include <bits/stdc++.h>
using namespace std;
 
int main() {
    long long n;
    cin >> n;
    long long answer = 0;
    vector<int> stick(n);
    for (int i = 0; i < n; ++i){
       cin>>stick[i];
    }
    sort(stick.begin(),stick.end());
    int median=n/2;
    for(auto num:stick){
        answer+=abs(stick[median]-num);
    }
    cout<<answer;
    
    return 0;
}