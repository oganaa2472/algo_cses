#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD = 1e9+7;
vector<vector<ll>> dp;

int solve(ll i,ll j, vector<ll>&piles) {
    if(i>j) return 0;
    if(i==j) return dp[i][j] = piles[i];
    if(dp[i][j]!=-1){
        return dp[i][j];
    }
    ll chooseFirst = piles[i] - solve(i+1,j,piles);
    ll chooseLast= piles[j] - solve(i,j-1,piles);
    return dp[i][j] = max(chooseFirst, chooseLast);
}

int main() {
    ll n;
    ll sum = 0;
    cin >> n;
    vector<ll> piles(n);
    for(ll i = 0;i<n;i++){
        cin>>piles[i];
        sum+=piles[i];
    }
    dp.resize(n,vector<ll>(n,-1));
    ll result = sum + solve(0,n-1,piles);
    cout << result/2 <<endl;  // `2`-ийн модуляр урвуу
}
