
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
int n, m;
vector<int> x;
vector<vector<int>> dp;

int solve(int i, int prev) {
    if (i == n) return 1;  // base case: full array is built

    if (dp[i][prev] != -1) return dp[i][prev];
    int res = 0;
    if(x[i]!=0){
        if (abs(x[i] - prev) <= 1)
            res = solve(i + 1, x[i]);
        else
            res = 0;
    }else{
        for (int d = -1; d <= 1; d++) {
            int next = prev + d;
            if (next >= 1 && next <= m)
                res = (res + solve(i + 1, next)) % MOD;
        }
    }
    return dp[i][prev] = res;
}
int main() {
    cin >> n >> m;
    x.resize(n);
    for (int i = 0; i < n; i++) cin >> x[i];

    dp.assign(n, vector<int>(m + 2, -1));

    int result = 0;
    if (x[0] != 0) {
        result = solve(1, x[0]);
    } else {
        for (int val = 1; val <= m; val++) {
            result = (result + solve(1, val)) % MOD;
        }
    }

    cout << result << '\n';
    return 0;
}