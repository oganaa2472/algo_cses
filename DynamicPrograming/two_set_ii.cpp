#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;
vector<vector<int>> memo;

int countWays(int i, int sum) {
    if (sum == 0) return 1;  
    if (i == 0 || sum < 0) return 0;  
    if (memo[i][sum] != -1) return memo[i][sum];

    int exclude = countWays(i-1, sum);
    int include = countWays(i-1, sum - i); 

    return memo[i][sum] = (include + exclude) % MOD;
}

int main() {
    int n;
    cin >> n;
    int target = n * (n+1) / 2;

    if (target % 2) {
        cout << 0 << endl;
        return 0;
    }
    
    target /= 2;
    memo.assign(n, vector<int>(target + 1, -1));

    int result = countWays(n-1, target);
    cout << (result) % MOD << endl;  // `2`-ийн модуляр урвуу
}
