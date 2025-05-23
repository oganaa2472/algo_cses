#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    sort(t.begin(), t.end());
    
    vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= x; ++j) {
            for (int l = i; l >= 1; --l) {
                int penalty = t[i - 1] - t[l - 1];
                if (penalty > j) break;
                dp[i][j] = (dp[i][j] + dp[l - 1][j - penalty]) % MOD;
            }
        }
    }
    
    int ans = 0;
    for (int j = 0; j <= x; ++j) {
        ans = (ans + dp[n][j]) % MOD;
    }
    cout << ans << endl;
    return 0;
}