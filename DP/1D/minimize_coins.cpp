#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;

int solve(int amount, vector<int>& dp, vector<int>& coins) {
    if (amount == 0) return 0;
    if (amount < 0) return INT_MAX;
    if (dp[amount] != -1) return dp[amount];

    int min_val = INT_MAX;
    for (int pos = 0; pos < coins.size(); pos++) {
        int sub = solve(amount - coins[pos], dp, coins);
        if (sub != INT_MAX)
            min_val = min(min_val, 1 + sub);
    }
    return dp[amount] = min_val;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> coins(n);
    for (int i = 0; i < n; i++) cin >> coins[i];

    vector<int> dp(m + 1, -1);
    int res = solve(m, dp, coins);

    if (res == INT_MAX) cout << -1 << endl;
    else cout << res << endl;

    return 0;
}
