#include <bits/stdc++.h>
using namespace std;
 
int main() {
    long long n;
    cin >> n;
    long long answer = INT_MIN;
    long long sum = 0;
    for (int i = 0; i < n; ++i){
        long long a;
        cin>>a;
        sum = max(sum+a,a);
        answer=max(sum,answer);
    }
    cout<<answer;
        
    
    return 0;
}