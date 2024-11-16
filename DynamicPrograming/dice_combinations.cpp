#include <iostream>
#include <vector>
using namespace std;

long long MOD = 1e9 + 7;

long long solve(vector<long long>& dp,long long n){
    if(n==0) return 1;
    if(dp[n]!=-1) return dp[n];
    long long ans=0;
    for(int i = 1;i<=6;i++){
        if(n-i>=0){
            ans += solve(dp,n-i);
        }
    }
    dp[n] = ans%MOD;
    return dp[n];
}

int main() {
    long long n;
    cin >> n;
    vector<long long> dp(n+1,-1);
    long long answer = solve(dp,n);
    cout<<answer<<endl;
    return 0;
}
